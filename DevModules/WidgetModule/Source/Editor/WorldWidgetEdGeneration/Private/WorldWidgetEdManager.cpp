// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldWidgetEdManager.h"

#include "EngineUtils.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "SWorldWidgetContainer.h"
#include "WorldWidgetComponent.h"
#include "WorldWidgetPoint.h"
#include "BPFunctions/BPFunctions_EditorScene.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "UWidget/SimpleTextBox.h"
#include "Base/UserWidgetBase.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/Layout/SConstraintCanvas.h"

void UEditorWorldWidgetPanel::NativeOnCreate()
{
	UWorldWidgetPanel::NativeOnCreate();

	RefreshAllWorldWidgetComponent();
}

void UEditorWorldWidgetPanel::NativeOnRefresh()
{
	if (!ConstraintCanvas.IsValid() || !LevelEditorViewportClient || !LevelEditorViewportClient->ParentLevelEditor.IsValid())
	{
		return;
	}

	/* 遍历所有的Widget并更新其位置 */
	TMap<UWorldWidgetComponent*, UUserWidgetBase*> TempWorldWidgets = WorldWidgets;
	for (const auto& TempWorldWidget : TempWorldWidgets)
	{
		if (!IsValid(TempWorldWidget.Value))
		{
			WorldWidgets.Remove(TempWorldWidget.Key);
			continue;
		}

		if (TempWorldWidget.Key->GetOwner()->IsHiddenEd())
		{
			TempWorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		if (!LevelEditorViewportClient->IsPerspective())
		{
			TempWorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		if (const FViewport* Viewport = LevelEditorViewportClient->Viewport)
		{
			/* 获取世界坐标转屏幕坐标 */
			FVector2D ScreenPosition;
			if (UBPFunctions_EditorWidget::EditorProjectWorldToScreen(LevelEditorViewportClient, TempWorldWidget.Key->GetComponentLocation(), ScreenPosition))
			{
				const FVector2D ResultPosition = ScreenPosition + TempWorldWidget.Value->GetAnchorOffset();

				/* 超出屏幕大小时隐藏 */
				if (ResultPosition.X > -TempWorldWidget.Value->GetDesiredSize().X && ResultPosition.X < Viewport->GetSizeXY().X && ResultPosition.Y > -TempWorldWidget.Value->GetDesiredSize().Y && ResultPosition.Y < Viewport->GetSizeXY().Y)
				{
					TempWorldWidget.Value->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					WorldWidgetSlots.FindRef(TempWorldWidget.Key)->SetOffset(FMargin(ResultPosition.X, ResultPosition.Y, 0, 0));
					// TempWorldWidget.Value->SetRenderTranslation(ResultPosition);
					continue;
				}
			}
		}

		TempWorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UEditorWorldWidgetPanel::NativeOnDestroy()
{
	for (const auto& WorldWidget : WorldWidgets)
	{
		ConstraintCanvas->RemoveSlot(WorldWidget.Value->TakeWidget());
		WorldWidget.Value->MarkAsGarbage();
	}

	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::RemoveFromEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}

	UWorldWidgetPanel::NativeOnDestroy();

	WorldWidgetContainer.Reset();
}

void UEditorWorldWidgetPanel::HandleAddToViewport()
{
	/* 对视口创建新的Panel存放WorldWidget */
	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::AddToEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}
}

void UEditorWorldWidgetPanel::HandleRemoveFromViewport()
{
	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::RemoveFromEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}
}

bool UEditorWorldWidgetPanel::IsContain(UWorldWidgetComponent* InWorldWidgetComponent)
{
	for (const auto& WorldWidget : WorldWidgetContainer)
	{
		if (WorldWidget.Key == InWorldWidgetComponent)
		{
			return true;
		}
	}

	return false;
}

void UEditorWorldWidgetPanel::AddWorldWidgetComponent(AActor* InActor)
{
	Super::AddWorldWidgetComponent(InActor);
}

void UEditorWorldWidgetPanel::AddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (InWorldWidgetComponent->WorldWidgetPaintMethod != EWorldWidgetPaintMethod::PaintInScreen)
	{
		return;
	}

	if (!IsValid(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Error, TEXT("InWorldWidgetComponent Is NULL"))
		return;
	}

	if (!IsValid(InWorldWidgetComponent->WorldWidget))
	{
		DLOG(DLogUI, Warning, TEXT("WorldWidgetComponent %s Has a InValid WorldWidget"), *InWorldWidgetComponent->GetName())
		return;
	}

	if (WorldWidgets.Contains(InWorldWidgetComponent))
	{
		DLOG(DLogUI, Warning, TEXT("This WorldWidget Already Created"))
		return;
	}

	UUserWidgetBase* DuplicateWorldWidget = DuplicateObject(InWorldWidgetComponent->WorldWidget, InWorldWidgetComponent);
	DuplicateWorldWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	WorldWidgets.Add(InWorldWidgetComponent, DuplicateWorldWidget);

	TSharedPtr<SWorldWidgetContainer> NewContainer = SNew(SWorldWidgetContainer)
		.OnWorldWidgetMiddleClicked_UObject(this, &UEditorWorldWidgetPanel::OnWorldWidgetMiddleClicked)
		[
			DuplicateWorldWidget->TakeWidget()
		];

	SConstraintCanvas::FSlot* NewSlot;
	ConstraintCanvas->AddSlot()
		.Expose(NewSlot)
		.AutoSize(true)
		.Anchors(FAnchors())
		.Alignment(FVector2D())
		.Offset(FMargin())
		.ZOrder(DuplicateWorldWidget->ZOrder)
		[
			NewContainer.ToSharedRef()
		];

	WorldWidgetContainer.FindOrAdd(InWorldWidgetComponent, NewContainer);
	WorldWidgetSlots.FindOrAdd(InWorldWidgetComponent, NewSlot);
}

void UEditorWorldWidgetPanel::RemoveWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	/* InWorldWidgetComponent为空 */
	if (!IsValid(InWorldWidgetComponent))
	{
		return;
	}

	ConstraintCanvas->RemoveSlot(WorldWidgetContainer.FindRef(InWorldWidgetComponent).ToSharedRef());

	WorldWidgets.Remove(InWorldWidgetComponent);
	WorldWidgetContainer.Remove(InWorldWidgetComponent);
	WorldWidgetSlots.Remove(InWorldWidgetComponent);
}

void UEditorWorldWidgetPanel::RefreshAllWorldWidgetComponent()
{
	/* 清除当前所有的WorldWidget */
	{
		for (const auto& WorldWidget : WorldWidgets)
		{
			ConstraintCanvas->RemoveSlot(WorldWidgetContainer.FindRef(WorldWidget.Key).ToSharedRef());
			WorldWidget.Value->MarkAsGarbage();
		}

		WorldWidgets.Reset();
		WorldWidgetContainer.Reset();
		WorldWidgetSlots.Reset();
	}

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		AddWorldWidgetComponent(Actor);
	}
}

void UEditorWorldWidgetPanel::OnWorldWidgetMiddleClicked(TSharedPtr<SWorldWidgetContainer> DoubleClickedContainer)
{
	if (const UWorldWidgetComponent* WorldWidgetComponent = *WorldWidgetContainer.FindKey(DoubleClickedContainer))
	{
		if (GEditor->CanSelectActor(WorldWidgetComponent->GetOwner(), true))
		{
			UBPFunctions_EditorScene::SelectNone();
			UBPFunctions_EditorScene::SelectActor(WorldWidgetComponent->GetOwner(), true);
		}
	}
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

bool UWorldWidgetEdManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWorldWidgetEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	RegisterManager(this);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdManager::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UWorldWidgetEdManager::OnLevelViewportClientListChanged);
	LevelActorAddedHandle = GEditor->OnLevelActorAdded().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorAdded);
	ActorsMovedHandle = GEditor->OnActorsMoved().AddUObject(this, &UWorldWidgetEdManager::OnActorsMoved);
	LevelActorDeletedHandle = GEditor->OnLevelActorDeleted().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorDeleted);
	BlueprintCompiledHandle = GEditor->OnBlueprintCompiled().AddUObject(this, &UWorldWidgetEdManager::OnBlueprintCompiled);

	if (UWorld* World = GetWorld())
	{
		LevelsChangedHandle = World->OnLevelsChanged().AddUObject(this, &UWorldWidgetEdManager::OnLevelsChanged);
	}

	WorldWidgetComponentRegisterHandle = UWorldWidgetComponent::OnWorldWidgetComponentRegister.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetComponentRegister);
	WorldWidgetComponentUnRegisterHandle = UWorldWidgetComponent::OnWorldWidgetComponentUnRegister.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetComponentUnRegister);

	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::Deinitialize()
{
	UnRegisterManager();

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}

	WorldWidgetPanels.Reset();
	WorldWidgetComponents.Reset();

	LevelEditorCreatedHandle.Reset();
	LevelViewportClientListChangedHandle.Reset();
	LevelActorAddedHandle.Reset();
	ActorsMovedHandle.Reset();
	LevelActorDeletedHandle.Reset();
	BlueprintCompiledHandle.Reset();

	LevelsChangedHandle.Reset();

	WorldWidgetComponentRegisterHandle.Reset();
	WorldWidgetComponentUnRegisterHandle.Reset();
}

bool UWorldWidgetEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UWorldWidgetEdManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	/* 运行时开始的时候把编辑器的3DUI清空 */
	ClearAllWorldWidgetPanel();
}

void UWorldWidgetEdManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	/* 运行时结束时重新生成编辑器的3DUI */
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	GenerateWorldWidgetPanel();
	RefreshAllWorldWidgetComponents();
}

void UWorldWidgetEdManager::OnLevelViewportClientListChanged()
{
	ClearAllWorldWidgetPanel();
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelActorAdded(AActor* Actor)
{
	TryToAddWorldWidgetComponent(Actor);
}

void UWorldWidgetEdManager::OnActorsMoved(TArray<AActor*>& Actors)
{
	for (const auto& Actor : Actors)
	{
		TryToAddWorldWidgetComponent(Actor);
	}
}

void UWorldWidgetEdManager::OnLevelActorDeleted(AActor* Actor)
{
	TryToRemoveWorldWidgetComponent(Actor);
}

void UWorldWidgetEdManager::OnBlueprintCompiled()
{
	RefreshAllWorldWidgetComponents();
}

void UWorldWidgetEdManager::OnLevelsChanged()
{
	RefreshAllWorldWidgetComponents();
}

void UWorldWidgetEdManager::OnWorldWidgetComponentRegister(UWorldWidgetComponent* WorldWidgetComponent)
{
	TryToAddWorldWidgetComponent(WorldWidgetComponent);
}

void UWorldWidgetEdManager::OnWorldWidgetComponentUnRegister(UWorldWidgetComponent* WorldWidgetComponent)
{
	TryToRemoveWorldWidgetComponent(WorldWidgetComponent);
}

void UWorldWidgetEdManager::GenerateWorldWidgetPanel()
{
	for (const auto& LevelEditorViewportClient : UBPFunctions_EditorWidget::GetLevelEditorViewportClients())
	{
		/* 添加到LevelEditorViewport */
		if (UEditorWorldWidgetPanel* EditorWorldWidgetPanel = Cast<UEditorWorldWidgetPanel>(CreateWorldWidgetPanel()))
		{
			EditorWorldWidgetPanel->LevelEditorViewportClient = LevelEditorViewportClient;
			EditorWorldWidgetPanel->NativeOnCreate();
		}
	}
}

UWorldWidgetPanel* UWorldWidgetEdManager::CreateWorldWidgetPanel()
{
	UEditorWorldWidgetPanel* NewEditorWorldWidgetPanel = NewObject<UEditorWorldWidgetPanel>(this);
	WorldWidgetPanels.Add(NewEditorWorldWidgetPanel);

	return NewEditorWorldWidgetPanel;
}

void UWorldWidgetEdManager::RefreshWorldWidgetComponents3DLookAtRotation(TArray<UWorldWidgetComponent*> InWorldWidgetComponents)
{
	// Super::RefreshWorldWidgetComponents3D(InWorldWidgetComponents);

	for (const auto& WorldWidgetComponent : InWorldWidgetComponents)
	{
		/* Disable Look At Player */
		if (!WorldWidgetComponent->WorldWidgetLookAtSetting.bEnableLookAtPlayerCamera)
		{
			continue;
		}

		if (UWidgetComponent* WidgetComponent = WorldWidgetComponent->GetWidgetComponent())
		{
			if (GCurrentLevelEditingViewportClient)
			{
				const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->GetComponentLocation(), GCurrentLevelEditingViewportClient->GetViewLocation());
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

#undef LOCTEXT_NAMESPACE
