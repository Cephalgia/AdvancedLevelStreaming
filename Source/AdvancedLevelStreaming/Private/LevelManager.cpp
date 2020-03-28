
#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomStreamLevelAction.h"
#include "DrawDebugHelpers.h"

FLevelDoor::FLevelDoor()
{

}

FLevelDoor::FLevelDoor(ALevelStreamingDoorPoint* InDoorPoint)
{
	DoorPoint = InDoorPoint;
}

FLevelInfo::FLevelInfo()
{

}

FLevelInfo::FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming, FTransform InLevelTransform)
{
	LevelName = InName;
	LevelStreaming = InLevelStreaming;
	LevelTransform = InLevelTransform;
}

void FLevelInfo::Reset()
{
	LevelStreaming = nullptr;
	LevelName = "";
	LevelDoors.Empty();
}

TSharedPtr<FLevelInfo> FLevelMap::GetLevelMapInfo(ULevel* InLevel)
{
	if (!InLevel)
	{
		return TSharedPtr<FLevelInfo>();
	}
	FName LevelName = InLevel->GetOuter()->GetFName();
	TSharedPtr<FLevelInfo> * FoundLevel = Levels.Find(LevelName);
	return FoundLevel ? *FoundLevel : TSharedPtr<FLevelInfo>();
}

bool FLevelMap::HasLevel(FName InName)
{
	TSharedPtr<FLevelInfo>* FoundLevel = Levels.Find(InName);
	bool bHasLevel = false;
	TArray<FName> LevelNames;
	Levels.GenerateKeyArray(LevelNames);
	bHasLevel = LevelNames.Contains(InName);
	bool AnotherHasLevel = FoundLevel != nullptr;
	return AnotherHasLevel;
}

void FLevelMap::RemoveLevel(FName InLevelName)
{
	Levels.Remove(InLevelName);
}

TSharedPtr<FLevelInfo> FLevelMap::GetCurrentLevel()
{
	TSharedPtr<FLevelInfo> * FoundLevel = Levels.Find(CurrentLevelName);
	return FoundLevel ? *FoundLevel : TSharedPtr<FLevelInfo>();
}

void FLevelMap::SetCurrentLevel(FName InLevelName)
{
	CurrentLevelName = InLevelName;
	UE_LOG(LogTemp, Warning, TEXT("CurrentLevel set to %s"), *InLevelName.ToString());
}

ULevelManager::ULevelManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULevelManager::Initialize()
{
	UWorld * CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	TArray<FName> Levels;
	TArray<FString> LevelPaths;
	const TArray<ULevelStreaming*> StreamingLevels = CurrentWorld->GetStreamingLevels();
	for (ULevelStreaming* StreamingLevel : StreamingLevels)
	{
		FString WorldAssetPackage = StreamingLevel->GetWorldAssetPackageName();
		int32 SlashIndex;
		if (WorldAssetPackage.FindLastChar('/', SlashIndex))
		{
			FString LevelName = WorldAssetPackage.RightChop(SlashIndex + 1);
			FSoftObjectPath LevelAssetName = WorldAssetPackage.LeftChop(WorldAssetPackage.Len() - SlashIndex) + "/Data.LevelInfo";
			if (ULevelInfoAsset * LevelAsset = Cast<ULevelInfoAsset>(LevelAssetName.TryLoad()))
			{
				LevelInfoAssets.Add(LevelName, LevelAsset);
			}
		}
	}


}

void ULevelManager::Tick(float DeltaSeconds)
{
	TArray<TSharedPtr<FLevelInfo>> MapValues;
	LevelMap.Levels.GenerateValueArray(MapValues);
	for (TSharedPtr<FLevelInfo> LevelInfo : MapValues)
	{
		bool bHasNonEmptyDoor = false;
		for (TSharedPtr<FLevelDoor> Door : LevelInfo->LevelDoors)
		{
			if (Door->AdjacentLevel.IsValid())
			{
				bHasNonEmptyDoor = true;
			}
		}
		if (!bHasNonEmptyDoor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level %s has all doors empty"), *LevelInfo->LevelName.ToString());
		}
	}

	if (ACharacter * PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UCharacterMovementComponent * MC = Cast<UCharacterMovementComponent>(PlayerCharacter->GetMovementComponent()))
		{
			if (UPrimitiveComponent * Floor = MC->GetMovementBase())
			{
				ULevel * CurrentLevel = LevelMap.GetCurrentLevel()->LevelStreaming->GetLoadedLevel();
				ULevel * FloorLevel = Cast<ULevel>(Floor->GetOwner()->GetOuter());
				if (CurrentLevel != FloorLevel)
				{
					SetCurrentLevel(FloorLevel);
					LoadAdjacentLevels();
					TrimAdjacentLevels();
				}
			}
		}
	}
}

void ULevelManager::OnStartPlay()
{
	FTransform StartTransform = FTransform(FVector::ZeroVector);
	if (APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		StartTransform = PlayerPawn->GetActorTransform();
	}
	FTransform NewLevelTransform;
	ULevelStreaming * StartingLevel = StreamRandomLevel(StartTransform, FTransform::Identity, NewLevelTransform, true);
	LevelMap.Levels.Empty();
	LevelMap.Levels.Add(GetLevelName(StartingLevel), TSharedPtr<FLevelInfo>(new FLevelInfo(GetLevelName(StartingLevel), StartingLevel, NewLevelTransform)));
	LevelMap.SetCurrentLevel(GetLevelName(StartingLevel));
	LevelMap.GetCurrentLevel()->LevelStreaming->OnLevelShown.AddDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

void ULevelManager::OnFirstLevelLoaded()
{
	LoadAdjacentLevels();
	LevelMap.GetCurrentLevel()->LevelStreaming->OnLevelShown.RemoveDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

ULevelStreaming* ULevelManager::StreamRandomLevel(FTransform LevelTransform, FTransform LevelRelative, FTransform& NewLevelRelative, bool bStartPlay)
{
	UWorld * CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return nullptr;
	}

	TArray<FName> Levels;
	const TArray<ULevelStreaming*> StreamingLevels = CurrentWorld->GetStreamingLevels();
	for (ULevelStreaming* StreamingLevel : StreamingLevels)
	{
		FString LevelName = StreamingLevel->GetWorldAssetPackageName();
		int32 SlashIndex;
		if (LevelName.FindLastChar('/', SlashIndex))
		{
			LevelName = LevelName.RightChop(SlashIndex + 1);
			Levels.Add(*LevelName);
		}
	}

	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = ActionCounter;
	LatentAction.ExecutionFunction = "StreamRandomLevel";

	FRandomStream RandomStream(FPlatformTime::Seconds());

	int32 LevelIndex = RandomStream.RandRange(0, Levels.Num() - 1);
	bool bFoundNewLevel = false;
	int32 LevelCount = 0;
	while (!bFoundNewLevel && LevelCount < Levels.Num() * 2)
	{
		bool bIsAlreadyLoaded = false;
		if (LevelMap.HasLevel(Levels[LevelIndex]))
		{
			bIsAlreadyLoaded = true;
			LevelIndex = RandomStream.RandRange(0, Levels.Num() - 1);
		}

		LevelCount++;
		bFoundNewLevel = !bIsAlreadyLoaded;
	}

	ULevelStreaming* LevelStreaming = nullptr;

	// Choose door
	FTransform DoorTransform = FTransform::Identity;
	ULevelInfoAsset ** LevelAsset = LevelInfoAssets.Find(Levels[LevelIndex].ToString());
	if (LevelAsset)
	{
		if (bStartPlay)
		{
			FVector Diff = LevelTransform.GetLocation() - (*LevelAsset)->LevelSavedInfo.LevelBox.GetCenter();
			DoorTransform = FTransform(Diff);
		}
		else
		{
			FLevelSavedInfo LevelInfo = (*LevelAsset)->LevelSavedInfo;
			int32 DoorIndex = RandomStream.RandRange(0, LevelInfo.DoorTransforms.Num() - 1);

			FTransform NewDoorTransform = LevelInfo.DoorTransforms[DoorIndex];
			float DoorYaw = LevelTransform.GetRotation().Rotator().Yaw - NewDoorTransform.GetRotation().Rotator().Yaw + 180.f;
			FVector DoorLocation = NewDoorTransform.GetLocation();
			FRotator RelativeRot(0.f, DoorYaw, 0.f);
			FVector NewDoorLocation = RelativeRot.RotateVector(DoorLocation);
			FVector CurDoorLocal = LevelTransform.GetLocation() - LevelRelative.GetLocation();
			FVector Relative = CurDoorLocal - NewDoorLocation + LevelRelative.GetLocation();
			DoorTransform.SetLocation(Relative);
			DoorTransform.SetRotation(RelativeRot.Quaternion());
		}
		NewLevelRelative = DoorTransform;
	}
	else
	{
		//error
		return nullptr;
	}

	if (UWorld* World = GetWorld())
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FCustomStreamLevelAction>(LatentAction.CallbackTarget, LatentAction.UUID) == nullptr)
		{
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(true, Levels[LevelIndex], true, false, LatentAction, World);
			if (NewAction->Level)
			{
				NewAction->Level->LevelTransform = DoorTransform;
				LevelStreaming = NewAction->Level;
				ActionCounter++;
			}
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
		}
	}

	return LevelStreaming;
}

void ULevelManager::RegisterDoor(ALevelStreamingDoorPoint * NewDoor)
{
	if (ULevel * DoorLevel = Cast<ULevel>(NewDoor->GetOuter()))
	{
		TSharedPtr<FLevelInfo> DoorLevelInfo = LevelMap.GetLevelMapInfo(DoorLevel);
		if (DoorLevelInfo.IsValid())
		{
			DoorLevelInfo->LevelDoors.Add(TSharedPtr<FLevelDoor>(new FLevelDoor(NewDoor)));

			// get adjacent levels(must be just one) - look through all levels and see if this one is adjacent
			// check all its doors - if one of them has same position, then that level is adjacent
			TArray<TSharedPtr<FLevelInfo>> Levels;
			LevelMap.Levels.GenerateValueArray(Levels);
			for (TSharedPtr<FLevelInfo> Level : Levels)
			{
				if (Level == DoorLevelInfo)
				{
					continue;
				}
				for (TSharedPtr<FLevelDoor> Door : Level->LevelDoors)
				{
					if (Door->AdjacentLevel == DoorLevelInfo)
					{
						for (TSharedPtr<FLevelDoor> DoorsDoor : Level->LevelDoors)
						{
							if ((DoorsDoor->DoorPoint->GetActorLocation() - NewDoor->GetActorLocation()).SizeSquared() <= KINDA_SMALL_NUMBER)
							{
								DoorLevelInfo->LevelDoors.Last()->AdjacentLevel = Level;
							}
						}
					}
				}
			}
		}
	}
}

void ULevelManager::UnloadLevel(FName LevelToUnload)
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = ActionCounter;
	LatentAction.ExecutionFunction = "UnloadLevel";

	if (UWorld* World = GetWorld())
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FCustomStreamLevelAction>(LatentAction.CallbackTarget, LatentAction.UUID) == nullptr)
		{
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(false, LevelToUnload, false, false, LatentAction, World);
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
			ActionCounter++;
			LevelMap.RemoveLevel(LevelToUnload);
		}
	}
}

void ULevelManager::LoadAdjacentLevels()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading adjacent levels"));
	for (TSharedPtr<FLevelDoor> LevelDoor : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		if (!LevelDoor->AdjacentLevel)
		{
			FTransform NewLevelsTransform;
			ULevelStreaming * NewLevel = StreamRandomLevel(LevelDoor->DoorPoint->GetPointTransform(), LevelMap.GetCurrentLevel()->LevelTransform, NewLevelsTransform);
			if (NewLevel)
			{
				UE_LOG(LogTemp, Warning, TEXT("Loading %s"), *GetLevelName(NewLevel).ToString());
				LevelMap.Levels.Add(GetLevelName(NewLevel), TSharedPtr<FLevelInfo>(new FLevelInfo(GetLevelName(NewLevel), NewLevel, NewLevelsTransform)));
				LevelDoor->AdjacentLevel = *LevelMap.Levels.Find(GetLevelName(NewLevel));
			}
		}
	}
}

void ULevelManager::TrimAdjacentLevels()
{
	UE_LOG(LogTemp, Warning, TEXT("Trimming adjacent levels"));
	// get current level, iterate over adjacent, unload their adjacents
	for (TSharedPtr<FLevelDoor> Door : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		TSharedPtr<FLevelInfo> AdjacentLevel = Door->AdjacentLevel;
		if (AdjacentLevel.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Trimming levels of %s"), *AdjacentLevel->LevelName.ToString());
			TArray<TSharedPtr<FLevelDoor>> AdjacentsDoors = AdjacentLevel->LevelDoors;
			for (TSharedPtr<FLevelDoor> AdjacentsDoor : AdjacentsDoors)
			{
				TSharedPtr<FLevelInfo> CurrentLevel = LevelMap.GetCurrentLevel();
				if (AdjacentsDoor->AdjacentLevel && AdjacentsDoor->AdjacentLevel != CurrentLevel)
				{
					FName LevelName = AdjacentsDoor->AdjacentLevel->LevelName;
					UE_LOG(LogTemp, Warning, TEXT("Unloading %s"), *LevelName.ToString());
					if (AdjacentsDoor->AdjacentLevel->LevelDoors.Num() > 0)
					{
						int k = 0;
					}
					AdjacentsDoor->AdjacentLevel->LevelDoors.Empty();
					UnloadLevel(LevelName);
					AdjacentsDoor->AdjacentLevel.Reset();
				}
			}
		}
	}
}

void ULevelManager::SetCurrentLevel(ULevel * InLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("Current level set to %s"), *LevelMap.GetLevelMapInfo(InLevel)->LevelName.ToString());
	LevelMap.SetCurrentLevel(LevelMap.GetLevelMapInfo(InLevel)->LevelName);
}

void ULevelManager::SetNextLevel(ULevelStreaming * Level)
{
	
}

bool ULevelManager::IsCurrentLevel(ULevel * InLevel)
{
	return LevelMap.GetCurrentLevel()->LevelStreaming->GetLoadedLevel() == InLevel;
}

FName ULevelManager::GetLevelName(ULevelStreaming * Level)
{
	FString LevelAssetName = Level->GetWorldAssetPackageName();
	int32 LastSlash;
	LevelAssetName.FindLastChar('/', LastSlash);

	return FName(*LevelAssetName.RightChop(LastSlash + 1));
}