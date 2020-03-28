// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#pragma once

#include "UObject/Object.h"
#include "ALSConfig.generated.h"

UCLASS(config = Game, defaultconfig)
class ADVANCEDLEVELSTREAMING_API UALSConfig : public UObject
{
	GENERATED_BODY()

public:
	UALSConfig(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {};

	UPROPERTY(config, EditAnywhere, Category = Maps, meta = (AllowedClasses = "World"))
	FSoftObjectPath StartingMap;

	UPROPERTY(config, EditAnywhere, Category = Maps, meta = (AllowedClasses = "LevelInfoAsset"))
	FSoftObjectPath LInfo;
};
