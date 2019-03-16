// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DreamGameMode.h"
#include "LevelManager.h"
#include "LevelStreamingStatics.h"

ADreamGameMode::ADreamGameMode()
	: Super()
{
}

void ADreamGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	LevelManager = NewObject<ULevelManager>(this);
	LevelManager->Initialize();
}

void ADreamGameMode::StartPlay()
{
	LevelManager->OnStartPlay();
	Super::StartPlay();;
}

