// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "ScreenWidgetManager.h"
#include "WorldWidget.h"
#include "WorldWidgetPoint.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerGlobal.h"
#include "Widget/TagNameSlot.h"
#include "Widgets/Layout/SConstraintCanvas.h"


UWorldWidgetPanel::UWorldWidgetPanel(const FObjectInitializer& ObjectInitializer)
{
	Panel = NewObject<UCanvasPanel>(GetOuter());
}

void UWorldWidgetPanel::NativeOnCreate()
{
	IProcedureInterface::NativeOnCreate();
}

void UWorldWidgetPanel::NativeOnRefresh()
{
	IProcedureInterface::NativeOnRefresh();

	if (!IsValid(Panel) || !IsValid(GetWorld()))
	{
		return;
	}

	for (const auto& WorldWidget : WorldWidgets)
	{
		if (WorldWidget.Key->IsHidden())
		{
			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			FVector2D ScreenPosition;
			APlayerController* PlayerController = Iterator->Get();

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
	IProcedureInterface::NativeOnDestroy();

	for (const auto& WorldWidget : WorldWidgets)
	{
		if (IsValid(WorldWidget.Value))
		{
			WorldWidget.Value->MarkAsGarbage();
		}
	}

	Panel = nullptr;
	WorldWidgets.Reset();
}

void UWorldWidgetPanel::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();

	if (IsValid(Panel))
	{
		Panel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UWorldWidgetPanel::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();

	if (IsValid(Panel))
	{
		Panel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWorldWidgetPanel::AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!WorldWidgets.Contains(InWorldWidgetPoint))
	{
		if (IsValid(InWorldWidgetPoint->WorldWidget))
		{
			/* 直接使用该UMG会导致位置错误，因为会对所有的PlayerController进行位置更新，这就意味着他在不同player中看到的位置是不一样的 */
			UWorldWidget* DuplicateWorldWidget = DuplicateObject(InWorldWidgetPoint->WorldWidget, InWorldWidgetPoint);
			WorldWidgets.Add(InWorldWidgetPoint, DuplicateWorldWidget);

			UPanelSlot* PanelSlot = Panel->AddChild(DuplicateWorldWidget);
			if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
			{
				CanvasPanelSlot->SetAutoSize(true);
				CanvasPanelSlot->SetAnchors(FAnchors());
				CanvasPanelSlot->SetAlignment(FVector2D());
				CanvasPanelSlot->SetOffsets(FMargin());
			}

			/* 创建，但未打开，只在需要的时候显示 */
			DuplicateWorldWidget->NativeOnCreate();
			DuplicateWorldWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UWorldWidgetPanel::RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (WorldWidgets.Contains(InWorldWidgetPoint) && IsValid(Panel))
		if (WorldWidgets.Contains(InWorldWidgetPoint) && IsValid(Panel))
		{
			Panel->RemoveChild(WorldWidgets.FindRef(InWorldWidgetPoint));
			WorldWidgets.Remove(InWorldWidgetPoint);
		}
}

void UWorldWidgetPanel::ClearWorldWidget()
{
	Panel->ClearChildren();
	WorldWidgets.Reset();
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

UWorldWidgetManager::UWorldWidgetManager()
{
}

FText UWorldWidgetManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "World Widget Manager");
}

void UWorldWidgetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NativeOnRefresh();
}

void UWorldWidgetManager::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	if (IsValid(GetWorld()) && GetWorld()->IsGameWorld() && !WorldWidgetPanels.IsEmpty())
	{
		for (const auto& WorldWidgetPanel : WorldWidgetPanels)
		{
			if (WorldWidgetPanel->GetIsActive())
			{
				WorldWidgetPanel->NativeOnRefresh();
			}
		}
	}
}

void UWorldWidgetManager::NativeOnActived()
{
	Super::NativeOnActived();

	FScreenWidgetDelegates::OnHUDCreated.AddUObject(this, &UWorldWidgetManager::GenerateWorldWidgetPanel);
}

void UWorldWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	WorldWidgetPoints.Reset();
	ClearupWorldWidgetPanel();
}

void UWorldWidgetManager::GenerateWorldWidgetPanel()
{
	UTagNameSlot* Slot = GetManager<UScreenWidgetManager>()->GetSlot(FGameplayTag::RequestGameplayTag(FName("HUD.Main.WorldWidget")));
	if (IsValid(Slot))
	{
		UWorldWidgetPanel* NewWorldWidgetPanel = CreateWorldWidgetPanel();
		Slot->SetContent(NewWorldWidgetPanel->GetPanel());
		NewWorldWidgetPanel->NativeOnActived();

		RefreshAllPanelWorldWidgetPoint();
	}
}

void UWorldWidgetManager::AddWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!InWorldWidgetPoint)
	{
		DEBUG(Debug_UI, Error, TEXT("InWorldWidgetPoint Is NULL"))
		return;
	}

	if (WorldWidgetPoints.Contains(InWorldWidgetPoint))
	{
		return;
	}

	WorldWidgetPoints.Add(InWorldWidgetPoint);
	AddPanelWorldWidgetPoint(InWorldWidgetPoint);
}

void UWorldWidgetManager::RemoveWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!InWorldWidgetPoint)
	{
		DEBUG(Debug_UI, Error, TEXT("InWorldWidgetPoint Is NULL"))
		return;
	}

	if (!WorldWidgetPoints.Contains(InWorldWidgetPoint))
	{
		return;
	}

	WorldWidgetPoints.Remove(InWorldWidgetPoint);
	RemovePanelWorldWidgetPoint(InWorldWidgetPoint);
}

void UWorldWidgetManager::RefreshWolrdWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	RemoveWorldWidgetPoint(InWorldWidgetPoint);
	AddWorldWidgetPoint(InWorldWidgetPoint);
}

void UWorldWidgetManager::RefreshAllWorldWidgetPoint()
{
	TArray<AWorldWidgetPoint*> TempWorldWidgetPoints = WorldWidgetPoints;
	for (const auto& TempWorldWidgetPoint : TempWorldWidgetPoints)
	{
		RefreshWolrdWidgetPoint(TempWorldWidgetPoint);
	}
}

void UWorldWidgetManager::AddPanelWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->AddWorldWidget(InWorldWidgetPoint);
	}
}

void UWorldWidgetManager::RemovePanelWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->RemoveWorldWidget(InWorldWidgetPoint);
	}
}

void UWorldWidgetManager::RefreshPanelWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint)
{
	RemovePanelWorldWidgetPoint(InWorldWidgetPoint);
	AddPanelWorldWidgetPoint(InWorldWidgetPoint);
}

void UWorldWidgetManager::RefreshAllPanelWorldWidgetPoint()
{
	for (const auto& WorldWidgetPoint : WorldWidgetPoints)
	{
		RefreshPanelWorldWidgetPoint(WorldWidgetPoint);
	}
}

UWorldWidgetPanel* UWorldWidgetManager::CreateWorldWidgetPanel()
{
	UWorldWidgetPanel* NewWorldWidgetPanel = NewObject<UWorldWidgetPanel>(this);
	NewWorldWidgetPanel->NativeOnCreate();
	WorldWidgetPanels.Add(NewWorldWidgetPanel);

	return NewWorldWidgetPanel;
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

#undef LOCTEXT_NAMESPACE
