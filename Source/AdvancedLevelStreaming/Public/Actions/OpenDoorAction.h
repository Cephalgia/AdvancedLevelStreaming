#pragma once
#include "InteractionAction.h"
#include "OpenDoorAction.generated.h"

UCLASS(BlueprintType, EditInlineNew, config = AdvancedLevelStreaming, meta = (DisplayName = "OpenDoorAction"))
class ADVANCEDLEVELSTREAMING_API UOpenDoorAction : public UInteractionAction
{
	GENERATED_UCLASS_BODY()	

public:
	virtual void PerformAction(UInteractionComponent * InComponent) override;
};
