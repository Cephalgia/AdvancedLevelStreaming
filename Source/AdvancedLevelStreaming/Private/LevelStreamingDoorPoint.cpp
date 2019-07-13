#include "LevelStreamingDoorPoint.h"
#include "DreamGameMode.h"
#include "LevelManager.h"
#include "Engine/LevelStreaming.h"


ALevelStreamingDoorPoint::ALevelStreamingDoorPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LevelStreamingComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Level Transform"));
	LevelStreamingComponent->SetupAttachment(RootComponent);
	LevelStreamingComponent->bEditableWhenInherited = true;
}

void ALevelStreamingDoorPoint::BeginPlay()
{
	Super::BeginPlay();
	if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ULevelManager * LevelManager = GameMode->LevelManager)
		{
			LevelManager->RegisterDoor(this);
		}
	}
}

FTransform ALevelStreamingDoorPoint::GetPointTransform()
{
	return LevelStreamingPointRelative * GetActorTransform();
}