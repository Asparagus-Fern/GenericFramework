// Copyright ChenTaiye 2025. All Rights Reserved.


#include "InteractiveDetectionComponent.h"

UInteractiveDetectionComponent::UInteractiveDetectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SphereRadius = 200.f;
}

void UInteractiveDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractiveDetectionComponent::HandleOnComponentBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractiveDetectionComponent::HandleOnComponentEndOverlap);
}

void UInteractiveDetectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnComponentBeginOverlap.RemoveAll(this);
	OnComponentEndOverlap.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void UInteractiveDetectionComponent::HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(APawn::StaticClass()))
	{
		return;
	}
}

void UInteractiveDetectionComponent::HandleOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
