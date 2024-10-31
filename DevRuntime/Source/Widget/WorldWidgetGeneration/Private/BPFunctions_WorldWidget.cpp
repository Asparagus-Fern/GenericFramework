// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_WorldWidget.h"

#include "WorldWidgetManager.h"
#include "Manager/ManagerGlobal.h"

void UBPFunctions_WorldWidget::RegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		WorldWidgetManager->RegisterWorldWidgetPoint(WorldWidgetPoint);
	}
}

void UBPFunctions_WorldWidget::UnRegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		WorldWidgetManager->UnRegisterWorldWidgetPoint(WorldWidgetPoint);
	}
}

TArray<AWorldWidgetPoint*> UBPFunctions_WorldWidget::GetWorldWidgetPoints()
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetPoints();
	}

	return TArray<AWorldWidgetPoint*>{};
}

AWorldWidgetPoint* UBPFunctions_WorldWidget::FindWorldWidgetPoint(FGameplayTag PointTag)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->FindWorldWidgetPoint(PointTag);
	}

	return nullptr;
}

TArray<AWorldWidgetPoint*> UBPFunctions_WorldWidget::FindWorldWidgetPoints(FGameplayTag PointTag)
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->FindWorldWidgetPoints(PointTag);
	}

	return TArray<AWorldWidgetPoint*>{};
}
