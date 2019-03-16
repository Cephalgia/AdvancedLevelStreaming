// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/LevelStreaming.h"
#include "LevelStreamingStatics.generated.h"

UCLASS(config = AdvancedLevelStreaming, meta = (DisplayName = "LevelStreamingStatics"))
class ADVANCEDLEVELSTREAMING_API ULevelStreamingStatics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Latent = "", LatentInfo = "LatentInfo"), Category = "Game")
	static void LoadStreamLevelWithTransform(const UObject* WorldContextObject, FName LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo, FTransform LevelTransform);
};
