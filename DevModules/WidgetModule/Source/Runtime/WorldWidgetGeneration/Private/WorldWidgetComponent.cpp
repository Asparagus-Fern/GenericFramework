// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetComponent.h"

#include "DWidgetComponent.h"
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

void UWorldWidgetComponent::OnHiddenInGameChanged()
{
	Super::OnHiddenInGameChanged();
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

		WorldWidget->SetIsActived(true);
	}

	WidgetComponent->RequestRenderUpdate();
}

void UWorldWidgetComponent::ClearWidgetComponent()
{
	if (WidgetComponent)
	{
		WidgetComponent->DestroyComponent();
		WidgetComponent = nullptr;

		if (WorldWidget)
		{
			WorldWidget->SetIsActived(false);
			
		}
	}
}

UWidgetComponent* UWorldWidgetComponent::CreateWidgetComponent()
{
	UDWidgetComponent* Result = Cast<UDWidgetComponent>(GetOwner()->AddComponentByClass(UDWidgetComponent::StaticClass(), false, FTransform::Identity, false));
	Result->SetWidgetSpace(EWidgetSpace::World);
	Result->SetDrawAtDesiredSize(false);
	Result->SetBlendMode(EWidgetBlendMode::Transparent);
	Result->SetTintColorAndOpacity(FLinearColor::White);
	Result->SetManuallyRedraw(true);

	if (UMaterialInstance* Material = LoadObject<UMaterialInstance>(NULL,TEXT("/Script/Engine.MaterialInstanceConstant'/WidgetModule/Material/Widget3DPassThrough_Translucent_OneSided.Widget3DPassThrough_Translucent_OneSided'")))
	{
		Result->SetMaterial(0, Material);
		Material->GetMaterial()->bDisableDepthTest = bAlwaysInFront;
	}

	return Result;
}
