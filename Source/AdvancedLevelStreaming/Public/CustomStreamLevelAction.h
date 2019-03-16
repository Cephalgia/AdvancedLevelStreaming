// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/LevelStreaming.h"
#include "LatentActions.h"
#include "Engine/CoreSettings.h"

class ADVANCEDLEVELSTREAMING_API FCustomStreamLevelAction : public FPendingLatentAction
{
public:
	bool			bLoading;
	bool			bMakeVisibleAfterLoad;
	bool			bShouldBlockOnLoad;
	ULevelStreaming* Level;
	FName			LevelName;

	FLatentActionInfo LatentInfo;

	FCustomStreamLevelAction(bool bIsLoading, const FName& InLevelName, bool bIsMakeVisibleAfterLoad, bool bIsShouldBlockOnLoad, const FLatentActionInfo& InLatentInfo, UWorld* World);

	/**
	* Given a level name, returns level name that will work with Play on Editor or Play on Console
	*
	* @param	InLevelName		Raw level name (no UEDPIE or UED<console> prefix)
	*/
	static FString MakeSafeLevelName(const FName& InLevelName, UWorld* InWorld);

	/**
	* Helper function to potentially find a level streaming object by name and cache the result
	*
	* @param	LevelName							Name of level to search streaming object for in case Level is NULL
	* @return	level streaming object or NULL if none was found
	*/
	static ULevelStreaming* FindAndCacheLevelStreamingObject(const FName LevelName, UWorld* InWorld);

	/**
	* Handles "Activated" for single ULevelStreaming object.
	*
	* @param	LevelStreamingObject	LevelStreaming object to handle "Activated" for.
	*/
	void ActivateLevel(ULevelStreaming* LevelStreamingObject);
	/**
	* Handles "UpdateOp" for single ULevelStreaming object.
	*
	* @param	LevelStreamingObject	LevelStreaming object to handle "UpdateOp" for.
	*
	* @return true if operation has completed, false if still in progress
	*/
	bool UpdateLevel(ULevelStreaming* LevelStreamingObject);

	virtual void UpdateOperation(FLatentResponse& Response) override;

#if WITH_EDITOR
	// Returns a human readable description of the latent operation's current state
	virtual FString GetDescription() const override;
#endif
};
