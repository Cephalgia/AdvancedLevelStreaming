
#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomStreamLevelAction.h"
#include "Engine/LevelBounds.h"
#include "ALSConfig.h"
#include "DrawDebugHelpers.h"

FLevelDoor::FLevelDoor()
{

}

FLevelDoor::FLevelDoor(ALevelStreamingDoorPoint* InDoorPoint)
{
	DoorPoint = InDoorPoint;
}

FLevelInfo::FLevelInfo()
{

}

FLevelInfo::FLevelInfo(FName InName, ULevelStreaming * InLevelStreaming, FTransform InLevelTransform, FName InLevelType)
{
	LevelName = InName;
	LevelStreaming = InLevelStreaming;
	LevelTransform = InLevelTransform;
	LevelType = InLevelType;
}

void FLevelInfo::Reset()
{
	LevelStreaming = nullptr;
	LevelName = "";
	LevelDoors.Empty();
}

TSharedPtr<FLevelInfo> FLevelMap::GetLevelMapInfo(ULevel* InLevel)
{
	if (!InLevel)
	{
		return TSharedPtr<FLevelInfo>();
	}
	FName LevelName = InLevel->GetOuter()->GetFName();
	TSharedPtr<FLevelInfo> * FoundLevel = Levels.Find(LevelName);
	return FoundLevel ? *FoundLevel : TSharedPtr<FLevelInfo>();
}

bool FLevelMap::HasLevel(FName InName)
{
	TSharedPtr<FLevelInfo>* FoundLevel = Levels.Find(InName);
	bool bHasLevel = false;
	TArray<FName> LevelNames;
	Levels.GenerateKeyArray(LevelNames);
	bHasLevel = LevelNames.Contains(InName);
	bool AnotherHasLevel = FoundLevel != nullptr;
	return AnotherHasLevel;
}

void FLevelMap::RemoveLevel(FName InLevelName)
{
	Levels.Remove(InLevelName);
}

TSharedPtr<FLevelInfo> FLevelMap::GetCurrentLevel() const
{
	const TSharedPtr<FLevelInfo> * FoundLevel = Levels.Find(CurrentLevelName);
	return FoundLevel ? *FoundLevel : TSharedPtr<FLevelInfo>();
}

void FLevelMap::SetCurrentLevel(FName InLevelName)
{
	CurrentLevelName = InLevelName;
	UE_LOG(LogTemp, Warning, TEXT("CurrentLevel set to %s"), *InLevelName.ToString());
}

ULevelManager::ULevelManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULevelManager::Initialize()
{
	UWorld * CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	TArray<FName> Levels;
	TArray<FString> LevelPaths;
	const TArray<ULevelStreaming*> StreamingLevels = CurrentWorld->GetStreamingLevels();
	for (ULevelStreaming* StreamingLevel : StreamingLevels)
	{
		FString WorldAssetPackage = StreamingLevel->GetWorldAssetPackageName();
		int32 SlashIndex;
		if (WorldAssetPackage.FindLastChar('/', SlashIndex))
		{
			FString LevelName = WorldAssetPackage.RightChop(SlashIndex + 1);
			FString AssetName = LevelName + "_Data";
			FSoftObjectPath LevelAssetName = WorldAssetPackage.LeftChop(WorldAssetPackage.Len() - SlashIndex) + "/" + AssetName + "." + AssetName;
			if (ULevelInfoAsset * LevelAsset = Cast<ULevelInfoAsset>(LevelAssetName.TryLoad()))
			{
				LevelInfoAssets.Add(*LevelName, LevelAsset);
			}
		}
	}


}

void ULevelManager::Tick(float DeltaSeconds)
{
	if (ACharacter * PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (UCharacterMovementComponent * MC = Cast<UCharacterMovementComponent>(PlayerCharacter->GetMovementComponent()))
		{
			if (UPrimitiveComponent * Floor = MC->GetMovementBase())
			{
				ULevel * CurrentLevel = LevelMap.GetCurrentLevel()->LevelStreaming->GetLoadedLevel();
				ULevel * FloorLevel = Cast<ULevel>(Floor->GetOwner()->GetOuter());
				if (CurrentLevel != FloorLevel)
				{
					SetCurrentLevel(FloorLevel);

					//NextRoomType = RoomTypeProgress >= GetDefault<UALSConfig>()->MinRoomsPerType ? GetNewRoomType() : CurrentRoomType;

					LoadAdjacentLevels();
					TrimAdjacentLevels();
				}
			}
		}
	}
}

void ULevelManager::OnStartPlay()
{
	FTransform StartTransform = FTransform(FVector::ZeroVector);
	if (APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		StartTransform = PlayerPawn->GetActorTransform();
	}
	FTransform NewLevelTransform;
	ULevelStreaming * StartingLevel = StreamRandomLevel(TSharedPtr<FLevelDoor>(), FTransform::Identity, NewLevelTransform, true);
	LevelMap.Levels.Empty();
	ULevelInfoAsset ** LevelInfo = LevelInfoAssets.Find(GetLevelName(StartingLevel));
	FName LevelType = LevelInfo != nullptr ? (*LevelInfo)->LevelSavedInfo.LevelType : NAME_None;
	LevelMap.Levels.Add(GetLevelName(StartingLevel), TSharedPtr<FLevelInfo>(new FLevelInfo(GetLevelName(StartingLevel), StartingLevel, NewLevelTransform, LevelType)));
	LevelMap.SetCurrentLevel(GetLevelName(StartingLevel));
	LevelMap.GetCurrentLevel()->LevelStreaming->OnLevelShown.AddDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

void ULevelManager::OnFirstLevelLoaded()
{
	SetCurrentLevel(LevelMap.GetCurrentLevel()->LevelStreaming->GetLoadedLevel());
	LoadAdjacentLevels();
	LevelMap.GetCurrentLevel()->LevelStreaming->OnLevelShown.RemoveDynamic(this, &ULevelManager::OnFirstLevelLoaded);
}

ULevelStreaming* ULevelManager::StreamRandomLevel(TSharedPtr<FLevelDoor> LevelDoor, FTransform LevelRelative, FTransform& NewLevelRelative, bool bStartPlay)
{
	UWorld * CurrentWorld = GetWorld();
	APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!CurrentWorld || !PlayerPawn)
	{
		return nullptr;
	}
	FTransform LevelTransform = LevelDoor.IsValid() ? LevelDoor->DoorPoint->GetPointTransform() : PlayerPawn->GetActorTransform();

	TArray<FName> Levels;
	LevelInfoAssets.GenerateKeyArray(Levels);
	//eliminate loaded levels
	Levels = Levels.FilterByPredicate([this, LevelDoor](const FName& LevelName) 
	{ 
		bool bIsLoaded = LevelMap.Levels.Find(LevelName) != nullptr;

		ULevelInfoAsset ** LevelInfo = LevelInfoAssets.Find(LevelName);
		bool bTypeAvailable = *LevelInfo != nullptr;
		if (CurrentRoomType != NAME_None)
		{
			FName LevelRoomType = (*LevelInfo)->LevelSavedInfo.LevelType;
			if (RoomTypeProgress >= GetDefault<UALSConfig>()->MinRoomsPerType)
			{
				bTypeAvailable = GetNewRoomTypes().Contains(LevelRoomType);
			}
			else
			{
				bTypeAvailable = LevelRoomType == CurrentRoomType;
			}
		}

		bool bIsTypeStrengthFitting = CurrentRoomType == NAME_None;
		if (!bIsTypeStrengthFitting)
		{
			int32 DoorLevelTypeStr = LevelDoor->DoorPoint->TypeStrength;
			bIsTypeStrengthFitting = (*LevelInfo)->LevelSavedInfo.DoorStrengths.Contains(DoorLevelTypeStr);
		}

		return !bIsLoaded && bTypeAvailable && bIsTypeStrengthFitting;
	});
	//shuffle remaining array
	FRandomStream RandomStream(FPlatformTime::Seconds());
	for (int i = Levels.Num() - 1; i > 0; --i)
	{
		int j = RandomStream.RandRange(0, i);
		FName Buffer = Levels[i];
		Levels[i] = Levels[j];
		Levels[j] = Buffer;
	}

	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = ActionCounter;
	LatentAction.ExecutionFunction = "StreamRandomLevel";

	//select first fitting level
	FTransform DoorTransform = FTransform::Identity;
	FName ChosenLevel = NAME_None;
	for (FName LevelName : Levels)
	{
		ULevelInfoAsset ** LevelAsset = LevelInfoAssets.Find(LevelName);
		if (LevelAsset)
		{
			FBox LevelBox = (*LevelAsset)->LevelSavedInfo.LevelBox;
			if (bStartPlay)
			{
				ChosenLevel = LevelName;
				FVector Diff = LevelTransform.GetLocation() - (*LevelAsset)->LevelSavedInfo.LevelBox.GetCenter();
				DoorTransform = FTransform(Diff);
			}
			else
			{
				TArray<FTransform> DoorTransforms;
				for (int i = 0; i < (*LevelAsset)->LevelSavedInfo.DoorTransforms.Num(); ++i)
				{
					if ((*LevelAsset)->LevelSavedInfo.DoorStrengths[i] == LevelDoor->DoorPoint->TypeStrength)
					{
						DoorTransforms.Add((*LevelAsset)->LevelSavedInfo.DoorTransforms[i]);
					}
				}

				if (DoorTransforms.Num() == 0)
				{
					continue;
				}

				//shuffle door array
				for (int i = DoorTransforms.Num() - 1; i > 0; --i)
				{
					int j = RandomStream.RandRange(0, i);
					FTransform Buffer = DoorTransforms[i];
					DoorTransforms[i] = DoorTransforms[j];
					DoorTransforms[j] = Buffer;
				}

				for (FTransform NewDoorTransform : DoorTransforms)
				{
					float DoorYaw = LevelTransform.GetRotation().Rotator().Yaw - NewDoorTransform.GetRotation().Rotator().Yaw + 180.f;
					FVector DoorLocation = NewDoorTransform.GetLocation();
					FRotator RelativeRot(0.f, DoorYaw, 0.f);
					FVector NewDoorLocation = RelativeRot.RotateVector(DoorLocation);
					FVector CurDoorLocal = LevelTransform.GetLocation() - LevelRelative.GetLocation();
					FVector Relative = CurDoorLocal - NewDoorLocation + LevelRelative.GetLocation();
					DoorTransform.SetLocation(Relative);
					DoorTransform.SetRotation(RelativeRot.Quaternion());

					FBox CheckBox = TransformLevelBox(LevelBox, DoorTransform);

					LevelBox = LevelBox.ExpandBy(-12.f);
					TArray<TSharedPtr<FLevelInfo>> LoadedLevelsInfo;
					LevelMap.Levels.GenerateValueArray(LoadedLevelsInfo);
					bool bIntersectsAnything = false;
					for (TSharedPtr<FLevelInfo> LevelInfo : LoadedLevelsInfo)
					{
						FBox OtherBounds;
						ULevelInfoAsset ** OtherLevelAsset = LevelInfoAssets.Find(LevelInfo->LevelName);
						if (OtherLevelAsset)
						{
							OtherBounds = (*OtherLevelAsset)->LevelSavedInfo.LevelBox;
							FTransform OtherTransform = LevelInfo->LevelStreaming->LevelTransform;
							OtherBounds = TransformLevelBox(OtherBounds, OtherTransform);
							if (CheckBox.Intersect(OtherBounds))
							{
								//DrawDebugBox(GetWorld(), CheckBox.GetCenter(), CheckBox.GetExtent(), FColor::Red, false, 80.f);
								bIntersectsAnything = true;
							}
						}
					}

					if (!bIntersectsAnything)
					{
						ChosenLevel = LevelName;
						NewLevelRelative = DoorTransform;
						break;
					}
				}
			}

			if (ChosenLevel != NAME_None)
			{
				break;
			}
		}
		else
		{
			return nullptr;
		}
	}

	if (ChosenLevel == NAME_None)
	{
		return nullptr;
	}

	ULevelStreaming* LevelStreaming = nullptr;

	if (UWorld* World = GetWorld())
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FCustomStreamLevelAction>(LatentAction.CallbackTarget, LatentAction.UUID) == nullptr)
		{
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(true, ChosenLevel, true, false, LatentAction, World);
			if (NewAction->Level)
			{
				NewAction->Level->LevelTransform = DoorTransform;
				LevelStreaming = NewAction->Level;
				ActionCounter++;
			}
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
		}
	}

	return LevelStreaming;
}

bool ULevelManager::RegisterDoor(ALevelStreamingDoorPoint * NewDoor)
{
	if (ULevel * DoorLevel = Cast<ULevel>(NewDoor->GetOuter()))
	{
		TSharedPtr<FLevelInfo> DoorLevelInfo = LevelMap.GetLevelMapInfo(DoorLevel);
		if (DoorLevelInfo.IsValid())
		{
			DoorLevelInfo->LevelDoors.Add(TSharedPtr<FLevelDoor>(new FLevelDoor(NewDoor)));

			// get adjacent levels(must be just one) - look through all levels and see if this one is adjacent
			// check all its doors - if one of them has same position, then that level is adjacent
			TArray<TSharedPtr<FLevelInfo>> Levels;
			LevelMap.Levels.GenerateValueArray(Levels);
			for (TSharedPtr<FLevelInfo> Level : Levels)
			{
				if (Level == DoorLevelInfo)
				{
					continue;
				}
				for (TSharedPtr<FLevelDoor> Door : Level->LevelDoors)
				{
					if (Door->AdjacentLevel == DoorLevelInfo)
					{
						for (TSharedPtr<FLevelDoor> DoorsDoor : Level->LevelDoors)
						{
							if ((DoorsDoor->DoorPoint->GetActorLocation() - NewDoor->GetActorLocation()).SizeSquared() <= FMath::Square(10.f))
							{
								DoorLevelInfo->LevelDoors.Last()->AdjacentLevel = Level;
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void ULevelManager::UnloadLevel(FName LevelToUnload)
{
	FLatentActionInfo LatentAction;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = ActionCounter;
	LatentAction.ExecutionFunction = "UnloadLevel";

	if (UWorld* World = GetWorld())
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FCustomStreamLevelAction>(LatentAction.CallbackTarget, LatentAction.UUID) == nullptr)
		{
			FCustomStreamLevelAction* NewAction = new FCustomStreamLevelAction(false, LevelToUnload, false, false, LatentAction, World);
			LatentManager.AddNewAction(LatentAction.CallbackTarget, LatentAction.UUID, NewAction);
			ActionCounter++;
			LevelMap.RemoveLevel(LevelToUnload);
		}
	}
}

void ULevelManager::LoadAdjacentLevels()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading adjacent levels"));
	for (TSharedPtr<FLevelDoor> LevelDoor : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		if (!LevelDoor->AdjacentLevel)
		{
			FTransform NewLevelsTransform;
			ULevelStreaming * NewLevel = StreamRandomLevel(LevelDoor, LevelMap.GetCurrentLevel()->LevelTransform, NewLevelsTransform);
			if (NewLevel)
			{
				UE_LOG(LogTemp, Warning, TEXT("Loading %s"), *GetLevelName(NewLevel).ToString());
				ULevelInfoAsset ** LevelInfo = LevelInfoAssets.Find(GetLevelName(NewLevel));
				FName LevelType = LevelInfo != nullptr ? (*LevelInfo)->LevelSavedInfo.LevelType : NAME_None;
				LevelMap.Levels.Add(GetLevelName(NewLevel), TSharedPtr<FLevelInfo>(new FLevelInfo(GetLevelName(NewLevel), NewLevel, NewLevelsTransform, LevelType)));
				LevelDoor->AdjacentLevel = *LevelMap.Levels.Find(GetLevelName(NewLevel));
				NewLevel->OnLevelShown.AddUniqueDynamic(LevelDoor->DoorPoint, &ALevelStreamingDoorPoint::OnDoorLevelShown);
			}
		}
	}
}

void ULevelManager::TrimAdjacentLevels()
{
	UE_LOG(LogTemp, Warning, TEXT("Trimming adjacent levels"));
	// get current level, iterate over adjacent, unload their adjacents
	for (TSharedPtr<FLevelDoor> Door : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		TSharedPtr<FLevelInfo> AdjacentLevel = Door->AdjacentLevel;
		if (AdjacentLevel.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Trimming levels of %s"), *AdjacentLevel->LevelName.ToString());
			TArray<TSharedPtr<FLevelDoor>> AdjacentsDoors = AdjacentLevel->LevelDoors;
			for (TSharedPtr<FLevelDoor> AdjacentsDoor : AdjacentsDoors)
			{
				TSharedPtr<FLevelInfo> CurrentLevel = LevelMap.GetCurrentLevel();
				if (AdjacentsDoor->AdjacentLevel && AdjacentsDoor->AdjacentLevel != CurrentLevel)
				{
					FName LevelName = AdjacentsDoor->AdjacentLevel->LevelName;
					UE_LOG(LogTemp, Warning, TEXT("Unloading %s"), *LevelName.ToString());
					AdjacentsDoor->AdjacentLevel->LevelDoors.Empty();
					UnloadLevel(LevelName);
					AdjacentsDoor->AdjacentLevel.Reset();
					AdjacentsDoor->DoorPoint->bLocked = true;
				}
			}
		}
	}
}

void ULevelManager::SetCurrentLevel(ULevel * InLevel)
{
	for (auto LevelDoor : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		LevelDoor->DoorPoint->DisableDoor();
	}

	FName NewLevelType = LevelMap.GetLevelMapInfo(InLevel)->LevelType;
	if (CurrentRoomType == NAME_None || NewLevelType != LevelMap.GetCurrentLevel()->LevelType)
	{
		CurrentRoomType = NewLevelType;
		RoomTypeProgress = 1;
	}
	else
	{
		RoomTypeProgress++;
	}

	UE_LOG(LogTemp, Warning, TEXT("Current level set to %s"), *LevelMap.GetLevelMapInfo(InLevel)->LevelName.ToString());
	LevelMap.SetCurrentLevel(LevelMap.GetLevelMapInfo(InLevel)->LevelName);

	for (auto LevelDoor : LevelMap.GetCurrentLevel()->LevelDoors)
	{
		LevelDoor->DoorPoint->EnableDoor();
	}
}

void ULevelManager::SetNextLevel(ULevelStreaming * Level)
{
	
}

bool ULevelManager::IsCurrentLevel(ULevel * InLevel) const
{
	return GetCurrentLevel() == InLevel;
}

ULevel * ULevelManager::GetCurrentLevel() const
{
	return LevelMap.GetCurrentLevel()->LevelStreaming->GetLoadedLevel();
}

FName ULevelManager::GetLevelName(ULevelStreaming * Level)
{
	FString LevelAssetName = Level->GetWorldAssetPackageName();
	int32 LastSlash;
	LevelAssetName.FindLastChar('/', LastSlash);

	return FName(*LevelAssetName.RightChop(LastSlash + 1));
}

FBox ULevelManager::TransformLevelBox(FBox InBox, FTransform InTransform)
{
	InBox.Min = InTransform.TransformVector(InBox.Min) + InTransform.GetLocation();
	InBox.Max = InTransform.TransformVector(InBox.Max) + InTransform.GetLocation();
	FVector Center = InBox.GetCenter();
	FVector Extent = InBox.GetExtent();
	Extent = Extent.GetAbs();
	InBox.Min = Center - Extent;
	InBox.Max = Center + Extent;
	return InBox;
}

TArray<FName> ULevelManager::GetNewRoomTypes() const
{
	TArray<FName> AvailableTypes = GetDefault<UALSConfig>()->RoomTypes;
	AvailableTypes = AvailableTypes.FilterByPredicate([this](const FName& Type) { return Type != CurrentRoomType; });
	return AvailableTypes;
}