// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetComponent.h"

#include "Base/UserWidgetBase.h"
#include "Components/WidgetComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_WorldWidget, "UI.WorldWidget");

UWorldWidgetComponent::UWorldWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWorldWidgetComponent::OnRegister()
{
	Super::OnRegister();
	OnWorldWidgetComponentRegister.Broadcast(this);
}

void UWorldWidgetComponent::OnUnregister()
{
	OnWorldWidgetComponentUnRegister.Broadcast(this);
	Super::OnUnregister();
}

void UWorldWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	OnWorldWidgetPointBeginPlay.Broadcast(this);
}

void UWorldWidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnWorldWidgetPointEndPlay.Broadcast(this);
}

void UWorldWidgetComponent::RefreshWidgetComponent()
{
	ClearWidgetComponent();
	WidgetComponent = CreateWidgetComponent();

	if (WorldWidget)
	{
		WidgetComponent->SetPivot(WorldWidget->Anchor);
		WidgetComponent->SetWidget(WorldWidget);
		WidgetComponent->SetDrawSize(WorldWidget->GetDesiredSize());
	}

	WidgetComponent->RequestRenderUpdate();
}

void UWorldWidgetComponent::ClearWidgetComponent()
{
	if (WidgetComponent)
	{
		WidgetComponent->DestroyComponent();
		WidgetComponent = nullptr;
	}
}

UWidgetComponent* UWorldWidgetComponent::CreateWidgetComponent()
{
	UWidgetComponent* Result = Cast<UWidgetComponent>(GetOwner()->AddComponentByClass(UWidgetComponent::StaticClass(), false, FTransform::Identity, false));
	Result->SetWidgetSpace(EWidgetSpace::World);
	Result->SetDrawAtDesiredSize(false);
	Result->SetBlendMode(EWidgetBlendMode::Transparent);
	Result->SetTintColorAndOpacity(FLinearColor::White);
	Result->SetManuallyRedraw(true);

	return Result;
}
