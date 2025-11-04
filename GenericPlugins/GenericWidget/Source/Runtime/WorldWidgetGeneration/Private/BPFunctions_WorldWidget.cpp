// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_WorldWidget.h"

#include "WorldWidgetGroupSubsystem.h"
#include "WorldWidgetSubsystem.h"


TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents(const UObject* WorldContextObject)
{
	if (UWorldWidgetSubsystem* WorldWidgetManager = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldWidgetManager->GetWorldWidgetComponents();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents2D(const UObject* WorldContextObject)
{
	if (UWorldWidgetSubsystem* WorldWidgetManager = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldWidgetManager->GetWorldWidgetComponents2D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents3D(const UObject* WorldContextObject)
{
	if (UWorldWidgetSubsystem* WorldWidgetManager = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldWidgetManager->GetWorldWidgetComponents3D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

UWorldWidgetComponent* UBPFunctions_WorldWidget::FindWorldWidgetComponent(const UObject* WorldContextObject,FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetSubsystem* WorldWidgetManager = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldWidgetManager->FindWorldWidgetComponent(WorldWidgetTag);
	}

	return nullptr;
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::FindWorldWidgetComponents(const UObject* WorldContextObject,FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetSubsystem* WorldWidgetManager = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldWidgetManager->FindWorldWidgetComponents(WorldWidgetTag);
	}

	return TArray<UWorldWidgetComponent*>{};
}

UGenericButtonGroup* UBPFunctions_WorldWidget::GetWorldWidgetGroup(const UObject* WorldContextObject,FGameplayTag InGroupTag)
{
	if (UWorldWidgetGroupSubsystem* WorldWidgetGroupManager = UWorldWidgetGroupSubsystem::Get(WorldContextObject))
	{
		return WorldWidgetGroupManager->GetWorldWidgetGroup(InGroupTag);
	}
	return nullptr;
}
