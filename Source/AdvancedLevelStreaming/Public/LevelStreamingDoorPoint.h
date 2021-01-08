#pragma once
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "LevelStreamingDoorPoint.generated.h"

UCLASS(BlueprintType, config = AdvancedLevelStreaming, meta = (DisplayName = "LevelStreamingDoorPoint"))
class ADVANCEDLEVELSTREAMING_API ALevelStreamingDoorPoint : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	UStaticMeshComponent * DoorStaticMesh;

	UPROPERTY(EditAnywhere, Category="LevelStreaming")
	FTransform LevelStreamingPointRelative;

	UPROPERTY(VisibleAnywhere, Category="LevelTransform")
	UArrowComponent * LevelStreamingComponent;

	UPROPERTY(EditAnywhere, Category = "LevelProperties")
	int TypeStrength = 0;

	bool bLocked = true; // can it open at the moment

public:

	virtual void BeginPlay() override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void Tick(float DeltaTime) override;

	FTransform GetPointTransform();

	UFUNCTION()
	void OnDoorLevelShown();

	void EnableDoor();
	void DisableDoor();

	void OpenDoor();

protected:
	bool bActive; // this door is visible
	bool bTryEnable = false; // if player is standing near it, try enabling next tick

	float CurrentAngle = 0.f;
	float TargetAngle = 0.f;
	float InterpSpeed = 0.5f;
};
