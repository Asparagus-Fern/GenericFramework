// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "ScreenWidgetManager.h"
#include "WorldWidget.h"
#include "WorldWidgetPoint.h"
#include "Animation/WidgetAnimationEvent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"
#include "UWidget/GameplayTagSlot.h"

UWorldWidgetPanel::UWorldWidgetPanel(const FObjectInitializer& ObjectInitializer)
{
	Panel = NewObject<UCanvasPanel>(GetOuter());
}

void UWorldWidgetPanel::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
}

void UWorldWidgetPanel::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();

	if (!IsValid(Panel) || !IsValid(GetWorld()))
	{
		DEBUG(Debug_UI, Error, TEXT("Panel/World Is NULL"))
		return;
	}

	for (const auto& WorldWidget : WorldWidgets)
	{
		/* 跳过非激活UI */
		if (!WorldWidget.Value->GetIsActive())
		{
			continue;
		}

		/* 跳过隐藏的UI */
		if (WorldWidget.Key->IsHidden())
		{
			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

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
			UWorldWidget* WorldWidget = InWorldWidgetPoint->WorldWidget;
			WorldWidgets.Add(InWorldWidgetPoint, WorldWidget);

			UPanelSlot* PanelSlot = Panel->AddChild(WorldWidget);
			if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
			{
				CanvasPanelSlot->SetAutoSize(true);
				CanvasPanelSlot->SetAnchors(FAnchors());
				CanvasPanelSlot->SetAlignment(FVector2D());
				CanvasPanelSlot->SetOffsets(FMargin());
				CanvasPanelSlot->SetZOrder(WorldWidget->ZOrder);
			}

			/* 创建，但未打开，只在需要的时候显示 */
			WorldWidget->NativeOnCreate();

			/* 自动激活 */
			if (InWorldWidgetPoint->bIsAutoActived)
			{
				WorldWidget->NativeOnActived();
			}
			else
			{
				WorldWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
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

void UWorldWidgetPanel::ActiveWorldWidget(const AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!IsValid(InWorldWidgetPoint))
	{
		DEBUG(Debug_UI, Error, TEXT("InWorldWidgetPoint Is NULL"))
		return;
	}

	if (WorldWidgets.Contains(InWorldWidgetPoint))
	{
		UWorldWidget* ActiveWidget = WorldWidgets.FindRef(InWorldWidgetPoint);
		ActiveWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		GetManager<UProcedureManager>()->RegisterProcedureHandle(GetManager<UScreenWidgetManager>()->GetProcedureInterfaceHandles(ActiveWidget, true));
	}
}

void UWorldWidgetPanel::InactiveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!IsValid(InWorldWidgetPoint))
	{
		DEBUG(Debug_UI, Error, TEXT("InWorldWidgetPoint Is NULL"))
		return;
	}

	if (WorldWidgets.Contains(InWorldWidgetPoint))
	{
		UWorldWidget* InactiveWidget = WorldWidgets.FindRef(InWorldWidgetPoint);

		FSimpleMulticastDelegate OnFinish;
		OnFinish.AddLambda([&InactiveWidget]()
			{
				InactiveWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		);

		GetManager<UProcedureManager>()->RegisterProcedureHandle(GetManager<UScreenWidgetManager>()->GetProcedureInterfaceHandles(InactiveWidget, false), OnFinish);
	}
}

void UWorldWidgetPanel::ActiveWorldWidgets(TArray<AWorldWidgetPoint*> InWorldWidgetPoints)
{
	for (const auto& InWorldWidgetPoint : InWorldWidgetPoints)
	{
		ActiveWorldWidget(InWorldWidgetPoint);
	}

	/*TArray<int32> Order;
	int32 OrderIndex = 0;
	
	/* 获取所有的顺序 #1#
	for (const auto& WorldWidgetPoint : InWorldWidgetPoints)
	{
		if (!Order.Contains(WorldWidgetPoint->Order))
		{
			Order.Add(WorldWidgetPoint->Order);
		}
	}
	
	/* 单次的处理 #1#
	auto HandleOnce = [this, &Order, &OrderIndex, &InWorldWidgetPoints]()
	{
		/* 激活的一组WorldWidget会根据AWorldWidgetPoint::Order进行顺序激活，Order越小越先被激活 #1#
		if (Order.IsValidIndex(OrderIndex))
		{
			float MaxDuration = 0.f;
			const TArray<AWorldWidgetPoint*> HandlePoints = UWorldWidgetManager::GetWorldWidgetPointsByOrder(InWorldWidgetPoints, Order[OrderIndex]);
			TArray<UWorldWidget*> HandleWidgets = GetWorldWidgetsByPoints(HandlePoints);
			for (const auto& HandleWidget : HandleWidgets)
			{
				if (IsValid(HandleWidget) && IsValid(HandleWidget->AnimationEvent))
				{
					MaxDuration = FMath::Max(MaxDuration, HandleWidget->AnimationEvent->GetAnimationDuration());
				}
			}
	
			/* 取动画的最大持续时间作为这一阶段的结束 #1#
			FTimerHandle Handle;
			GetWorld()->GetTimerManager().SetTimer
			(
				Handle,
				FTimerDelegate::CreateLambda([&OrderIndex]()
					{
						OrderIndex++;
						// HandleOnce();
					}
				),
				MaxDuration,
				false
			);
	
			/* 激活UI #1#
			for (const auto& HandleWidget : HandleWidgets)
			{
				HandleWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				HandleWidget->NativeOnActived();
			}
		}
	};*/
}

void UWorldWidgetPanel::InactiveWorldWidgets(TArray<AWorldWidgetPoint*> InWorldWidgetPoints)
{
	for (const auto& InWorldWidgetPoint : InWorldWidgetPoints)
	{
		InactiveWorldWidget(InWorldWidgetPoint);
	}
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

TArray<UWorldWidget*> UWorldWidgetPanel::GetWorldWidgetsByPoints(TArray<AWorldWidgetPoint*> InPoints)
{
	TArray<UWorldWidget*> OutWorldWidgets;
	for (const auto& InPoint : InPoints)
	{
		if (!WorldWidgets.Contains(InPoint))
		{
			continue;;
		}

		OutWorldWidgets.Add(WorldWidgets.FindRef(InPoint));
	}
	return OutWorldWidgets;
}

UWorldWidgetManager::UWorldWidgetManager()
{
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
}

void UWorldWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

FText UWorldWidgetManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "World Widget Manager");
}

void UWorldWidgetManager::NativeOnBeginPlay()
{
	Super::NativeOnBeginPlay();

	WorldWidgetPoints.Reset();
	GenerateWorldWidgetPanel();
}

void UWorldWidgetManager::NativeOnEndPlay()
{
	Super::NativeOnEndPlay();

	WorldWidgetPoints.Reset();
	ClearupWorldWidgetPanel();
}

void UWorldWidgetManager::ActiveWorldWidgetPoint(AWorldWidgetPoint* InPoint)
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->ActiveWorldWidget(InPoint);
	}
}

void UWorldWidgetManager::ActiveWorldWidgetPoint(FGameplayTag InPointTag)
{
	if (!InPointTag.IsValid())
	{
		DEBUG(Debug_UI, Error, TEXT("InPointTag Is NULL"))
		return;
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->ActiveWorldWidgets(GetWorldWidgetPoints(InPointTag));
	}
}

void UWorldWidgetManager::InactiveWorldWidgetPoint(AWorldWidgetPoint* InPoint)
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->InactiveWorldWidget(InPoint);
	}
}

void UWorldWidgetManager::InactiveWorldWidgetPoint(FGameplayTag InPointTag)
{
	if (!InPointTag.IsValid())
	{
		DEBUG(Debug_UI, Error, TEXT("InPointTag Is NULL"))
		return;
	}

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->InactiveWorldWidgets(GetWorldWidgetPoints(InPointTag));
	}
}

TArray<AWorldWidgetPoint*> UWorldWidgetManager::GetWorldWidgetPoints() const
{
	return WorldWidgetPoints;
}

TArray<AWorldWidgetPoint*> UWorldWidgetManager::GetWorldWidgetPoints(FGameplayTag InPointTag) const
{
	TArray<AWorldWidgetPoint*> Points;
	for (auto& WorldWidgetPoint : GetWorldWidgetPoints())
	{
		if (WorldWidgetPoint->PointTag.MatchesTag(InPointTag))
		{
			Points.Add(WorldWidgetPoint);
		}
	}
	return Points;
}

void UWorldWidgetManager::GenerateWorldWidgetPanel()
{
	UGameplayTagSlot* Slot = GetManager<UScreenWidgetManager>()->GetSlot(FGameplayTag::RequestGameplayTag(FName("HUD.Main.WorldWidget")));
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
