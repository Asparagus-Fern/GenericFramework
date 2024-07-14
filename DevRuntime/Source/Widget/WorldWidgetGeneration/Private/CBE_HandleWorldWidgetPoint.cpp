// Fill out your copyright notice in the Description page of Project Settings.


#include "CBE_HandleWorldWidgetPoint.h"

#include "WorldWidgetManager.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleWorldWidgetPoint::NativeOnActived()
{
	Super::NativeOnActived();

	for (auto& ActiveHandle : ActiveHandleWorldWidgetPointState)
	{
		if (ActiveHandle.Key.IsValid())
		{
			TArray<AWorldWidgetPoint*> WorldWidgetPoints = GetManager<UWorldWidgetManager>()->GetWorldWidgetPointsByTag(ActiveHandle.Key);
			for (const auto& WorldWidgetPoint : WorldWidgetPoints)
			{
				WorldWidgetPoint->SetIsActive(ActiveHandle.Value);
			}
		}
	}
}

void UCBE_HandleWorldWidgetPoint::NativeOnInactived()
{
	Super::NativeOnInactived();

	for (auto& InactiveHandle : InactiveHandleWorldWidgetPointState)
	{
		if (InactiveHandle.Key.IsValid())
		{
			TArray<AWorldWidgetPoint*> WorldWidgetPoints = GetManager<UWorldWidgetManager>()->GetWorldWidgetPointsByTag(InactiveHandle.Key);
			for (const auto& WorldWidgetPoint : WorldWidgetPoints)
			{
				WorldWidgetPoint->SetIsActive(InactiveHandle.Value);
			}
		}
	}
}
