// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_WorldWidget.h"

#include "WorldWidgetManager.h"
#include "WorldWidgetPoint.h"
#include "Manager/ManagerGlobal.h"

void UBPFunctions_WorldWidget::RegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	RegisterWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
}

void UBPFunctions_WorldWidget::UnRegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	UnRegisterWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
}

void UBPFunctions_WorldWidget::RegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		WorldWidgetManager->RegisterWorldWidgetComponent(WorldWidgetComponent);
	}
}

void UBPFunctions_WorldWidget::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		WorldWidgetManager->UnRegisterWorldWidgetComponent(WorldWidgetComponent);
	}
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents()
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents();
	}

	return TArray<UWorldWidgetComponent*>{};
}

UWorldWidgetComponent* UBPFunctions_WorldWidget::FindWorldWidgetComponent(FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->FindWorldWidgetComponent(WorldWidgetTag);
	}

	return nullptr;
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::FindWorldWidgetComponents(FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->FindWorldWidgetComponents(WorldWidgetTag);
	}

	return TArray<UWorldWidgetComponent*>{};
}
