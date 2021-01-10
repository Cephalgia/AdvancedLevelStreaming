#pragma once
#include "Engine/DataAsset.h"

#include "ManagerBase.h"

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

	UPROPERTY(VisibleAnywhere, Category = "Info")
	TArray<int32> DoorStrengths;

	UPROPERTY(VisibleAnywhere, Category = "Info")
	FName LevelType;

	UPROPERTY(EditAnywhere, Category = "Info")
	int TypeStrength;
};

/**
 * Items Database DataAsset, here we can save all of our game items
 */
UCLASS()
class ADVANCEDLEVELSTREAMING_API ULevelInfoAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Info")
	FLevelSavedInfo LevelSavedInfo;

};

class FLevelInfo
{
public:
	FLevelInfo();
	FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming, FTransform InLevelTransform, FName InLevelType);

	UPROPERTY()
	ULevelStreaming * LevelStreaming = nullptr;

	FName LevelName;

	UPROPERTY()
	TArray<TSharedPtr<FLevelDoor>> LevelDoors;

	FTransform LevelTransform;

	FName LevelType;

	int TypeStrength;

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

	TSharedPtr<FLevelInfo> GetCurrentLevel() const;

	void SetCurrentLevel(FName InLevelName);
private:
	FName CurrentLevelName;
};

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelManager"))
class ADVANCEDLEVELSTREAMING_API ULevelManager : public UManagerBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Initialize() override;

	virtual void OnStartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	bool RegisterDoor(ALevelStreamingDoorPoint * NewDoor);

	ULevelStreaming* StreamRandomLevel(TSharedPtr<FLevelDoor> LevelDoor, FTransform LevelRelative, FTransform& NewLevelRelative, bool bStartPlay = false);
	void UnloadLevel(FName LevelToUnload);
	void LoadAdjacentLevels();
	void TrimAdjacentLevels();

	void SetCurrentLevel(ULevel * InLevel);
	void SetNextLevel(ULevelStreaming * Level);

	bool IsCurrentLevel(ULevel * InLevel) const;
	ULevel * GetCurrentLevel() const;

	FBox TransformLevelBox(FBox InBox, FTransform InTransform);

	TArray<FName> GetNewRoomTypes() const;

private:
	FLevelMap LevelMap;

	FName GetLevelName(ULevelStreaming * Level);

	UFUNCTION()
	void OnFirstLevelLoaded();

	int32 ActionCounter = 0;

	FName CurrentRoomType;
	int32 RoomTypeProgress = 1;
	FName NextRoomType;

	UPROPERTY()
	TMap<FName, ULevelInfoAsset *> LevelInfoAssets;
};
