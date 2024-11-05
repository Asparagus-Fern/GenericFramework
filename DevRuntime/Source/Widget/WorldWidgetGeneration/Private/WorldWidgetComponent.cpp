// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_WorldWidget, "UI.WorldWidget");

UWorldWidgetComponent::FWorldWidgetComponentDelegate UWorldWidgetComponent::OnWorldWidgetComponentRegister;
UWorldWidgetComponent::FWorldWidgetComponentDelegate UWorldWidgetComponent::OnWorldWidgetPointBeginPlay;
UWorldWidgetComponent::FWorldWidgetComponentDelegate UWorldWidgetComponent::OnWorldWidgetPointEndPlay;

UWorldWidgetComponent::UWorldWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWorldWidgetComponent::OnRegister()
{
	Super::OnRegister();
	OnWorldWidgetComponentRegister.Broadcast(this);
}

void UWorldWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bIsAutoRegister)
	{
		OnWorldWidgetPointBeginPlay.Broadcast(this);
	}
}

void UWorldWidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnWorldWidgetPointEndPlay.Broadcast(this);
}
