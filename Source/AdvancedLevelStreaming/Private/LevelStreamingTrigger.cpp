// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LevelStreamingTrigger.h"
#include "EngineUtils.h"
#include "CustomStreamLevelAction.h"
#include "DreamGameMode.h"
#include "LevelManager.h"

ALevelStreamingTrigger::ALevelStreamingTrigger(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OnActorBeginOverlap.AddDynamic(this, &ALevelStreamingTrigger::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ALevelStreamingTrigger::OnEndOverlap);
}

void ALevelStreamingTrigger::BeginPlay()
{
	Super::BeginPlay();
	if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ULevelManager * LevelManager = GameMode->LevelManager)
		{
			LevelManager->RegisterTrigger(this);
		}
	}
}

void ALevelStreamingTrigger::OnBeginOverlap(AActor *OverlappingActor, AActor *OtherActor)
{
	// set level as current
	if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ULevelManager * LevelManager = GameMode->LevelManager)
		{
			if (ULevel * Level = Cast<ULevel>(GetOuter()))
			{
				LevelManager->SetCurrentLevel(Level);
				LevelManager->TrimAdjacentLevels(this);
				LevelManager->LoadAdjacentLevels(this);
			}
		}
	}
	/*if (!bLoaded)
	{
		if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (ULevelManager * LevelManager = GameMode->LevelManager)
			{
				LevelManager->StreamNextLevel();
			}
		}
	}*/
}

void ALevelStreamingTrigger::OnEndOverlap(AActor *OverlappingActor, AActor *OtherActor)
{
	if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ULevelManager * LevelManager = GameMode->LevelManager)
		{
			//LevelManager->UnloadLevel();
		}
	}
}