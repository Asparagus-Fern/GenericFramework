// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor/FloorActor.h"

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

void AFloorActor::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
}

void AFloorActor::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
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
