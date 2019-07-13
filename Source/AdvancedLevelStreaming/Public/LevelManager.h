#pragma once
#include "LevelStreamingDoorPoint.h"
#include "LevelManager.generated.h"

class FLevelDoor;

class FLevelInfo
{
public:
	FLevelInfo();
	FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming);

	UPROPERTY()
	ULevelStreaming * LevelStreaming = nullptr;

	FName LevelName;

	UPROPERTY()
	TArray<TSharedPtr<FLevelDoor>> LevelDoors;

	void Reset();
};

class FLevelDoor
{
public:
	FLevelDoor();
	FLevelDoor(ALevelStreamingDoorPoint* InDoorPoint);

	UPROPERTY()
	ALevelStreamingDoorPoint* DoorPoint = nullptr;

	UPROPERTY()
		TSharedPtr<FLevelInfo> AdjacentLevel;
};

class FLevelMap
{
public:
	UPROPERTY()
	TMap<FName, TSharedPtr<FLevelInfo>> Levels;

	TSharedPtr<FLevelInfo> GetLevelMapInfo(ULevel* InLevel);

	bool HasLevel(FName InName);

	void RemoveLevel(FName InLevelName);

	TSharedPtr<FLevelInfo> GetCurrentLevel();

	void SetCurrentLevel(FName InLevelName);
private:
	FName CurrentLevelName;
};

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelManager"))
class ADVANCEDLEVELSTREAMING_API ULevelManager : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void Initialize();

	void OnStartPlay();
	void Tick(float DeltaSeconds);

	void RegisterDoor(ALevelStreamingDoorPoint * NewDoor);

	ULevelStreaming* StreamRandomLevel(FTransform LevelTransform);
	void UnloadLevel(FName LevelToUnload);
	void LoadAdjacentLevels();
	void TrimAdjacentLevels();

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
