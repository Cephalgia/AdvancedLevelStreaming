// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LevelManager.h"

void FLevelInfo::Reset()
{
	LevelStreaming = nullptr;
	LevelName = "";
	Trigger = nullptr;
	DoorPoint = nullptr;
}

ULevelManager::ULevelManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULevelManager::Initialize()
{

}

void ULevelManager::OnStartPlay()
{
	ULevelStreaming * StartingLevel = StreamRandomLevel(FTransform(FVector(0.f, 200.f, -90.f)));
	SetCurrentLevel(StartingLevel);
}

ULevelStreaming* ULevelManager::StreamRandomLevel(FTransform LevelTransform)
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = 123;
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
			}
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
		}
	}

	return LevelStreaming;
}

void ULevelManager::RegisterTrigger(ALevelStreamingTrigger * NewTrigger)
{
	if (CurrentLevel.LevelStreaming->GetLoadedLevel() == NewTrigger->GetOuter())
	{ 
		CurrentLevel.Trigger = NewTrigger;
	}
	else if (NextLevel.LevelStreaming && NextLevel.LevelStreaming->GetLoadedLevel() == NewTrigger->GetOuter())
	{
		NextLevel.Trigger = NewTrigger;
	}
}

void ULevelManager::RegisterDoor(ALevelStreamingDoorPoint * NewDoor)
{
	if (CurrentLevel.LevelStreaming->GetLoadedLevel() == NewDoor->GetOuter())
	{
		CurrentLevel.DoorPoint = NewDoor;
	}
	else if (NextLevel.LevelStreaming && NextLevel.LevelStreaming->GetLoadedLevel() == NewDoor->GetOuter())
	{
		NextLevel.DoorPoint = NewDoor;
	}
}

void ULevelManager::UnloadLevel()
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
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(false, CurrentLevel.LevelName, false, false, LatentAction, World);
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
		}
	}

	CurrentLevel = NextLevel;

	NextLevel.Reset();
}

void ULevelManager::StreamNextLevel()
{
	if (CurrentLevel.DoorPoint && !CurrentLevel.DoorPoint->bLoadedRandom)
	{
		FTransform LevelTransform = CurrentLevel.DoorPoint->GetPointTransform();
		if (ULevelStreaming * NewLevelStreaming = StreamRandomLevel(LevelTransform))
		{
			SetNextLevel(NewLevelStreaming);
			CurrentLevel.DoorPoint->bLoadedRandom = true;
		}
	}
}

void ULevelManager::SetCurrentLevel(ULevelStreaming * Level)
{
	CurrentLevel.LevelStreaming = Level;
	CurrentLevel.LevelName = GetLevelName(Level);
}

void ULevelManager::SetNextLevel(ULevelStreaming * Level)
{
	NextLevel.LevelStreaming = Level;
	NextLevel.LevelName = GetLevelName(Level);
}

FName ULevelManager::GetLevelName(ULevelStreaming * Level)
{
	FString LevelAssetName = Level->GetWorldAssetPackageName();
	int32 LastSlash;
	LevelAssetName.FindLastChar('/', LastSlash);

	return FName(*LevelAssetName.RightChop(LastSlash + 1));
}