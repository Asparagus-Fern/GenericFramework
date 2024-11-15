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

	/* 对视口创建新的Panel存放WorldWidget */
	ConstraintCanvas = SNew(SConstraintCanvas);
	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::AddToEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}

	RefreshWorldWidgetComponent();
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
					TempWorldWidget.Value->SetRenderTranslation(ResultPosition);
					continue;
				}
			}
		}

		TempWorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UEditorWorldWidgetPanel::NativeOnDestroy()
{
	UWorldWidgetPanel::NativeOnDestroy();

	for (const auto& WorldWidget : WorldWidgets)
	{
		ConstraintCanvas->RemoveSlot(WorldWidget.Value->TakeWidget());
		WorldWidget.Value->MarkAsGarbage();
	}

	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::RemoveFromEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}

	ConstraintCanvas.Reset();
	WorldWidgets.Reset();
	WorldWidgetContainer.Reset();
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
	WorldWidgets.Add(InWorldWidgetComponent, DuplicateWorldWidget);

	TSharedPtr<SWorldWidgetContainer> NewContainer = SNew(SWorldWidgetContainer)
		.OnWorldWidgetDoubleClicked_UObject(this, &UEditorWorldWidgetPanel::OnWorldWidgetDoubleClicked)
		[
			DuplicateWorldWidget->TakeWidget()
		];

	WorldWidgetContainer.FindOrAdd(InWorldWidgetComponent, NewContainer);

	ConstraintCanvas->AddSlot()
		.AutoSize(true)
		.Anchors(FAnchors())
		.Alignment(FVector2D())
		.Offset(FMargin())
		.ZOrder(DuplicateWorldWidget->ZOrder)
		[
			NewContainer.ToSharedRef()
		];
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
}

void UEditorWorldWidgetPanel::RefreshWorldWidgetComponent()
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

void UEditorWorldWidgetPanel::OnWorldWidgetDoubleClicked(TSharedPtr<SWorldWidgetContainer> DoubleClickedContainer)
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
	return Super::ShouldCreateSubsystem(Outer) && UWorldWidgetEdManagerSetting::Get()->bEnableSubsystem;
}

void UWorldWidgetEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	RegistManager(this);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdManager::OnLevelEditorCreated);

	LevelActorAddedHandle = GEditor->OnLevelActorAdded().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorAdded);
	ActorsMovedHandle = GEditor->OnActorsMoved().AddUObject(this, &UWorldWidgetEdManager::OnActorsMoved);
	LevelActorDeletedHandle = GEditor->OnLevelActorDeleted().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorDeleted);
	BlueprintCompiledHandle = GEditor->OnBlueprintCompiled().AddUObject(this, &UWorldWidgetEdManager::OnBlueprintCompiled);

	WorldWidgetComponentRegisterHandle = UWorldWidgetComponent::OnWorldWidgetComponentRegister.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetComponentRegister);

	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::Deinitialize()
{
	UnRegistManager();

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}

	WorldWidgetPanels.Reset();
	WorldWidgetComponents.Reset();
	bIsGenerateWorldWidgetPanel = false;

	LevelEditorCreatedHandle.Reset();
	LevelActorAddedHandle.Reset();
	ActorsMovedHandle.Reset();
	LevelActorDeletedHandle.Reset();
	BlueprintCompiledHandle.Reset();
	WorldWidgetComponentRegisterHandle.Reset();
}

bool UWorldWidgetEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UWorldWidgetEdManager::OnWorldBeginPlay(UWorld* InWorld)
{
	/* 运行时开始的时候把编辑器的3DUI清空 */
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}

	bIsGenerateWorldWidgetPanel = false;
	WorldWidgetPanels.Reset();
}

void UWorldWidgetEdManager::OnWorldEndPlay(UWorld* InWorld)
{
	/* 运行时结束时重新生成编辑器的3DUI */
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelActorAdded(AActor* Actor)
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnActorsMoved(TArray<AActor*>& Actors)
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelActorDeleted(AActor* InActor)
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnBlueprintCompiled()
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnWorldWidgetComponentRegister(UWorldWidgetComponent* WorldWidgetComponent)
{
	RefreshWorldWidgetPanel();
}

void UWorldWidgetEdManager::GenerateWorldWidgetPanel()
{
	if (bIsGenerateWorldWidgetPanel)
	{
		return;
	}

	TArray<FLevelEditorViewportClient*> LevelEditorViewportClients = GEditor->GetLevelViewportClients();
	for (const auto& LevelEditorViewportClient : LevelEditorViewportClients)
	{
		/* ActorLock是编辑器的相机窗口 todo:尝试添加到相机视口 */
		FLevelViewportActorLock& ActorLock = LevelEditorViewportClient->GetActorLock();
		const AActor* Actor = ActorLock.GetLockedActor();
		if (IsValid(Actor))
		{
			continue;
		}

		/* 添加到LevelEditorViewport */
		if (UEditorWorldWidgetPanel* EditorWorldWidgetPanel = Cast<UEditorWorldWidgetPanel>(CreateWorldWidgetPanel()))
		{
			if (!bIsGenerateWorldWidgetPanel)
			{
				bIsGenerateWorldWidgetPanel = true;
			}

			EditorWorldWidgetPanel->LevelEditorViewportClient = LevelEditorViewportClient;
			EditorWorldWidgetPanel->NativeOnCreate();
		}
	}

	/* todo:尝试添加到ActorPreview */
	//...
}

UWorldWidgetPanel* UWorldWidgetEdManager::CreateWorldWidgetPanel()
{
	UEditorWorldWidgetPanel* NewEditorWorldWidgetPanel = NewObject<UEditorWorldWidgetPanel>(this);
	WorldWidgetPanels.Add(NewEditorWorldWidgetPanel);

	return NewEditorWorldWidgetPanel;
}

#undef LOCTEXT_NAMESPACE
