// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "GameHUDManager.h"
#include "WorldWidgetComponent.h"
#include "Base/UserWidgetBase.h"

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

bool UWorldWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWorldWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UWorldWidgetComponent::OnWorldWidgetComponentRegister.AddUObject(this, &UWorldWidgetManager::RegisterWorldWidgetComponent);
	UWorldWidgetComponent::OnWorldWidgetComponentUnRegister.AddUObject(this, &UWorldWidgetManager::UnRegisterWorldWidgetComponent);
}

void UWorldWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UWorldWidgetComponent::OnWorldWidgetComponentRegister.RemoveAll(this);
	UWorldWidgetComponent::OnWorldWidgetComponentUnRegister.RemoveAll(this);
}

bool UWorldWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWorldWidgetManager::RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
	}

	if (WorldWidgetComponents.Contains(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetPoint Is Already Register"))
	}

	WorldWidgetComponents.Add(InWorldWidgetComponent);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWorldWidgetComponentRegister, BPDelegate_OnWorldWidgetComponentRegister, InWorldWidgetComponent);
}

void UWorldWidgetManager::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
	}

	if (WorldWidgetComponents.Contains(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetPoint Is Already UnRegister"))
	}

	WorldWidgetComponents.Remove(InWorldWidgetComponent);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWorldWidgetComponentUnRegister, BPDelegate_OnWorldWidgetComponentUnRegister, InWorldWidgetComponent);
}

TArray<UWorldWidgetComponent*> UWorldWidgetManager::GetWorldWidgetComponents2D()
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

TArray<UWorldWidgetComponent*> UWorldWidgetManager::GetWorldWidgetComponents3D()
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

UWorldWidgetComponent* UWorldWidgetManager::FindWorldWidgetComponent(const FGameplayTag WorldWidgetTag)
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

TArray<UWorldWidgetComponent*> UWorldWidgetManager::FindWorldWidgetComponents(FGameplayTag WorldWidgetTag)
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
