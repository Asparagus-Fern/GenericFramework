// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_WorldWidget.h"

#include "WorldWidgetManager.h"
#include "Manager/ManagerProxy.h"

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents()
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents2D()
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents2D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents3D()
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents3D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

UWorldWidgetComponent* UBPFunctions_WorldWidget::FindWorldWidgetComponent(FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->FindWorldWidgetComponent(WorldWidgetTag);
	}

	return nullptr;
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::FindWorldWidgetComponents(FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->FindWorldWidgetComponents(WorldWidgetTag);
	}

	return TArray<UWorldWidgetComponent*>{};
}

void UBPFunctions_WorldWidget::SetWorldWidgetComponentActiveStateWithActor(AActor* InActor, bool IsActive)
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->SetWorldWidgetComponentActiveState(InActor, IsActive);
	}
}

void UBPFunctions_WorldWidget::SetWorldWidgetComponentActiveStateWithComponent(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive)
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->SetWorldWidgetComponentActiveState(InWorldWidgetComponent, IsActive);
	}
}

void UBPFunctions_WorldWidget::SetWorldWidgetPaintMethod(UWorldWidgetComponent* InWorldWidgetComponent, EWorldWidgetPaintMethod WorldWidgetPaintMethod)
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->SetWorldWidgetPaintMethod(InWorldWidgetComponent, WorldWidgetPaintMethod);
	}
}

void UBPFunctions_WorldWidget::SetWorldWidgetLookAtSetting(UWorldWidgetComponent* InWorldWidgetComponent, FWorldWidgetLookAtSetting WorldWidgetLookAtSetting)
{
	if (UWorldWidgetManager* WorldWidgetManager = UManagerProxy::Get()->GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->SetWorldWidgetLookAtSetting(InWorldWidgetComponent, WorldWidgetLookAtSetting);
	}
}
