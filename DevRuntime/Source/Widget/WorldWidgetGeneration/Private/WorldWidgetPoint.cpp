// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetPoint.h"

#include "WorldWidget.h"
#include "WorldWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Point, "Point");

AWorldWidgetPoint::FWorldWidgetPointDelegate AWorldWidgetPoint::OnWorldWidgetPointConstruct;
AWorldWidgetPoint::FWorldWidgetPointDelegate AWorldWidgetPoint::OnWorldWidgetPointRegister;
AWorldWidgetPoint::FWorldWidgetPointDelegate AWorldWidgetPoint::OnWorldWidgetPointUnRegister;

AWorldWidgetPoint::AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;
}

void AWorldWidgetPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	OnWorldWidgetPointConstruct.Broadcast(this);
}

void AWorldWidgetPoint::BeginPlay()
{
	Super::BeginPlay();
	OnWorldWidgetPointRegister.Broadcast(this);
}

void AWorldWidgetPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnWorldWidgetPointUnRegister.Broadcast(this);
}
