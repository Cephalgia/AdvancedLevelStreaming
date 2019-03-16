// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/TriggerVolume.h"
#include "LevelStreamingTrigger.generated.h"

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelStreamingTrigger"))
class ADVANCEDLEVELSTREAMING_API ALevelStreamingTrigger : public ATriggerVolume
{
	GENERATED_UCLASS_BODY()

	bool bLoaded = false;
public:
	UFUNCTION()
	void OnBeginOverlap(AActor *OverlappingActor, AActor *OtherActor);
	UFUNCTION()
	void OnEndOverlap(AActor *OverlappingActor, AActor *OtherActor);
	virtual void BeginPlay() override;
};
