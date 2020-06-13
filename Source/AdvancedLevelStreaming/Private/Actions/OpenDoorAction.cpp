#pragma once
#include "Actions/OpenDoorAction.h"
#include "LevelStreamingDoorPoint.h"
#include "InteractionComponent.h"


UOpenDoorAction::UOpenDoorAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UOpenDoorAction::PerformAction(UInteractionComponent * InComponent)
{
	if (ALevelStreamingDoorPoint * Door = Cast<ALevelStreamingDoorPoint>(InComponent->GetOwner()))
	{
		Door->OpenDoor();
	}
}