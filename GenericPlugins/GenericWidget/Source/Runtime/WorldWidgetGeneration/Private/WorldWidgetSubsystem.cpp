// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WorldWidgetSubsystem.h"

#include "WidgetType.h"
#include "WorldWidgetComponent.h"
#include "Base/GenericWidget.h"
#include "Type/DebugType.h"
#include "Type/GenericType.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetGenerationModule"

UWorldWidgetSubsystem* UWorldWidgetSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UWorldWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UWorldWidgetComponent::OnWorldWidgetComponentRegister.AddUObject(this, &UWorldWidgetSubsystem::RegisterWorldWidgetComponent);
	UWorldWidgetComponent::OnWorldWidgetComponentUnRegister.AddUObject(this, &UWorldWidgetSubsystem::UnRegisterWorldWidgetComponent);
}

void UWorldWidgetSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UWorldWidgetComponent::OnWorldWidgetComponentRegister.RemoveAll(this);
	UWorldWidgetComponent::OnWorldWidgetComponentUnRegister.RemoveAll(this);
}

void UWorldWidgetSubsystem::RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	if (WorldWidgetComponents.Contains(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("WorldWidgetPoint Is Already Register"))
		return;
	}

	WorldWidgetComponents.Add(InWorldWidgetComponent);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWorldWidgetComponentRegister, BPDelegate_OnWorldWidgetComponentRegister, InWorldWidgetComponent);
}

void UWorldWidgetSubsystem::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	if (WorldWidgetComponents.Contains(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("WorldWidgetPoint Is Already UnRegister"))
		return;
	}

	WorldWidgetComponents.Remove(InWorldWidgetComponent);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWorldWidgetComponentUnRegister, BPDelegate_OnWorldWidgetComponentUnRegister, InWorldWidgetComponent);
}

TArray<UWorldWidgetComponent*> UWorldWidgetSubsystem::GetWorldWidgetComponents2D()
{
	TArray<UWorldWidgetComponent*> WorldWidget2D;
	for (auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		if (WorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen)
		{
			WorldWidget2D.Add(WorldWidgetComponent);
		}
	}
	return WorldWidget2D;
}

TArray<UWorldWidgetComponent*> UWorldWidgetSubsystem::GetWorldWidgetComponents3D()
{
	TArray<UWorldWidgetComponent*> WorldWidget2D;
	for (auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		if (WorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld)
		{
			WorldWidget2D.Add(WorldWidgetComponent);
		}
	}
	return WorldWidget2D;
}

UWorldWidgetComponent* UWorldWidgetSubsystem::FindWorldWidgetComponent(const FGameplayTag WorldWidgetTag)
{
	for (const auto& WorldWidgetPoint : WorldWidgetComponents)
	{
		if (WorldWidgetPoint->WorldWidgetTag == WorldWidgetTag)
		{
			return WorldWidgetPoint;
		}
	}

	return nullptr;
}

TArray<UWorldWidgetComponent*> UWorldWidgetSubsystem::FindWorldWidgetComponents(FGameplayTag WorldWidgetTag)
{
	TArray<UWorldWidgetComponent*> Result;

	for (const auto& WorldWidgetPoint : WorldWidgetComponents)
	{
		if (WorldWidgetPoint->WorldWidgetTag.MatchesTag(WorldWidgetTag))
		{
			Result.Add(WorldWidgetPoint);
		}
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE
