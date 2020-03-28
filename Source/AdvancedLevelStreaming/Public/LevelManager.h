#pragma once
#include "Engine/DataAsset.h"

#include "LevelStreamingDoorPoint.h"
#include "LevelManager.generated.h"

class FLevelDoor;

USTRUCT()
struct FLevelSavedInfo 
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category="Info")
	FBox LevelBox;

	// Door transfroms relative to the zero point
	UPROPERTY(VisibleAnywhere, Category = "Info")
	TArray<FTransform> DoorTransforms;
};

/**
 * Items Database DataAsset, here we can save all of our game items
 */
UCLASS()
class ADVANCEDLEVELSTREAMING_API ULevelInfoAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Info")
	FLevelSavedInfo LevelSavedInfo;

};

class FLevelInfo
{
public:
	FLevelInfo();
	FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming, FTransform InLevelTransform);

	UPROPERTY()
	ULevelStreaming * LevelStreaming = nullptr;

	FName LevelName;

	UPROPERTY()
	TArray<TSharedPtr<FLevelDoor>> LevelDoors;

	FTransform LevelTransform;

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

	ULevelStreaming* StreamRandomLevel(FTransform LevelTransform, FTransform LevelRelative, FTransform& NewLevelRelative, bool bStartPlay = false);
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

	UPROPERTY()
	TMap<FString, ULevelInfoAsset *> LevelInfoAssets;
};
