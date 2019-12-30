
#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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

FLevelInfo::FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming)
{
	LevelName = InName;
	LevelStreaming = InLevelStreaming;
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

}

void ULevelManager::Tick(float DeltaSeconds)
{
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
	ULevelStreaming * StartingLevel = StreamRandomLevel(FTransform(FVector(0.f, 200.f, -90.f)));
	LevelMap.Levels.Empty();
	LevelMap.Levels.Add(GetLevelName(StartingLevel), TSharedPtr<FLevelInfo>(new FLevelInfo(GetLevelName(StartingLevel), StartingLevel)));
	LevelMap.SetCurrentLevel(GetLevelName(StartingLevel));
	LevelMap.GetCurrentLevel()->LevelStreaming->OnLevelShown.AddDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

void ULevelManager::OnFirstLevelLoaded()
{
	LoadAdjacentLevels();
	LevelMap.GetCurrentLevel()->LevelStreaming->OnLevelShown.RemoveDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

ULevelStreaming* ULevelManager::StreamRandomLevel(FTransform LevelTransform)
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = ActionCounter;
	LatentAction.ExecutionFunction = "StreamRandomLevel";
	TArray<FName> Levels({ "R_Black_1", "R_Red_1", "R_White_1", "R_Wood_1", "R_Black_2", "R_Red_2", "R_White_2", "R_Wood_2" });
	int32 LevelIndex = FMath::RandRange(0, Levels.Num() - 1);
	bool bFoundNewLevel = false;
	UWorld * CurrentWorld = GetWorld();
	int32 LevelCount = 0;
	while (!bFoundNewLevel && LevelCount < Levels.Num() * 2)
	{
		bool bIsAlreadyLoaded = false;
		if (LevelMap.HasLevel(Levels[LevelIndex]))
		{
			bIsAlreadyLoaded = true;
			LevelIndex = FMath::RandRange(0, Levels.Num() - 1);
		}

		LevelCount++;
		bFoundNewLevel = !bIsAlreadyLoaded;
	}

	ULevelStreaming* LevelStreaming = nullptr;

	if (UWorld* World = GetWorld())
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FCustomStreamLevelAction>(LatentAction.CallbackTarget, LatentAction.UUID) == nullptr)
		{
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(true, Levels[LevelIndex], true, false, LatentAction, World);
			if (NewAction->Level)
			{
				NewAction->Level->LevelTransform = LevelTransform;
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
							if (DoorsDoor->DoorPoint->GetActorLocation() == NewDoor->GetActorLocation())
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
	for (TSharedPtr<FLevelDoor> LevelDoor : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		if (!LevelDoor->AdjacentLevel)
		{
			ULevelStreaming * NewLevel = StreamRandomLevel(LevelDoor->DoorPoint->GetPointTransform());
			if (NewLevel)
			{
				LevelMap.Levels.Add(GetLevelName(NewLevel), TSharedPtr<FLevelInfo>(new FLevelInfo(GetLevelName(NewLevel), NewLevel)));
				LevelDoor->AdjacentLevel = *LevelMap.Levels.Find(GetLevelName(NewLevel));
			}
		}
	}
}

void ULevelManager::TrimAdjacentLevels()
{
	// get current level, iterate over adjacent, unload their adjacents
	for (TSharedPtr<FLevelDoor> Door : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		TSharedPtr<FLevelInfo> AdjacentLevel = Door->AdjacentLevel;
		if (AdjacentLevel.IsValid())
		{
			TArray<TSharedPtr<FLevelDoor>> AdjacentsDoors = AdjacentLevel->LevelDoors;
			for (TSharedPtr<FLevelDoor> AdjacentsDoor : AdjacentsDoors)
			{
				TSharedPtr<FLevelInfo> CurrentLevel = LevelMap.GetCurrentLevel();
				if (AdjacentsDoor->AdjacentLevel && AdjacentsDoor->AdjacentLevel != CurrentLevel)
				{
					FName LevelName = AdjacentsDoor->AdjacentLevel->LevelName;
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