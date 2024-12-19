// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldWidgetEdManager.h"

#include "EngineUtils.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "SWorldWidgetContainer.h"
#include "WorldWidgetComponent.h"
#include "WorldWidgetEdManagerSetting.h"
#include "WorldWidgetPoint.h"
#include "BPFunctions/BPFunctions_EditorScene.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "UserWidget/Base/UserWidgetBase.h"
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

void UEditorWorldWidgetPanel::AddWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	/* InWorldWidgetComponent为空 */
	if (!IsValid(InWorldWidgetComponent))
	{
		return;
	}

	/* 该WorldWidget组件没有指定WorldWidget */
	if (!IsValid(InWorldWidgetComponent->WorldWidget))
	{
		return;
	}

	/* 该WorldWidget组件已被创建 */
	if (WorldWidgets.Contains(InWorldWidgetComponent))
	{
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

		if (const AWorldWidgetPoint* WorldWidgetPoint = Cast<AWorldWidgetPoint>(Actor))
		{
			AddWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
		}
		else
		{
			TArray<UWorldWidgetComponent*> WorldWidgetComponents;
			Actor->GetComponents(UWorldWidgetComponent::StaticClass(), WorldWidgetComponents);

			for (const auto& WorldWidgetComponent : WorldWidgetComponents)
			{
				AddWorldWidgetComponent(WorldWidgetComponent);
			}
		}
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
	return Super::ShouldCreateSubsystem(Outer) && UWorldWidgetEdManagerSetting::Get()->GetEnableManager();
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
}

bool UWorldWidgetEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UWorldWidgetEdManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	/* 运行时开始的时候把编辑器的3DUI清空 */
	ClearupWorldWidgetPanel();
}

void UWorldWidgetEdManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	/* 运行时结束时重新生成编辑器的3DUI */
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelViewportClientListChanged()
{
	ClearupWorldWidgetPanel();
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelActorAdded(AActor* Actor)
{
	// RefreshWorldWidgetPanel();

	for (const auto& Panel : WorldWidgetPanels)
	{
		if (const AWorldWidgetPoint* WorldWidgetPoint = Cast<AWorldWidgetPoint>(Actor))
		{
			Panel->AddWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
		}
	}
}

void UWorldWidgetEdManager::OnActorsMoved(TArray<AActor*>& Actors)
{
	// RefreshWorldWidgetPanel();

	for (const auto& Panel : WorldWidgetPanels)
	{
		for (const auto& Actor : Actors)
		{
			if (const AWorldWidgetPoint* WorldWidgetPoint = Cast<AWorldWidgetPoint>(Actor))
			{
				if (Panel->IsContain(WorldWidgetPoint->WorldWidgetComponent))
				{
					Panel->RefreshWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
				}
				else
				{
					Panel->AddWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
				}
			}
		}
	}
}

void UWorldWidgetEdManager::OnLevelActorDeleted(AActor* Actor)
{
	// RefreshWorldWidgetPanel();

	for (const auto& Panel : WorldWidgetPanels)
	{
		if (const AWorldWidgetPoint* WorldWidgetPoint = Cast<AWorldWidgetPoint>(Actor))
		{
			if (Panel->IsContain(WorldWidgetPoint->WorldWidgetComponent))
			{
				Panel->RemoveWorldWidgetComponent(WorldWidgetPoint->WorldWidgetComponent);
			}
		}
	}
}

void UWorldWidgetEdManager::OnBlueprintCompiled()
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelsChanged()
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnWorldWidgetComponentRegister(UWorldWidgetComponent* WorldWidgetComponent)
{
	// RefreshWorldWidgetPanel();

	for (const auto& Panel : WorldWidgetPanels)
	{
		if (Panel->IsContain(WorldWidgetComponent))
		{
			Panel->RefreshWorldWidgetComponent(WorldWidgetComponent);
		}
		else
		{
			Panel->AddWorldWidgetComponent(WorldWidgetComponent);
		}
	}
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

#undef LOCTEXT_NAMESPACE
