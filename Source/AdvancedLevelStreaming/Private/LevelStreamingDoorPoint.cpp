// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LevelStreamingDoorPoint.h"
#include "LevelStreamingStatics.h"
#include "Engine/Level.h"
#include "DreamGameMode.h"
#include "LevelManager.h"
#include "Engine/LevelStreaming.h"


ALevelStreamingDoorPoint::ALevelStreamingDoorPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>();
	LevelStreamingComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Level Transform"));
	LevelStreamingComponent->SetupAttachment(RootComponent);
	LevelStreamingComponent->bEditableWhenInherited = true;
}

void ALevelStreamingDoorPoint::BeginPlay()
{
	Super::BeginPlay();
	if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ULevelManager * LevelManager = GameMode->LevelManager)
		{
			LevelManager->RegisterDoor(this);
		}
	}
}

FTransform ALevelStreamingDoorPoint::GetPointTransform()
{
	return LevelStreamingPointRelative * GetActorTransform();
}