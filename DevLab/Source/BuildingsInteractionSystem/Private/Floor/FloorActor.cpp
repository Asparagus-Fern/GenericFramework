// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Floor/FloorActor.h"

#include "Building/BuildingActor.h"
#include "Floor/FloorBodyComponent.h"

AFloorActor::AFloorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	FloorBodyComponent = CreateDefaultSubobject<UFloorBodyComponent>("Floor Body");
	FloorBodyComponent->SetupAttachment(SceneComponent);
}

void AFloorActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AFloorActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

ABuildingActor* AFloorActor::GetOwnerBuilding()
{
	return OwnerBuilding.Get();
}

void AFloorActor::SetOwnerBuilding(ABuildingActor* InBuildingActor)
{
	OwnerBuilding = InBuildingActor;
}

void AFloorActor::OnActived_Implementation()
{
	IProcedureInterface::OnActived_Implementation();
	FloorBodyComponent->AddBodyMouseDelegate();
}

void AFloorActor::OnInactived_Implementation()
{
	IProcedureInterface::OnInactived_Implementation();
	FloorBodyComponent->RemoveBodyMouseDelegate();
}

void AFloorActor::HandleBeginCursorOverBody_Implementation(UFloorBodyComponent* BodyComponent)
{
	IFloorBodyInteractionInterface::HandleBeginCursorOverBody_Implementation(BodyComponent);
}

void AFloorActor::HandleEndCursorOverBody_Implementation(UFloorBodyComponent* BodyComponent)
{
	IFloorBodyInteractionInterface::HandleEndCursorOverBody_Implementation(BodyComponent);
}

void AFloorActor::HandleBodyClicked_Implementation(UFloorBodyComponent* BodyComponent)
{
	IFloorBodyInteractionInterface::HandleBodyClicked_Implementation(BodyComponent);
}

void AFloorActor::HandleFloorSelectionChanged_Implementation(bool bIsSelected)
{
	IFloorBodyInteractionInterface::HandleFloorSelectionChanged_Implementation(bIsSelected);
}

bool AFloorActor::GetIsFloorSelected() const
{
	return bIsFloorSelected;
}
