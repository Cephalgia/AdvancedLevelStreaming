// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "LevelStreamingTrigger.h"
#include "LevelStreamingDoorPoint.h"
#include "LevelManager.generated.h"

//class ALevelStreamingDoorPoint;
//class ALevelStreamingTrigger;

class FLevelDoor;


class FLevelInfo
{
	//GENERATED_BODY()
public:
	FLevelInfo();
	FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming);

	UPROPERTY()
	ULevelStreaming * LevelStreaming = nullptr;

	FName LevelName;

	// trigger is for detecting whether the player has left/entered the level
	// maybe i should change it to checking the level of the floor the player is standing on to allow non-square rooms
	UPROPERTY()
	ALevelStreamingTrigger* Trigger = nullptr;

	UPROPERTY()
	TArray<FLevelDoor> LevelDoors;

	void Reset();
};


//UCLASS()
class FLevelDoor
{
	//GENERATED_BODY()

public:
	FLevelDoor();
	FLevelDoor(ALevelStreamingDoorPoint* InDoorPoint);

	UPROPERTY()
	ALevelStreamingDoorPoint* DoorPoint = nullptr;

	UPROPERTY()
	FLevelInfo* AdjacentLevel = nullptr;
};

//UCLASS()
class FLevelMap
{
	//GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FLevelInfo> Levels;

	UPROPERTY()
	FLevelInfo * CurrentLevel = nullptr;

	FLevelInfo * GetLevelMapInfo(ULevel* InLevel);
};

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelManager"))
class ADVANCEDLEVELSTREAMING_API ULevelManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void Initialize();

	void OnStartPlay();
	void Tick(float DeltaSeconds);

	void RegisterTrigger(ALevelStreamingTrigger * NewTrigger);
	void RegisterDoor(ALevelStreamingDoorPoint * NewDoor);

	ULevelStreaming* StreamRandomLevel(FTransform LevelTransform);
	void UnloadLevel(FName LevelToUnload);
	void LoadAdjacentLevels(ALevelStreamingTrigger * NewTrigger);
	void TrimAdjacentLevels(ALevelStreamingTrigger * NewTrigger);

	void SetCurrentLevel(ULevel * InLevel);
	void SetNextLevel(ULevelStreaming * Level);

	bool IsCurrentLevel(ULevel * InLevel);

private:
	FLevelMap LevelMap;

	FName GetLevelName(ULevelStreaming * Level);

	UFUNCTION()
	void OnFirstLevelLoaded();

	int32 ActionCounter = 0;
};
