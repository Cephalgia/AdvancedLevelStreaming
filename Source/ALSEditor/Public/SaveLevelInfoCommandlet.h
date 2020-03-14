#pragma once

#include "Commandlets/Commandlet.h"

#include "SaveLevelInfoCommandlet.generated.h"


UCLASS()
class USaveLevelInfoCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:

	/** Default constructor. */
	USaveLevelInfoCommandlet();

public:

	//~ UCommandlet interface

	virtual int32 Main(const FString& Params) override;

	int32 LevelNumber;
	int32 MaxLevelNumber;

	UFUNCTION()
	void OnLevelLoaded();

private:
	void SaveLevelInfo(UWorld * InLevelWorld);
	void WriteToAsset(UWorld * InLevelWorld, FBox InLevelBox, TArray<FTransform> InDoorTransforms);
};