#include "SaveLevelInfoCommandlet.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelBounds.h"
#include "Engine/Engine.h"
#include "Modules/ModuleManager.h"
#include "Factories/DataAssetFactory.h"
#include "LevelManager.h"
#include "AssetToolsModule.h"
#include "UObject/UObjectGlobals.h"
#include "ALSConfig.h"

#define LOCTEXT_NAMESPACE "SaveLevelInfoCommandlet"

USaveLevelInfoCommandlet::USaveLevelInfoCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}


int32 USaveLevelInfoCommandlet::Main(const FString& Params)
{
	if (UWorld * StartingWorld = Cast<UWorld>(GetDefault<UALSConfig>()->StartingMap.TryLoad()))
	{
		const TArray<ULevelStreaming*> StreamingLevels = StartingWorld->GetStreamingLevels();

		for (auto Level : StreamingLevels)
		{
			if (UWorld * LevelWorld = Level->GetWorldAsset().LoadSynchronous())
			{
				LevelWorld->InitWorld();
				FURL URL;
				LevelWorld->InitializeActorsForPlay(URL);
				
				SaveLevelInfo(LevelWorld);

				GEngine->DestroyWorldContext(LevelWorld);
				LevelWorld->DestroyWorld(false);
			}
		}

		return 0;
	}


	return 1;
}

void USaveLevelInfoCommandlet::SaveLevelInfo(UWorld * InLevelWorld)
{
	bool bOk = true;

	FBox LevelBox = ALevelBounds::CalculateLevelBounds(InLevelWorld->PersistentLevel);

	TArray<FTransform> DoorTransforms;
	TArray<int32> DoorStrengths;
	TArray<AActor*> Doors;
	UGameplayStatics::GetAllActorsOfClass(InLevelWorld, ALevelStreamingDoorPoint::StaticClass(), Doors);
	for (auto Door : Doors)
	{
		if (ALevelStreamingDoorPoint * DoorPoint = Cast<ALevelStreamingDoorPoint>(Door))
		{
			DoorTransforms.Add(Door->GetActorTransform());
			DoorStrengths.Add(DoorPoint->TypeStrength);
		}
	}

	FString LevelName = InLevelWorld->GetName();
	int32 UnderscoreIndex = -1;
	bOk &= LevelName.FindChar('_', UnderscoreIndex);
	int32 UnderscoreIndex2;
	bOk &= LevelName.FindLastChar('_', UnderscoreIndex2);
	FName TypeName = *LevelName.Mid(UnderscoreIndex + 1, UnderscoreIndex2 - UnderscoreIndex - 1);

	if (bOk)
	{
		WriteToAsset(InLevelWorld, LevelBox, DoorTransforms, DoorStrengths, TypeName);
	}
	
}

void USaveLevelInfoCommandlet::WriteToAsset(UWorld * InLevelWorld, FBox InLevelBox, TArray<FTransform> InDoorTransforms, TArray<int32> InDoorStrengths, FName InTypeName)
{
	FString PathName = InLevelWorld->GetPathName();
	int32 SlashIndex = -1;
	if (PathName.FindLastChar('/', SlashIndex))
	{
		PathName = PathName.LeftChop(PathName.Len() - SlashIndex - 1);
		PathName += InLevelWorld->GetName() + "_Data";
		UPackage * Package = CreatePackage(nullptr, *PathName); //find package first, if no, create
		check(Package);
		Package->FullyLoad();
		Package->Modify();
		FString FileName = InLevelWorld->GetName() + "_Data";
		ULevelInfoAsset * LevelAsset = NewObject<ULevelInfoAsset>(Package, ULevelInfoAsset::StaticClass(), *FileName, RF_Public | RF_Standalone);
		LevelAsset->LevelSavedInfo.LevelBox = InLevelBox;
		LevelAsset->LevelSavedInfo.DoorTransforms = InDoorTransforms;
		LevelAsset->LevelSavedInfo.DoorStrengths = InDoorStrengths;
		LevelAsset->LevelSavedInfo.LevelType = InTypeName;
		FString const PackageFileName = FPackageName::LongPackageNameToFilename(*Package->GetName(), FPackageName::GetAssetPackageExtension());

		UPackage::SavePackage(Package, NULL, RF_Standalone, *PackageFileName, GError, nullptr, false, true, SAVE_NoError);
	}
}

#undef LOCTEXT_NAMESPACE