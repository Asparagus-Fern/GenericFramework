// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "ScreenWidgetManager.h"
#include "WorldWidget.h"
#include "WorldWidgetManagerSetting.h"
#include "WorldWidgetPoint.h"
#include "Animation/WidgetAnimationEvent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"
#include "UWidget/GameplayTagSlot.h"

void UWorldWidgetPanel::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	Panel = NewObject<UCanvasPanel>(GetOuter());
}

void UWorldWidgetPanel::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();

	if (!IsValid(Panel) || !IsValid(GetWorld()))
	{
		return;
	}

	for (const auto& WorldWidget : WorldWidgets)
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			FVector2D ScreenPosition;
			APlayerController* PlayerController = Iterator->Get();

			/* 映射位置到所有PlayerController */
			if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, WorldWidget.Key->GetActorLocation(), ScreenPosition, false))
			{
				if (UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(WorldWidget.Value))
				{
					const FVector2D ResultPosition = ScreenPosition + WorldWidget.Value->GetAnchorOffset();

					int32 ViewportSizeX;
					int32 ViewportSizeY;
					PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

					if ((ResultPosition.X > 0) && (ResultPosition.X < ViewportSizeX) && (ResultPosition.Y > 0) && (ResultPosition.Y < ViewportSizeY))
					{
						WorldWidget.Value->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						CanvasPanelSlot->SetPosition(ResultPosition);
						continue;
					}
				}
			}

			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UWorldWidgetPanel::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	Panel->ClearChildren();
}

void UWorldWidgetPanel::AddWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (IsValid(InWorldWidgetPoint) && !WorldWidgets.Contains(InWorldWidgetPoint))
	{
		WorldWidgets.FindOrAdd(InWorldWidgetPoint, InWorldWidgetPoint->WorldWidget);

		if (IsValid(Panel))
		{
			UCanvasPanelSlot* CanvasPanelSlot = Panel->AddChildToCanvas(InWorldWidgetPoint->WorldWidget);
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetAnchors(FAnchors());
			CanvasPanelSlot->SetAlignment(FVector2D());
			CanvasPanelSlot->SetOffsets(FMargin());
			CanvasPanelSlot->SetZOrder(InWorldWidgetPoint->WorldWidget->ZOrder);
		}
	}
}

void UWorldWidgetPanel::RemoveWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (IsValid(InWorldWidgetPoint) && WorldWidgets.Contains(InWorldWidgetPoint))
	{
		if (IsValid(Panel))
		{
			Panel->RemoveChild(WorldWidgets.FindRef(InWorldWidgetPoint));
		}

		WorldWidgets.Remove(InWorldWidgetPoint);
	}
}

void UWorldWidgetPanel::RefreshWorldWidgetPoint()
{
	Panel->ClearChildren();

	for (const auto& WorldWidget : WorldWidgets)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Panel->AddChildToCanvas(WorldWidget.Key->WorldWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetAnchors(FAnchors());
		CanvasPanelSlot->SetAlignment(FVector2D());
		CanvasPanelSlot->SetOffsets(FMargin());
		CanvasPanelSlot->SetZOrder(WorldWidget.Value->ZOrder);
	}
}

bool UWorldWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UWorldWidgetManagerSetting::Get()->bEnableSubsystem;
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

void UWorldWidgetManager::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnRefresh();
	}
}

void UWorldWidgetManager::NativeOnActived()
{
	Super::NativeOnActived();

	GetManager<UScreenWidgetManager>()->PostHUDCreated.AddUniqueDynamic(this, &UWorldWidgetManager::GenerateWorldWidgetPanel);
	AWorldWidgetPoint::OnWorldWidgetPointRegister.AddUObject(this, &UWorldWidgetManager::RegisterWorldWidgetPoint);
	AWorldWidgetPoint::OnWorldWidgetPointUnRegister.AddUObject(this, &UWorldWidgetManager::RegisterWorldWidgetPoint);
}

void UWorldWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	/* 从插槽移除3DUI面板 */
	const FGameplayTag WorldWidgetPanelTag = FGameplayTag::RequestGameplayTag(FName("UI.HUD.Main.WorldWidget"));
	if (WorldWidgetPanelTag.IsValid())
	{
		if (const UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
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

	/* 销毁代理 */
	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->PostHUDCreated.RemoveAll(this);
	}

	AWorldWidgetPoint::OnWorldWidgetPointRegister.RemoveAll(this);
	AWorldWidgetPoint::OnWorldWidgetPointUnRegister.RemoveAll(this);
}

void UWorldWidgetManager::GenerateWorldWidgetPanel()
{
	const FGameplayTag WorldWidgetPanelTag = FGameplayTag::RequestGameplayTag(FName("UI.HUD.Main.WorldWidget"));
	if (WorldWidgetPanelTag.IsValid())
	{
		UGameplayTagSlot* Slot = GetManager<UScreenWidgetManager>()->GetSlot(WorldWidgetPanelTag);
		if (IsValid(Slot))
		{
			Slot->SetContent(CreateWorldWidgetPanel()->GetPanel());

			for (const auto& WorldWidgetPoint : WorldWidgetPoints)
			{
				if (!WorldWidgetPoint->bIsManual)
				{
					TryToAddWorldWidgetPoint(WorldWidgetPoint);
				}
			}
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
		WorldWidgetPanel->RefreshWorldWidgetPoint();
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

void UWorldWidgetManager::RegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	if (IsValid(WorldWidgetPoint) && !WorldWidgetPoints.Contains(WorldWidgetPoint))
	{
		WorldWidgetPoints.Add(WorldWidgetPoint);

		if (!WorldWidgetPoint->bIsManual)
		{
			TryToAddWorldWidgetPoint(WorldWidgetPoint);
		}
	}
}

void UWorldWidgetManager::UnRegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	if (IsValid(WorldWidgetPoint) && WorldWidgetPoints.Contains(WorldWidgetPoint))
	{
		TryToRemoveWorldWidgetPoint(WorldWidgetPoint);
		WorldWidgetPoints.Remove(WorldWidgetPoint);
	}
}

void UWorldWidgetManager::TryToAddWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	if (!IsValid(WorldWidgetPoint))
	{
		LOG(Debug_UI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	if (!IsValid(WorldWidgetPoint->WorldWidget))
	{
		LOG(Debug_UI, Error, TEXT("WorldWidget Is NULL"))
		return;
	}

	if (WorldWidgetPoint->IsHidden())
	{
		LOG(Debug_UI, Error, TEXT("WorldWidgetPoint Is Hidden"))
		return;
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->AddWorldWidgetPoint(WorldWidgetPoint);
	}
}

void UWorldWidgetManager::TryToRemoveWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint)
{
	if (!IsValid(WorldWidgetPoint))
	{
		LOG(Debug_UI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->RemoveWorldWidgetPoint(WorldWidgetPoint);
	}
}

#undef LOCTEXT_NAMESPACE
