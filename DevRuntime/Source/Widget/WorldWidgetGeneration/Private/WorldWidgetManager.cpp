// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "ScreenWidgetManager.h"
#include "WorldWidget.h"
#include "WorldWidgetPoint.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerCollection.h"
#include "Widget/TagNameSlot.h"
#include "Widgets/Layout/SConstraintCanvas.h"

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

FWorldWidgetPanel::FWorldWidgetPanel(UWorldWidgetManager* InOwner)
	: Owner(InOwner)
{
	Panel = NewObject<UCanvasPanel>(Owner);
}

void FWorldWidgetPanel::NativeOnCreate()
{
	IProcedureInterface::NativeOnCreate();
}

void FWorldWidgetPanel::NativeOnRefresh()
{
	IProcedureInterface::NativeOnRefresh();

	if (!IsValid(Owner) || !IsValid(Panel) || !IsValid(Owner->GetWorld()))
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

		for (FConstPlayerControllerIterator Iterator = Owner->GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
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

void FWorldWidgetPanel::NativeOnDestroy()
{
	IProcedureInterface::NativeOnDestroy();

	for (const auto& WorldWidget : WorldWidgets)
	{
		if (IsValid(WorldWidget.Value))
		{
			WorldWidget.Value->MarkAsGarbage();
		}
	}

	Owner = nullptr;
	Panel = nullptr;
	WorldWidgets.Reset();
}

void FWorldWidgetPanel::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();

	if (IsValid(Panel))
	{
		Panel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void FWorldWidgetPanel::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();

	if (IsValid(Panel))
	{
		Panel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void FWorldWidgetPanel::AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!WorldWidgets.Contains(InWorldWidgetPoint))
	{
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
	}
}

void FWorldWidgetPanel::RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (WorldWidgets.Contains(InWorldWidgetPoint) && IsValid(Panel))
		if (WorldWidgets.Contains(InWorldWidgetPoint) && IsValid(Panel))
		{
			Panel->RemoveChild(WorldWidgets.FindRef(InWorldWidgetPoint));
			WorldWidgets.Remove(InWorldWidgetPoint);
		}
}

void FWorldWidgetPanel::ClearWorldWidget()
{
	Panel->ClearChildren();
	WorldWidgets.Reset();
}

UWorldWidgetManager::UWorldWidgetManager()
{
	DisplayName = LOCTEXT("DisplayName", "World Widget Manager");
	ProcedureOrder = 0;
}

void UWorldWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWorldWidgetManager::Deinitialize()
{
	Super::Deinitialize();
}

UWorldWidgetManager* UWorldWidgetManager::Get()
{
	return FManagerCollection::Get()->GetManager<UWorldWidgetManager>();
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

	FScreenWidgetDelegates::OnHUDCreated.AddUObject(this, &UWorldWidgetManager::GenerateWorldWidget);
}

void UWorldWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	WorldWidgetPoints.Reset();
	ClearupWorldWidgetPanel();
}

void UWorldWidgetManager::GenerateWorldWidget()
{
	UTagNameSlot* Slot = UScreenWidgetManager::Get()->GetSlot(FGameplayTag::RequestGameplayTag(FName("HUD.Main.WorldWidget")));
	if (IsValid(Slot))
	{
		FWorldWidgetPanel* NewWorldWidgetPanel = CreateWorldWidgetPanel();
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

	RemovePanelWorldWidgetPoint(InWorldWidgetPoint);
	WorldWidgetPoints.Remove(InWorldWidgetPoint);
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

FWorldWidgetPanel* UWorldWidgetManager::CreateWorldWidgetPanel()
{
	FWorldWidgetPanel* NewWorldWidgetPanel = new FWorldWidgetPanel(this);
	NewWorldWidgetPanel->NativeOnCreate();
	WorldWidgetPanels.Add(NewWorldWidgetPanel);

	return NewWorldWidgetPanel;
}

void UWorldWidgetManager::ClearupWorldWidgetPanel()
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		delete WorldWidgetPanel;
	}

	WorldWidgetPanels.Reset();
}

#undef LOCTEXT_NAMESPACE
