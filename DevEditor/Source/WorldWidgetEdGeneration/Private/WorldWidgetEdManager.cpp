// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldWidgetEdManager.h"

#include "EngineUtils.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "SWorldWidgetContainer.h"
#include "UnrealEdGlobals.h"
#include "WorldWidget.h"
#include "WorldWidgetEdManagerSetting.h"
#include "WorldWidgetPoint.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Editor/UnrealEdEngine.h"
#include "Widgets/Layout/SConstraintCanvas.h"

void UEditorWorldWidgetPanel::NativeOnCreate()
{
	UWorldWidgetPanel::NativeOnCreate();

	ConstraintCanvas = SNew(SConstraintCanvas);
	if (LevelEditorViewportClient)
	{
		UBPFunctions_EditorWidget::AddToEditorViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}

	RefreshWorldWidgetPoint();
}

void UEditorWorldWidgetPanel::NativeOnRefresh()
{
	if (!ConstraintCanvas.IsValid() || !LevelEditorViewportClient)
	{
		return;
	}

	/* 遍历所有的Widget并更新其位置 */
	TMap<AWorldWidgetPoint*, UUserWidgetBase*> TempWorldWidgets = WorldWidgets;
	for (const auto& TempWorldWidget : TempWorldWidgets)
	{
		if (!IsValid(TempWorldWidget.Value))
		{
			WorldWidgets.Remove(TempWorldWidget.Key);
			continue;
		}

		if (TempWorldWidget.Key->IsHiddenEd())
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
			if (UBPFunctions_EditorWidget::EditorProjectWorldToScreen(LevelEditorViewportClient, TempWorldWidget.Key->GetActorLocation(), ScreenPosition))
			{
				const FVector2D ResultPosition = ScreenPosition + TempWorldWidget.Value->GetAnchorOffset();

				/* 超出屏幕大小时隐藏 */
				if (ResultPosition.X > 0 && ResultPosition.X < Viewport->GetSizeXY().X && ResultPosition.Y > 0 && ResultPosition.Y < Viewport->GetSizeXY().Y)
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

void UEditorWorldWidgetPanel::RefreshWorldWidgetPoint()
{
	for (const auto& WorldWidget : WorldWidgets)
	{
		ConstraintCanvas->RemoveSlot(WorldWidgetContainer.FindRef(WorldWidget.Key).ToSharedRef());
		WorldWidget.Value->MarkAsGarbage();
	}

	WorldWidgets.Reset();
	WorldWidgetContainer.Reset();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (AWorldWidgetPoint* WorldWidgetPoint = Cast<AWorldWidgetPoint>(Actor))
		{
			if (WorldWidgets.Contains(WorldWidgetPoint))
			{
				continue;
			}

			if (!IsValid(WorldWidgetPoint->WorldWidget))
			{
				LOG(Debug_UI, Error, TEXT("WorldWidget Is NULL"))
				continue;
			}

			if (!WorldWidgetPoint->bPreview)
			{
				LOG(Debug_UI, Error, TEXT("Preview Is False"))
				continue;
			}

			if (!WorldWidgets.Contains(WorldWidgetPoint))
			{
				UUserWidgetBase* DuplicateWorldWidget = DuplicateObject(WorldWidgetPoint->WorldWidget, WorldWidgetPoint);
				WorldWidgets.Add(WorldWidgetPoint, DuplicateWorldWidget);

				TSharedPtr<SWorldWidgetContainer> NewContainer = SNew(SWorldWidgetContainer)
					.OnWorldWidgetDoubleClicked_UObject(this, &UEditorWorldWidgetPanel::OnWorldWidgetDoubleClicked)
					[
						DuplicateWorldWidget->TakeWidget()
					];

				WorldWidgetContainer.FindOrAdd(WorldWidgetPoint, NewContainer);

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
		}
	}
}

void UEditorWorldWidgetPanel::OnWorldWidgetDoubleClicked(TSharedPtr<SWorldWidgetContainer> DoubleClickedContainer)
{
	if (WorldWidgetContainer.FindKey(DoubleClickedContainer))
	{
		AWorldWidgetPoint* WorldWidgetPoint = *WorldWidgetContainer.FindKey(DoubleClickedContainer);

		if (GEditor->CanSelectActor(WorldWidgetPoint, true))
		{
			GEditor->SelectNone(false, true, false);
			GEditor->SelectActor(WorldWidgetPoint, true, true, true);
		}
	}
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

bool UWorldWidgetEdManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UWorldWidgetEdManagerSetting::Get()->bEnableSubsystem;
}

bool UWorldWidgetEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UWorldWidgetEdManager::NativeOnCreate()
{
	Super::NativeOnCreate();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdManager::OnLevelEditorCreated);

	LevelActorAddedHandle = GEditor->OnLevelActorAdded().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorAdded);
	ActorsMovedHandle = GEditor->OnActorsMoved().AddUObject(this, &UWorldWidgetEdManager::OnActorsMoved);
	LevelActorDeletedHandle = GEditor->OnLevelActorDeleted().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorDeleted);
	BlueprintCompiledHandle = GEditor->OnBlueprintCompiled().AddUObject(this, &UWorldWidgetEdManager::OnBlueprintCompiled);

	BeginPIEHandle = FEditorDelegates::BeginPIE.AddUObject(this, &UWorldWidgetEdManager::BeginPIE);
	EndPIEHandle = FEditorDelegates::EndPIE.AddUObject(this, &UWorldWidgetEdManager::EndPIE);

	WorldWidgetPointConstructHandle = AWorldWidgetPoint::OnWorldWidgetPointConstruct.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetPointConstruct);

	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::NativeOnDestroy()
{
	Super::NativeOnDestroy();

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}

	WorldWidgetPanels.Reset();
	WorldWidgetPoints.Reset();
	bIsGenerateWorldWidgetPanel = false;

	LevelEditorCreatedHandle.Reset();
	LevelActorAddedHandle.Reset();
	ActorsMovedHandle.Reset();
	LevelActorDeletedHandle.Reset();
	BlueprintCompiledHandle.Reset();
	BeginPIEHandle.Reset();
	EndPIEHandle.Reset();
	WorldWidgetPointConstructHandle.Reset();
}

void UWorldWidgetEdManager::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnRefresh();
	}
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

void UWorldWidgetEdManager::BeginPIE(bool bIsSimulating)
{
	for (const auto& WorldWidgetPanel : WorldWidgetPanels)
	{
		WorldWidgetPanel->NativeOnDestroy();
		WorldWidgetPanel->MarkAsGarbage();
	}

	bIsGenerateWorldWidgetPanel = false;
	WorldWidgetPanels.Reset();
}

void UWorldWidgetEdManager::EndPIE(bool bIsSimulating)
{
	GenerateWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnWorldWidgetPointConstruct(AWorldWidgetPoint* WorldWidgetPoint)
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
		/* ActorLock是编辑器的相机窗口 */
		FLevelViewportActorLock& ActorLock = LevelEditorViewportClient->GetActorLock();
		const AActor* Actor = ActorLock.GetLockedActor();
		if (IsValid(Actor))
		{
			continue;
		}

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
}

UWorldWidgetPanel* UWorldWidgetEdManager::CreateWorldWidgetPanel()
{
	UEditorWorldWidgetPanel* NewEditorWorldWidgetPanel = NewObject<UEditorWorldWidgetPanel>(this);
	WorldWidgetPanels.Add(NewEditorWorldWidgetPanel);

	return NewEditorWorldWidgetPanel;
}

#undef LOCTEXT_NAMESPACE
