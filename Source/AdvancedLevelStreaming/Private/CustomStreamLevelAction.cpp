#include "CustomStreamLevelAction.h"
#include "Engine/World.h"

FCustomStreamLevelAction::FCustomStreamLevelAction(bool bIsLoading, const FName& InLevelName, bool bIsMakeVisibleAfterLoad, bool bIsShouldBlockOnLoad, const FLatentActionInfo& InLatentInfo, UWorld* World)
	: bLoading(bIsLoading)
	, bMakeVisibleAfterLoad(bIsMakeVisibleAfterLoad)
	, bShouldBlockOnLoad(bIsShouldBlockOnLoad)
	, LevelName(InLevelName)
	, LatentInfo(InLatentInfo)
{
	Level = FindAndCacheLevelStreamingObject(LevelName, World);
	ActivateLevel(Level);
}

void FCustomStreamLevelAction::UpdateOperation(FLatentResponse& Response)
{
	ULevelStreaming* LevelStreamingObject = Level; // to avoid confusion.
	bool bIsOperationFinished = UpdateLevel(LevelStreamingObject);
	Response.FinishAndTriggerIf(bIsOperationFinished, LatentInfo.ExecutionFunction, LatentInfo.Linkage, LatentInfo.CallbackTarget);
}

#if WITH_EDITOR
FString FCustomStreamLevelAction::GetDescription() const
{
	return FString::Printf(TEXT("Streaming Level in progress...(%s)"), *LevelName.ToString());
}
#endif

/**
* Helper function to potentially find a level streaming object by name
*
* @param	LevelName							Name of level to search streaming object for in case Level is NULL
* @return	level streaming object or NULL if none was found
*/
ULevelStreaming* FCustomStreamLevelAction::FindAndCacheLevelStreamingObject(const FName LevelName, UWorld* InWorld)
{
	// Search for the level object by name.
	if (LevelName != NAME_None)
	{
		FString SearchPackageName = MakeSafeLevelName(LevelName, InWorld);
		if (FPackageName::IsShortPackageName(SearchPackageName))
		{
			// Make sure MyMap1 and Map1 names do not resolve to a same streaming level
			SearchPackageName = TEXT("/") + SearchPackageName;
		}

		for (ULevelStreaming* LevelStreaming : InWorld->GetStreamingLevels())
		{
			// We check only suffix of package name, to handle situations when packages were saved for play into a temporary folder
			// Like Saved/Autosaves/PackageName
			if (LevelStreaming &&
				LevelStreaming->GetWorldAssetPackageName().EndsWith(SearchPackageName, ESearchCase::IgnoreCase))
			{
				return LevelStreaming;
			}
		}
	}

	return NULL;
}

/**
* Given a level name, returns a level name that will work with Play on Editor or Play on Console
*
* @param	InLevelName		Raw level name (no UEDPIE or UED<console> prefix)
* @param	InWorld			World in which to check for other instances of the name
*/
FString FCustomStreamLevelAction::MakeSafeLevelName(const FName& InLevelName, UWorld* InWorld)
{
	// Special case for PIE, the PackageName gets mangled.
	if (!InWorld->StreamingLevelsPrefix.IsEmpty())
	{
		FString PackageName = FPackageName::GetShortName(InLevelName);
		if (!PackageName.StartsWith(InWorld->StreamingLevelsPrefix))
		{
			PackageName = InWorld->StreamingLevelsPrefix + PackageName;
		}

		if (!FPackageName::IsShortPackageName(InLevelName))
		{
			PackageName = FPackageName::GetLongPackagePath(InLevelName.ToString()) + TEXT("/") + PackageName;
		}

		return PackageName;
	}

	return InLevelName.ToString();
}
/**
* Handles "Activated" for single ULevelStreaming object.
*
* @param	LevelStreamingObject	LevelStreaming object to handle "Activated" for.
*/
void FCustomStreamLevelAction::ActivateLevel(ULevelStreaming* LevelStreamingObject)
{
	if (LevelStreamingObject != NULL)
	{
		// Loading.
		if (bLoading)
		{
			UE_LOG(LogStreaming, Log, TEXT("Streaming in level %s (%s)..."), *LevelStreamingObject->GetName(), *LevelStreamingObject->GetWorldAssetPackageName());
			LevelStreamingObject->SetShouldBeLoaded(true);
			LevelStreamingObject->SetShouldBeVisible(LevelStreamingObject->GetShouldBeVisibleFlag() | bMakeVisibleAfterLoad);
			LevelStreamingObject->bShouldBlockOnLoad = bShouldBlockOnLoad;
		}
		// Unloading.
		else
		{
			UE_LOG(LogStreaming, Log, TEXT("Streaming out level %s (%s)..."), *LevelStreamingObject->GetName(), *LevelStreamingObject->GetWorldAssetPackageName());
			LevelStreamingObject->SetShouldBeLoaded(false);
			LevelStreamingObject->SetShouldBeVisible(false);
		}

		UWorld* LevelWorld = CastChecked<UWorld>(LevelStreamingObject->GetOuter());
		// If we have a valid world
		if (LevelWorld)
		{
			// Notify players of the change
			for (FConstPlayerControllerIterator Iterator = LevelWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				APlayerController* PlayerController = Iterator->Get();

				UE_LOG(LogLevel, Log, TEXT("ActivateLevel %s %i %i %i"),
					*LevelStreamingObject->GetWorldAssetPackageName(),
					LevelStreamingObject->ShouldBeLoaded(),
					LevelStreamingObject->ShouldBeVisible(),
					LevelStreamingObject->bShouldBlockOnLoad);



				PlayerController->LevelStreamingStatusChanged(
					LevelStreamingObject,
					LevelStreamingObject->ShouldBeLoaded(),
					LevelStreamingObject->ShouldBeVisible(),
					LevelStreamingObject->bShouldBlockOnLoad,
					INDEX_NONE);

			}
		}
	}
	else
	{
		UE_LOG(LogLevel, Warning, TEXT("Failed to find streaming level object associated with '%s'"), *LevelName.ToString());
	}
}

/**
* Handles "UpdateOp" for single ULevelStreaming object.
*
* @param	LevelStreamingObject	LevelStreaming object to handle "UpdateOp" for.
*
* @return true if operation has completed, false if still in progress
*/
bool FCustomStreamLevelAction::UpdateLevel(ULevelStreaming* LevelStreamingObject)
{
	// No level streaming object associated with this sequence.
	if (LevelStreamingObject == NULL)
	{
		return true;
	}
	// Level is neither loaded nor should it be so we finished (in the sense that we have a pending GC request) unloading.
	else if ((LevelStreamingObject->GetLoadedLevel() == NULL) && !LevelStreamingObject->ShouldBeLoaded())
	{
		return true;
	}
	// Level shouldn't be loaded but is as background level streaming is enabled so we need to fire finished event regardless.
	else if (LevelStreamingObject->GetLoadedLevel() && !LevelStreamingObject->ShouldBeLoaded() && !GUseBackgroundLevelStreaming)
	{
		return true;
	}
	// Level is both loaded and wanted so we finished loading.
	else if (LevelStreamingObject->GetLoadedLevel() && LevelStreamingObject->ShouldBeLoaded()
		// Make sure we are visible if we are required to be so.
		&& (!bMakeVisibleAfterLoad || LevelStreamingObject->GetLoadedLevel()->bIsVisible))
	{
		return true;
	}

	// Loading/ unloading in progress.
	return false;
}