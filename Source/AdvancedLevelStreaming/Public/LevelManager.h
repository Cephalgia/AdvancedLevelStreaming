// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "LevelStreamingTrigger.h"
#include "LevelStreamingDoorPoint.h"
#include "LevelManager.generated.h"

//class ALevelStreamingDoorPoint;
//class ALevelStreamingTrigger;

USTRUCT()
struct FLevelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	ULevelStreaming * LevelStreaming;

	FName LevelName;

	ALevelStreamingTrigger* Trigger;

	ALevelStreamingDoorPoint* DoorPoint;

	void Reset();
};

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelManager"))
class ADVANCEDLEVELSTREAMING_API ULevelManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void Initialize();

	void OnStartPlay();

	void RegisterTrigger(ALevelStreamingTrigger * NewTrigger);
	void RegisterDoor(ALevelStreamingDoorPoint * NewDoor);

	ULevelStreaming* StreamRandomLevel(FTransform LevelTransform);
	void UnloadLevel();
	void StreamNextLevel();

	void SetCurrentLevel(ULevelStreaming * Level);
	void SetNextLevel(ULevelStreaming * Level);

private:
	FLevelInfo CurrentLevel;

	FLevelInfo NextLevel;

	FName GetLevelName(ULevelStreaming * Level);
};
