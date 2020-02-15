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
};