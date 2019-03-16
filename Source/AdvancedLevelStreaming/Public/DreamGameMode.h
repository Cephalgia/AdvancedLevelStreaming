// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelManager.h"
#include "DreamGameMode.generated.h"

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "DreamGameMode"))
class ADVANCEDLEVELSTREAMING_API ADreamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADreamGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartPlay() override;

	UPROPERTY()
	ULevelManager * LevelManager = nullptr;
};
