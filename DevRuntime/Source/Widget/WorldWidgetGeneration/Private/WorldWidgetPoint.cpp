// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetPoint.h"

#include "WorldWidget.h"
#include "WorldWidgetManager.h"
#include "Manager/ManagerGlobal.h"

AWorldWidgetPoint::AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWorldWidgetPoint::OnConstruction(const FTransform& Transform)
{
	FWorldWidgetDelegates::OnWorldWidgetPointConstruction.Broadcast(this);
}

void AWorldWidgetPoint::BeginPlay()
{
	Super::BeginPlay();

	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		WorldWidgetManager->AddWorldWidgetPoint(this);
	}
}

void AWorldWidgetPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		WorldWidgetManager->RemoveWorldWidgetPoint(this);
	}
}

void AWorldWidgetPoint::Destroyed()
{
	Super::Destroyed();
	FWorldWidgetDelegates::OnWorldWidgetPointDestroy.Broadcast(this);
}

void AWorldWidgetPoint::SetIsActive(const bool InActive)
{
	PreActiveStateChange.Broadcast(this);
	if (InActive)
	{
		GetManager<UWorldWidgetManager>()->ActiveWorldWidgetPoint(this);
	}
	else
	{
		GetManager<UWorldWidgetManager>()->InactiveWorldWidgetPoint(this);
	}
	OnActiveStateChange.Broadcast(this, InActive);
}
