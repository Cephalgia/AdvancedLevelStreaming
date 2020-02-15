#include "SaveLevelInfoCommandlet.h"
#include "Engine/World.h"
#include "ALSConfig.h"

USaveLevelInfoCommandlet::USaveLevelInfoCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}


int32 USaveLevelInfoCommandlet::Main(const FString& Params)
{
	if (UWorld * StartingWorld = Cast<UWorld>(GetDefault<UALSConfig>()->StartingMap.TryLoad()))
	{
		StartingWorld->GetStreamingLevels();

		return 0;
	}


	return 1;
}