#include "LevelStreamingDoorPoint.h"
#include "DreamGameMode.h"
#include "LevelManager.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

ALevelStreamingDoorPoint::ALevelStreamingDoorPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LevelStreamingComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Level Transform"));
	LevelStreamingComponent->SetupAttachment(RootComponent);
	LevelStreamingComponent->bEditableWhenInherited = true;

	bRelevantForLevelBounds = false;
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelStreamingDoorPoint::BeginPlay()
{
	Super::BeginPlay();
	DoorStaticMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (ULevelManager * LevelManager = GameMode->GetManager<ULevelManager>())
		{
			if (LevelManager->RegisterDoor(this))
			{
				bLocked = false;
			}
		}
	}

	if (ULevel * DoorLevel = Cast<ULevel>(GetOuter()))
	{
		if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (ULevelManager * LevelManager = GameMode->GetManager<ULevelManager>())
			{
				if (!LevelManager->IsCurrentLevel(DoorLevel))
				{
					DoorStaticMesh->SetVisibility(false);
					DoorStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					for (auto Component : GetComponents())
					{
						Component->PrimaryComponentTick.SetTickFunctionEnable(false);
					}
				}
			}
		}
	}
}

void ALevelStreamingDoorPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!DoorStaticMesh || !PlayerPawn)
	{
		return;
	}
	float DistanceToPlayerSq = (GetActorLocation() - PlayerPawn->GetActorLocation()).SizeSquared2D();
	if (FMath::Abs(CurrentAngle - TargetAngle) > 1.f)
	{
		CurrentAngle = FMath::FInterpConstantTo(CurrentAngle, TargetAngle, DeltaTime, 100.f);
		FRotator CurrentRotation = DoorStaticMesh->GetRelativeRotation();
		//DoorStaticMesh->MoveComponent(FVector::ZeroVector, FRotator(CurrentRotation.Pitch, CurrentAngle, CurrentRotation.Roll), false);
		DoorStaticMesh->SetRelativeRotation(FRotator(CurrentRotation.Pitch, CurrentAngle, CurrentRotation.Roll));

		UE_LOG(LogTemp, Warning, TEXT("CURRENT ANGLE %f, REAL %f"), CurrentAngle, DoorStaticMesh->GetComponentRotation().Yaw);
	}
	else if (FMath::Abs(CurrentAngle - TargetAngle) < 1.f && CurrentAngle != TargetAngle)
	{
		CurrentAngle = TargetAngle;
	}
	else if (TargetAngle != 0.f)
	{
		if (DistanceToPlayerSq > FMath::Square(600.f))
		{
			UE_LOG(LogTemp, Warning, TEXT("CLOSING DOOR"));
			TargetAngle = 0.f;
		}
	}
	if (bTryEnable && DistanceToPlayerSq > FMath::Square(50.f))
	{
		bTryEnable = false;
		EnableDoor();
	}

	/*float Radius = 20.f;
	if (!DoorStaticMesh->IsVisible())
	{
		Radius = 10.f;
	}
	FColor DebugColor = bLocked ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), GetActorLocation() + FVector(0.f, 0.f, 60.f), Radius, 8, DebugColor);*/
}

void ALevelStreamingDoorPoint::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	//OpenDoor();
}

void ALevelStreamingDoorPoint::OpenDoor()
{
	if (!bLocked && CurrentAngle == 0.f)
	{
		bool bSide = false; // check if current level is door level, if true - TargetAngle will be +90, else -90
		if (ULevel * DoorLevel = Cast<ULevel>(GetOuter()))
		{
			if (ADreamGameMode * GameMode = Cast<ADreamGameMode>(GetWorld()->GetAuthGameMode()))
			{
				if (ULevelManager * LevelManager = GameMode->GetManager<ULevelManager>())
				{
					bSide = LevelManager->IsCurrentLevel(DoorLevel);
				}
			}
		}
		TargetAngle = bSide ? 90.f : -90.f;
		UE_LOG(LogTemp, Warning, TEXT("OPENING DOOR %f"), TargetAngle);
	}
}

FTransform ALevelStreamingDoorPoint::GetPointTransform()
{
	return LevelStreamingPointRelative * GetActorTransform();
}

void ALevelStreamingDoorPoint::OnDoorLevelShown()
{
	bLocked = false;
}

void ALevelStreamingDoorPoint::EnableDoor()
{
	if (APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		if ((GetActorLocation() - PlayerPawn->GetActorLocation()).SizeSquared2D() > FMath::Square(50.f))
		{
			DoorStaticMesh->SetVisibility(true);
			DoorStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			bTryEnable = true;
		}

		for (auto Component : GetComponents())
		{
			Component->PrimaryComponentTick.SetTickFunctionEnable(true);
		}
	}
}

void ALevelStreamingDoorPoint::DisableDoor()
{
	DoorStaticMesh->SetVisibility(false);
	DoorStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	for (auto Component : GetComponents())
	{
		Component->PrimaryComponentTick.SetTickFunctionEnable(false);
	}
}