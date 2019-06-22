// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LevelManager.h"

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
	Trigger = nullptr;
	LevelDoors.Empty();
}

FLevelInfo * FLevelMap::GetLevelMapInfo(ULevel* InLevel)
{
	if (!InLevel)
	{
		return nullptr;
	}
	for (FLevelInfo &Level: Levels)
	{
		if (InLevel == Level.LevelStreaming->GetLoadedLevel())
		{
			return &Level;
		}
	}
	return nullptr;
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

}

void ULevelManager::OnStartPlay()
{
	ULevelStreaming * StartingLevel = StreamRandomLevel(FTransform(FVector(0.f, 200.f, -90.f)));
	LevelMap.Levels.Empty();
	LevelMap.Levels.Add(FLevelInfo(GetLevelName(StartingLevel), StartingLevel));
	LevelMap.CurrentLevel = &LevelMap.Levels.Last();
	LevelMap.CurrentLevel->LevelStreaming->OnLevelShown.AddDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

void ULevelManager::OnFirstLevelLoaded()
{
	LoadAdjacentLevels(LevelMap.CurrentLevel->Trigger);
	LevelMap.CurrentLevel->LevelStreaming->OnLevelShown.RemoveDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

ULevelStreaming* ULevelManager::StreamRandomLevel(FTransform LevelTransform)
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = ActionCounter;
	LatentAction.ExecutionFunction = "StreamRandomLevel";
	TArray<FName> Levels({ "R_Black_1", "R_Red_1", "R_White_1", "R_Wood_1" });
	int32 LevelIndex = FMath::RandRange(0, Levels.Num() - 1);
	bool bFoundNewLevel = false;
	UWorld * CurrentWorld = GetWorld();
	int32 LevelCount = 0;
	while (!bFoundNewLevel && LevelCount < Levels.Num() * 2)
	{
		bool bIsAlreadyLoaded = false;
		for (ULevel * Level : CurrentWorld->GetLevels())
		{
			if (Level->GetOuter()->GetFName() == Levels[LevelIndex])
			{
				bIsAlreadyLoaded = true;
				LevelIndex = FMath::RandRange(0, Levels.Num() - 1);
				break;
			}
		}
		LevelCount++;
		bFoundNewLevel = !bIsAlreadyLoaded;
	}

	LatentAction.UUID = LevelIndex;
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
		else
		{
			int ohno = 1;
		}
	}

	return LevelStreaming;
}

void ULevelManager::RegisterTrigger(ALevelStreamingTrigger * NewTrigger)
{
	if (ULevel * Level = Cast<ULevel>(NewTrigger->GetOuter()))
	{
		FLevelInfo* TriggerLevelInfo = LevelMap.GetLevelMapInfo(Level);
		TriggerLevelInfo->Trigger = NewTrigger;
	}
}

void ULevelManager::RegisterDoor(ALevelStreamingDoorPoint * NewDoor)
{
	if (ULevel * Level = Cast<ULevel>(NewDoor->GetOuter()))
	{
		if (FLevelInfo* DoorLevelInfo = LevelMap.GetLevelMapInfo(Level))
		{
			DoorLevelInfo->LevelDoors.Add(FLevelDoor(NewDoor));

			// get adjacent levels(must be just one) - look through all levels and see if this one is adjacent
			// check all its doors - if one of them has same position, then that level is adjacent
			FLevelInfo * ParentLevel = nullptr;
			for (FLevelInfo & Level : LevelMap.Levels)
			{
				if (&Level == DoorLevelInfo)
				{
					continue;
				}
				for (FLevelDoor & Door : Level.LevelDoors)
				{
					if (Door.AdjacentLevel == DoorLevelInfo)
					{
						ParentLevel = &Level;
						break;
					}
				}
			}
			if (ParentLevel)
			{
				for (FLevelDoor & Door : ParentLevel->LevelDoors)
				{
					if (Door.DoorPoint->GetActorLocation() == NewDoor->GetActorLocation())
					{
						DoorLevelInfo->LevelDoors.Last().AdjacentLevel = ParentLevel;
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
	LatentAction.UUID = 124;
	LatentAction.ExecutionFunction = "UnloadLevel";

	if (UWorld* World = GetWorld())
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FCustomStreamLevelAction>(LatentAction.CallbackTarget, LatentAction.UUID) == nullptr)
		{
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(false, LevelToUnload, false, false, LatentAction, World);
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
		}
	}
}

void ULevelManager::LoadAdjacentLevels(ALevelStreamingTrigger * NewTrigger)
{
	if (ULevel * Level = Cast<ULevel>(NewTrigger->GetOuter()))
	{
		FLevelInfo * TriggersLevelInfo = LevelMap.GetLevelMapInfo(Level);
		for (FLevelDoor& LevelDoor : TriggersLevelInfo->LevelDoors)
		{
			if (!LevelDoor.AdjacentLevel)
			{
				ULevelStreaming * NewLevel = StreamRandomLevel(LevelDoor.DoorPoint->GetPointTransform());
				if (NewLevel)
				{
					LevelMap.Levels.Add(FLevelInfo(GetLevelName(NewLevel), NewLevel));
					LevelDoor.AdjacentLevel = &LevelMap.Levels.Last();
				}
			}
		}
	}
}

void ULevelManager::TrimAdjacentLevels(ALevelStreamingTrigger * NewTrigger)
{
	// get current level, iterate over adjacent, unload their adjacents
	for (FLevelDoor& Door : LevelMap.CurrentLevel->LevelDoors)
	{
		if (FLevelInfo* AdjacentLevel = Door.AdjacentLevel)
		{
			TArray<FLevelDoor> AdjacentsDoors = AdjacentLevel->LevelDoors;
			for (FLevelDoor& AdjacentsDoor : AdjacentsDoors)
			{
				if (AdjacentsDoor.AdjacentLevel && AdjacentsDoor.AdjacentLevel != LevelMap.CurrentLevel)
				{
					FName LevelName = AdjacentsDoor.AdjacentLevel->LevelName;
					AdjacentsDoor.AdjacentLevel->LevelDoors.Empty();
					AdjacentsDoor.AdjacentLevel->Trigger = nullptr;
					UnloadLevel(LevelName);
				}
			}
			AdjacentLevel->LevelDoors.Empty();
		}
	}
}

void ULevelManager::SetCurrentLevel(ULevel * InLevel)
{
	//LevelMap.CurrentLevel->LevelStreaming = Level;
	//LevelMap.CurrentLevel->LevelName = GetLevelName(Level);
	LevelMap.CurrentLevel = LevelMap.GetLevelMapInfo(InLevel);
}

void ULevelManager::SetNextLevel(ULevelStreaming * Level)
{
	
}

bool ULevelManager::IsCurrentLevel(ULevel * InLevel)
{
	return LevelMap.CurrentLevel->LevelStreaming->GetLoadedLevel() == InLevel;
}

FName ULevelManager::GetLevelName(ULevelStreaming * Level)
{
	FString LevelAssetName = Level->GetWorldAssetPackageName();
	int32 LastSlash;
	LevelAssetName.FindLastChar('/', LastSlash);

	return FName(*LevelAssetName.RightChop(LastSlash + 1));
}