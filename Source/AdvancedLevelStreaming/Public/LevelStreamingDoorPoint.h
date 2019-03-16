// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "LevelStreamingDoorPoint.generated.h"

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelStreamingDoorPoint"))
class ADVANCEDLEVELSTREAMING_API ALevelStreamingDoorPoint : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	UStaticMeshComponent * DoorStaticMesh;
	// Door component (closing and opening)
	UPROPERTY(EditAnywhere, Category="LevelStreaming")
	FTransform LevelStreamingPointRelative;

	UPROPERTY(VisibleAnywhere, Category="LevelTransform")
	UArrowComponent * LevelStreamingComponent;

public:

	virtual void BeginPlay() override;

	FTransform GetPointTransform();

	bool bLoadedRandom = false;
};
