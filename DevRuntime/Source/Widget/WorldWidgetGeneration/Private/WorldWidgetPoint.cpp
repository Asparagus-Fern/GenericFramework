// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetPoint.h"

#include "WorldWidget.h"
#include "WorldWidgetManager.h"

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

	if (UWorldWidgetManager* WorldWidgetManager = UWorldWidgetManager::Get())
	{
		WorldWidgetManager->AddWorldWidgetPoint(this);
	}
}

void AWorldWidgetPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UWorldWidgetManager* WorldWidgetManager = UWorldWidgetManager::Get())
	{
		WorldWidgetManager->RemoveWorldWidgetPoint(this);
	}
}