// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "ScreenWidgetManager.h"
#include "WorldWidgetComponent.h"
#include "WorldWidgetManagerSetting.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager/ManagerProxy.h"
#include "UWidget/Override/GameplayTagSlot.h"

void UWorldWidgetPanel::NativeOnCreate()
{
	Super::NativeOnCreate();
}

void UWorldWidgetPanel::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	if (!IsValid(CanvasPanel) || !IsValid(GetWorld()))
	{
		return;
	}

	for (const auto& WorldWidget : WorldWidgets)
	{
		/* 对每个Player单独做世界位置转屏幕位置的计算 */
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			FVector2D ScreenPosition;
			APlayerController* PlayerController = Iterator->Get();

			/* 映射位置到所有PlayerController */
			if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, WorldWidget.Key->GetComponentLocation(), ScreenPosition, false))
			{
				if (UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(WorldWidget.Value))
				{
					/* 最终的位置 */
					const FVector2D ResultPosition = ScreenPosition + WorldWidget.Value->GetAnchorOffset();

					int32 ViewportSizeX;
					int32 ViewportSizeY;
					PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

					/* 可显示区域根据WorldWidget的大小而定，会比屏幕大小略大一些，水平方向为当前屏幕X大小左右外扩WorldWidget的SizeX距离，垂直方向为当前屏幕Y上下外扩WorldWidget的SizeY距离，才能保证WorldWidget在边缘处被正确显示而不是被折叠 */
					if ((ResultPosition.X > -WorldWidget.Value->GetDesiredSize().X) && (ResultPosition.X < ViewportSizeX) && (ResultPosition.Y > -WorldWidget.Value->GetDesiredSize().Y) && (ResultPosition.Y < ViewportSizeY))
					{
						WorldWidget.Value->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						CanvasPanelSlot->SetPosition(ResultPosition);
						continue;
					}
				}
			}

			/* 其余情况均折叠WorldWidget */
			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UWorldWidgetPanel::NativeOnDestroy()
{
	Super::NativeOnDestroy();
	WorldWidgets.Reset();
}

void UWorldWidgetPanel::HandleAddToViewport()
{
	const FGameplayTag WorldWidgetPanelTag = FGameplayTag::RequestGameplayTag(FName("UI.HUD.Main.WorldWidget"));
	if (WorldWidgetPanelTag.IsValid())
	{
		UGameplayTagSlot* Slot = UManagerProxy::Get()->GetManager<UScreenWidgetManager>()->GetSlot(WorldWidgetPanelTag);
		if (IsValid(Slot))
		{
			Slot->SetContent(CanvasPanel);
		}
	}
}

void UWorldWidgetPanel::HandleRemoveFromViewport()
{
	CanvasPanel->RemoveFromParent();
}

bool UWorldWidgetPanel::IsContain(UWorldWidgetComponent* InWorldWidgetComponent)
{
	for (const auto& WorldWidget : WorldWidgets)
	{
		if (WorldWidget.Key == InWorldWidgetComponent)
		{
			return true;
		}
	}

	return false;
}

void UWorldWidgetPanel::AddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (IsValid(InWorldWidgetComponent) && !WorldWidgets.Contains(InWorldWidgetComponent))
	{
		WorldWidgets.FindOrAdd(InWorldWidgetComponent, InWorldWidgetComponent->WorldWidget);

		if (IsValid(CanvasPanel))
		{
			UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel->AddChildToCanvas(InWorldWidgetComponent->WorldWidget);
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetAnchors(FAnchors());
			CanvasPanelSlot->SetAlignment(FVector2D());
			CanvasPanelSlot->SetOffsets(FMargin());
			CanvasPanelSlot->SetZOrder(InWorldWidgetComponent->WorldWidget->ZOrder);
		}
	}
}

void UWorldWidgetPanel::RemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (IsValid(InWorldWidgetComponent) && WorldWidgets.Contains(InWorldWidgetComponent))
	{
		if (IsValid(CanvasPanel))
		{
			CanvasPanel->RemoveChild(WorldWidgets.FindRef(InWorldWidgetComponent));
		}

		WorldWidgets.Remove(InWorldWidgetComponent);
	}
}

void UWorldWidgetPanel::RefreshWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	RemoveWorldWidgetComponent(InWorldWidgetComponent);
	AddWorldWidgetComponent(InWorldWidgetComponent);
}

void UWorldWidgetPanel::RefreshAllWorldWidgetComponent()
{
	CanvasPanel->ClearChildren();

	for (const auto& WorldWidget : WorldWidgets)
	{
		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel->AddChildToCanvas(WorldWidget.Key->WorldWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetAnchors(FAnchors());
		CanvasPanelSlot->SetAlignment(FVector2D());
		CanvasPanelSlot->SetOffsets(FMargin());
		CanvasPanelSlot->SetZOrder(WorldWidget.Value->ZOrder);
	}
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

bool UWorldWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWorldWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UScreenWidgetManager::PostHUDCreated.AddUObject(this, &UWorldWidgetManager::GenerateWorldWidgetPanel);
	UWorldWidgetComponent::OnWorldWidgetPointBeginPlay.AddUObject(this, &UWorldWidgetManager::RegisterWorldWidgetComponent);
	UWorldWidgetComponent::OnWorldWidgetPointEndPlay.AddUObject(this, &UWorldWidgetManager::UnRegisterWorldWidgetComponent);
}

void UWorldWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UWorldWidgetComponent::OnWorldWidgetPointBeginPlay.RemoveAll(this);
	UWorldWidgetComponent::OnWorldWidgetPointEndPlay.RemoveAll(this);
	UScreenWidgetManager::PostHUDCreated.RemoveAll(this);
}

bool UWorldWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWorldWidgetManager::Tick(float DeltaTime)
{
	FTickableInternalManager::Tick(DeltaTime);

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnRefresh();
	}
}

void UWorldWidgetManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldBeginPlay(InWorld);
}

void UWorldWidgetManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	/* 从插槽移除3DUI面板 */
	const FGameplayTag WorldWidgetPanelTag = FGameplayTag::RequestGameplayTag(FName("UI.HUD.Main.WorldWidget"));
	if (WorldWidgetPanelTag.IsValid())
	{
		if (const UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
		{
			UGameplayTagSlot* Slot = ScreenWidgetManager->GetSlot(WorldWidgetPanelTag);
			if (IsValid(Slot))
			{
				Slot->ClearChildren();
			}
		}
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
	}
	WorldWidgetPanels.Reset();
}

void UWorldWidgetManager::RegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetPoint)
{
	if (IsValid(WorldWidgetPoint) && !WorldWidgetComponents.Contains(WorldWidgetPoint))
	{
		WorldWidgetComponents.Add(WorldWidgetPoint);

		if (!WorldWidgetPoint->bIsManualActive)
		{
			TryToAddWorldWidgetComponent(WorldWidgetPoint);
		}
	}
}

void UWorldWidgetManager::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetPoint)
{
	if (IsValid(WorldWidgetPoint) && WorldWidgetComponents.Contains(WorldWidgetPoint))
	{
		TryToRemoveWorldWidgetComponent(WorldWidgetPoint);
		WorldWidgetComponents.Remove(WorldWidgetPoint);
	}
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

void UWorldWidgetManager::GenerateWorldWidgetPanel()
{
	CreateWorldWidgetPanel();

	for (const auto& WorldWidgetPoint : WorldWidgetComponents)
	{
		if (!WorldWidgetPoint->bIsManualActive)
		{
			TryToAddWorldWidgetComponent(WorldWidgetPoint);
		}
	}
}

UWorldWidgetPanel* UWorldWidgetManager::CreateWorldWidgetPanel()
{
	UWorldWidgetPanel* NewWorldWidgetPanel = NewObject<UWorldWidgetPanel>(this);
	NewWorldWidgetPanel->NativeOnCreate();
	WorldWidgetPanels.Add(NewWorldWidgetPanel);

	return NewWorldWidgetPanel;
}

void UWorldWidgetManager::RefreshWorldWidgetPanel()
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->RefreshAllWorldWidgetComponent();
	}
}

void UWorldWidgetManager::RemoveWorldWidgetPanel(UWorldWidgetPanel* InWorldWidgetPanel)
{
	if (WorldWidgetPanels.Contains(InWorldWidgetPanel))
	{
		InWorldWidgetPanel->NativeOnDestroy();
		InWorldWidgetPanel->MarkAsGarbage();
		WorldWidgetPanels.Remove(InWorldWidgetPanel);
	}
}

void UWorldWidgetManager::ClearupWorldWidgetPanel()
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}
	WorldWidgetPanels.Reset();
}

void UWorldWidgetManager::TryToAddWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent)
{
	if (!IsValid(WorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	if (!IsValid(WorldWidgetComponent->WorldWidget))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidget Is NULL"))
		return;
	}

	if (WorldWidgetComponent->GetOwner()->IsHidden())
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetPoint Is Hidden"))
		return;
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->AddWorldWidgetComponent(WorldWidgetComponent);
	}
}

void UWorldWidgetManager::TryToRemoveWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent)
{
	if (!IsValid(WorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->RemoveWorldWidgetComponent(WorldWidgetComponent);
	}
}

#undef LOCTEXT_NAMESPACE
