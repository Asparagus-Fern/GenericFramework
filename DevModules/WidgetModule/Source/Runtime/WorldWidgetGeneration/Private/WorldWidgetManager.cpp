// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidgetManager.h"

#include "GameHUDManager.h"
#include "WorldWidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager/ManagerProxy.h"
#include "UWidget/Override/GameplayTagSlot.h"
#include "Base/UserWidgetBase.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager/ManagerStatics.h"

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
		if (APlayerController* PlayerController = UBPFunctions_Gameplay::GetPlayerControllerByClass(GetWorld(), APlayerController::StaticClass(), WorldWidget.Key->WorldWidgetLookAtSetting.LookAtPlayerIndex))
		{
			FVector2D ScreenPosition;

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
		UGameplayTagSlot* Slot = GetManager<UGameHUDManager>()->GetSlot(WorldWidgetPanelTag);
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

void UWorldWidgetPanel::AddWorldWidgetComponent(AActor* InActor)
{
	TArray<UWorldWidgetComponent*> WorldWidgetComponents;
	InActor->GetComponents(UWorldWidgetComponent::StaticClass(), WorldWidgetComponents);

	for (const auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		AddWorldWidgetComponent(WorldWidgetComponent);
	}
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

	UGameHUDManager::Delegate_PostHUDCreated.AddUObject(this, &UWorldWidgetManager::GenerateWorldWidgetPanel);
	UWorldWidgetComponent::OnWorldWidgetPointBeginPlay.AddUObject(this, &UWorldWidgetManager::RegisterWorldWidgetComponent);
	UWorldWidgetComponent::OnWorldWidgetPointEndPlay.AddUObject(this, &UWorldWidgetManager::UnRegisterWorldWidgetComponent);
}

void UWorldWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UWorldWidgetComponent::OnWorldWidgetPointBeginPlay.RemoveAll(this);
	UWorldWidgetComponent::OnWorldWidgetPointEndPlay.RemoveAll(this);
	UGameHUDManager::Delegate_PostHUDCreated.RemoveAll(this);
}

bool UWorldWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWorldWidgetManager::Tick(float DeltaTime)
{
	FTickableInternalManager::Tick(DeltaTime);

	RefreshWorldWidgetComponents2DLookAtRotation(GetWorldWidgetComponents2D());
	RefreshWorldWidgetComponents3DLookAtRotation(GetWorldWidgetComponents3D());
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
		if (const UGameHUDManager* GameHUDManager = GetManager<UGameHUDManager>())
		{
			UGameplayTagSlot* Slot = GameHUDManager->GetSlot(WorldWidgetPanelTag);
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

void UWorldWidgetManager::SetWorldWidgetComponentActiveState(AActor* InActor, bool IsActive)
{
	if (IsActive)
	{
		TryToAddWorldWidgetComponent(InActor);
	}
	else
	{
		TryToRemoveWorldWidgetComponent(InActor);
	}
}

void UWorldWidgetManager::SetWorldWidgetComponentActiveState(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive)
{
	if (IsActive)
	{
		TryToAddWorldWidgetComponent(InWorldWidgetComponent);
	}
	else
	{
		TryToRemoveWorldWidgetComponent(InWorldWidgetComponent);
	}
}

void UWorldWidgetManager::SetWorldWidgetPaintMethod(UWorldWidgetComponent* InWorldWidgetComponent, EWorldWidgetPaintMethod WorldWidgetPaintMethod)
{
	if (InWorldWidgetComponent->WorldWidgetPaintMethod != WorldWidgetPaintMethod)
	{
		TryToRemoveWorldWidgetComponent(InWorldWidgetComponent);
		InWorldWidgetComponent->WorldWidgetPaintMethod = WorldWidgetPaintMethod;
		TryToAddWorldWidgetComponent(InWorldWidgetComponent);
	}
}

void UWorldWidgetManager::SetWorldWidgetLookAtSetting(UWorldWidgetComponent* InWorldWidgetComponent, FWorldWidgetLookAtSetting WorldWidgetLookAtSetting)
{
	if (InWorldWidgetComponent->WorldWidgetLookAtSetting != WorldWidgetLookAtSetting)
	{
		TryToRemoveWorldWidgetComponent(InWorldWidgetComponent);
		InWorldWidgetComponent->WorldWidgetLookAtSetting = WorldWidgetLookAtSetting;
		TryToAddWorldWidgetComponent(InWorldWidgetComponent);
	}
}

void UWorldWidgetManager::RegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetPoint)
{
	if (!IsValid(WorldWidgetPoint))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
	}

	if (WorldWidgetComponents.Contains(WorldWidgetPoint))
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetPoint Is Already Register"))
	}

	if (!WorldWidgetPoint->bIsManualActive)
	{
		TryToAddWorldWidgetComponent(WorldWidgetPoint);
	}
}

void UWorldWidgetManager::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetPoint)
{
	if (!IsValid(WorldWidgetPoint))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
	}

	if (WorldWidgetComponents.Contains(WorldWidgetPoint))
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetPoint Is Already UnRegister"))
	}

	TryToRemoveWorldWidgetComponent(WorldWidgetPoint);
}

void UWorldWidgetManager::TryToAddWorldWidgetComponent(AActor* InActor)
{
	TArray<UWorldWidgetComponent*> ActorWorldWidgetComponents;
	InActor->GetComponents(UWorldWidgetComponent::StaticClass(), ActorWorldWidgetComponents);

	for (const auto& WorldWidgetComponent : ActorWorldWidgetComponents)
	{
		TryToAddWorldWidgetComponent(WorldWidgetComponent);
	}
}

void UWorldWidgetManager::TryToAddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	if (!IsValid(InWorldWidgetComponent->WorldWidget))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidget Is NULL"))
		return;
	}

	if (InWorldWidgetComponent->GetOwner()->IsHidden())
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetPoint Is Hidden"))
		return;
	}

	WorldWidgetComponents.AddUnique(InWorldWidgetComponent);

	if (InWorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen)
	{
		for (const auto& WorldWidgetPanel : WorldWidgetPanels)
		{
			if (WorldWidgetPanel->IsContain(InWorldWidgetComponent))
			{
				WorldWidgetPanel->RefreshWorldWidgetComponent(InWorldWidgetComponent);
			}
			else
			{
				WorldWidgetPanel->AddWorldWidgetComponent(InWorldWidgetComponent);
			}
		}
	}
	else if (InWorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld)
	{
		InWorldWidgetComponent->RefreshWidgetComponent();
	}
}

void UWorldWidgetManager::TryToRemoveWorldWidgetComponent(AActor* InActor)
{
	TArray<UWorldWidgetComponent*> ActorWorldWidgetComponents;
	InActor->GetComponents(UWorldWidgetComponent::StaticClass(), ActorWorldWidgetComponents);

	for (const auto& WorldWidgetComponent : ActorWorldWidgetComponents)
	{
		TryToRemoveWorldWidgetComponent(WorldWidgetComponent);
	}
}

void UWorldWidgetManager::TryToRemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("WorldWidgetPoint Is NULL"))
		return;
	}

	if (InWorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen)
	{
		for (const auto& WorldWidgetPanel : WorldWidgetPanels)
		{
			WorldWidgetPanel->RemoveWorldWidgetComponent(InWorldWidgetComponent);
		}
	}
	else if (InWorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld)
	{
		InWorldWidgetComponent->ClearWidgetComponent();
	}

	WorldWidgetComponents.Remove(InWorldWidgetComponent);
}

void UWorldWidgetManager::RefreshWorldWidgetComponents2DLookAtRotation(TArray<UWorldWidgetComponent*> InWorldWidgetComponents)
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnRefresh();
	}
}

void UWorldWidgetManager::RefreshWorldWidgetComponents3DLookAtRotation(TArray<UWorldWidgetComponent*> InWorldWidgetComponents)
{
	for (const auto& WorldWidgetComponent : InWorldWidgetComponents)
	{
		/* Disable Look At Player */
		if (!WorldWidgetComponent->WorldWidgetLookAtSetting.bEnableLookAtPlayerCamera)
		{
			continue;
		}

		if (UWidgetComponent* WidgetComponent = WorldWidgetComponent->GetWidgetComponent())
		{
			if (const APlayerController* PC = UBPFunctions_Gameplay::GetPlayerControllerByClass(GetWorld(), APlayerController::StaticClass(), WorldWidgetComponent->WorldWidgetLookAtSetting.LookAtPlayerIndex))
			{
				const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->GetComponentLocation(), PC->PlayerCameraManager->GetCameraLocation());
				FRotator WidgetComponentRotation = WidgetComponent->GetRelativeRotation();

				if (WorldWidgetComponent->WorldWidgetLookAtSetting.LookAtPitch)
				{
					WidgetComponentRotation.Pitch = LookAtRotation.Pitch;
				}
				if (WorldWidgetComponent->WorldWidgetLookAtSetting.LookAtYaw)
				{
					WidgetComponentRotation.Yaw = LookAtRotation.Yaw;
				}
				if (WorldWidgetComponent->WorldWidgetLookAtSetting.LookAtRoll)
				{
					WidgetComponentRotation.Roll = LookAtRotation.Roll;
				}

				WidgetComponent->SetRelativeRotation(WidgetComponentRotation);
			}
		}
	}
}

void UWorldWidgetManager::RefreshAllWorldWidgetComponents()
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->RefreshAllWorldWidgetComponent();
	}

	for (const auto& WorldWidgetComponent3D : GetWorldWidgetComponents3D())
	{
		WorldWidgetComponent3D->RefreshWidgetComponent();
	}
}

void UWorldWidgetManager::GenerateWorldWidgetPanel()
{
	CreateWorldWidgetPanel();

	for (const auto& WorldWidgetPoint : GetWorldWidgetComponents2D())
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

void UWorldWidgetManager::RemoveWorldWidgetPanel(UWorldWidgetPanel* InWorldWidgetPanel)
{
	if (WorldWidgetPanels.Contains(InWorldWidgetPanel))
	{
		InWorldWidgetPanel->NativeOnDestroy();
		InWorldWidgetPanel->MarkAsGarbage();
		WorldWidgetPanels.Remove(InWorldWidgetPanel);
	}
}

void UWorldWidgetManager::ClearAllWorldWidgetPanel()
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}
	WorldWidgetPanels.Reset();
}

#undef LOCTEXT_NAMESPACE
