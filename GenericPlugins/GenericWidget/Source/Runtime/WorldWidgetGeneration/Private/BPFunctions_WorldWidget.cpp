// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_WorldWidget.h"

#include "WorldWidgetGroupSubsystem.h"
#include "WorldWidgetSubsystem.h"


TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents(const UObject* WorldContextObject)
{
	if (UWorldWidgetSubsystem* WorldGenericWidgetSubsystem = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldGenericWidgetSubsystem->GetWorldWidgetComponents();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents2D(const UObject* WorldContextObject)
{
	if (UWorldWidgetSubsystem* WorldGenericWidgetSubsystem = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldGenericWidgetSubsystem->GetWorldWidgetComponents2D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents3D(const UObject* WorldContextObject)
{
	if (UWorldWidgetSubsystem* WorldGenericWidgetSubsystem = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldGenericWidgetSubsystem->GetWorldWidgetComponents3D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

UWorldWidgetComponent* UBPFunctions_WorldWidget::FindWorldWidgetComponent(const UObject* WorldContextObject,FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetSubsystem* WorldGenericWidgetSubsystem = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldGenericWidgetSubsystem->FindWorldWidgetComponent(WorldWidgetTag);
	}

	return nullptr;
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::FindWorldWidgetComponents(const UObject* WorldContextObject,FGameplayTag WorldWidgetTag)
{
	if (UWorldWidgetSubsystem* WorldGenericWidgetSubsystem = UWorldWidgetSubsystem::Get(WorldContextObject))
	{
		return WorldGenericWidgetSubsystem->FindWorldWidgetComponents(WorldWidgetTag);
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
