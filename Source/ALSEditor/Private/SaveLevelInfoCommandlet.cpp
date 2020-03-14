#include "SaveLevelInfoCommandlet.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelBounds.h"
#include "Engine/Engine.h"
#include "Modules/ModuleManager.h"
#include "Factories/DataAssetFactory.h"
#include "LevelManager.h"
#include "AssetToolsModule.h"
#include "UObject/UObjectGlobals.h"
#include "ALSConfig.h"

#define LOCTEXT_NAMESPACE "SaveLevelInfoCommandlet"

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
		const TArray<ULevelStreaming*> StreamingLevels = StartingWorld->GetStreamingLevels();

		for (auto Level : StreamingLevels)
		{
			if (UWorld * LevelWorld = Level->GetWorldAsset().LoadSynchronous())
			{
				LevelWorld->InitWorld();
				FURL URL;
				LevelWorld->InitializeActorsForPlay(URL);
				
				SaveLevelInfo(LevelWorld);

				GEngine->DestroyWorldContext(LevelWorld);
				LevelWorld->DestroyWorld(false);
			}
		}

		return 0;
	}


	return 1;
}

void USaveLevelInfoCommandlet::SaveLevelInfo(UWorld * InLevelWorld)
{
	FBox LevelBox = ALevelBounds::CalculateLevelBounds(InLevelWorld->PersistentLevel);
	TArray<FTransform> DoorTransforms;
	TArray<AActor*> Doors;
	UGameplayStatics::GetAllActorsOfClass(InLevelWorld, ALevelStreamingDoorPoint::StaticClass(), Doors);
	for (auto Door : Doors)
	{
		DoorTransforms.Add(Door->GetActorTransform());
	}
	WriteToAsset(InLevelWorld, LevelBox, DoorTransforms);
	
}

void USaveLevelInfoCommandlet::WriteToAsset(UWorld * InLevelWorld, FBox InLevelBox, TArray<FTransform> InDoorTransforms)
{
	FString PathName = InLevelWorld->GetPathName();
	int32 SlashIndex = -1;
	PathName.FindLastChar('/', SlashIndex);
	PathName = PathName.LeftChop(PathName.Len() - SlashIndex - 1);
	PathName += "Data/LevelData";
	UPackage * Package = CreatePackage(nullptr, *PathName);
	check(Package);
	Package->FullyLoad();
	Package->Modify();
	ULevelInfoAsset * LevelAsset = NewObject<ULevelInfoAsset>(Package, ULevelInfoAsset::StaticClass(), "LevelInfo", RF_Public | RF_Standalone);
	LevelAsset->LevelSavedInfo.LevelBox = InLevelBox;
	LevelAsset->LevelSavedInfo.DoorTransforms = InDoorTransforms;
	FString const PackageFileName = FPackageName::LongPackageNameToFilename(*Package->GetName(), FPackageName::GetAssetPackageExtension());

	UPackage::SavePackage(Package, NULL, RF_Standalone, *PackageFileName, GError, nullptr, false, true, SAVE_NoError);
}

void USaveLevelInfoCommandlet::OnLevelLoaded()
{
	LevelNumber++;
	if (LevelNumber == MaxLevelNumber)
	{

	}
}

#undef LOCTEXT_NAMESPACE