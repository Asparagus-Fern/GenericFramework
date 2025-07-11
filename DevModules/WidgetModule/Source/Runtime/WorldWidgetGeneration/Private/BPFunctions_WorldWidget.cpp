// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_WorldWidget.h"

#include "WorldWidgetGroupManager.h"
#include "WorldWidgetManager.h"
#include "Manager/ManagerStatics.h"

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents()
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents2D()
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents2D();
	}

	return TArray<UWorldWidgetComponent*>{};
}

TArray<UWorldWidgetComponent*> UBPFunctions_WorldWidget::GetWorldWidgetComponents3D()
{
	if (UWorldWidgetManager* WorldWidgetManager = GetManager<UWorldWidgetManager>())
	{
		return WorldWidgetManager->GetWorldWidgetComponents3D();
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

UGenericButtonGroup* UBPFunctions_WorldWidget::GetWorldWidgetGroup(FGameplayTag InGroupTag)
{
	if (UWorldWidgetGroupManager* WorldWidgetGroupManager = GetManager<UWorldWidgetGroupManager>())
	{
		return WorldWidgetGroupManager->GetWorldWidgetGroup(InGroupTag);
	}
	return nullptr;
}
