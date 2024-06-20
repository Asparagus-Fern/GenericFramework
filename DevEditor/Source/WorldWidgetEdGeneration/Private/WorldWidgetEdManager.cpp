// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldWidgetEdManager.h"

#include "EngineUtils.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "SLevelViewport.h"
#include "WorldWidget.h"
#include "WorldWidgetPoint.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager/ManagerCollection.h"
#include "StaticFunctions/StaticFunctions_LevelEditor.h"
#include "Widgets/Layout/SConstraintCanvas.h"


FEditorWorldWidgetPanel::FEditorWorldWidgetPanel(UWorldWidgetEdManager* InOwner, FLevelEditorViewportClient* InLevelEditorViewportClient)
	: FWorldWidgetPanel(InOwner),
	  LevelEditorViewportClient(InLevelEditorViewportClient)
{
}

FEditorWorldWidgetPanel::~FEditorWorldWidgetPanel()
{
}

void FEditorWorldWidgetPanel::NativeOnCreate()
{
	FWorldWidgetPanel::NativeOnCreate();

	ConstraintCanvas = SNew(SConstraintCanvas);
	if (LevelEditorViewportClient)
	{
		AddPanelToViewport();
	}
}

void FEditorWorldWidgetPanel::NativeOnRefresh()
{
	if (!IsValid(Owner) || !ConstraintCanvas.IsValid() || !LevelEditorViewportClient)
	{
		return;
	}

	for (const auto& WorldWidget : WorldWidgets)
	{
		if (LevelEditorViewportClient->IsActiveViewportType(LVT_Perspective))
		{
			const FViewport* Viewport = LevelEditorViewportClient->Viewport;

			/* 获取世界坐标转屏幕坐标 */
			FVector2D ScreenPosition;
			if (FStaticFunctions_LevelEditor::EditorProjectWorldToScreen(LevelEditorViewportClient, WorldWidget.Key->GetActorLocation(), ScreenPosition))
			{
				const FVector2D ResultPosition = ScreenPosition + WorldWidget.Value->GetAnchorOffset();

				/* 超出屏幕大小时隐藏 */
				if ((ResultPosition.X > 0) && (ResultPosition.X < Viewport->GetSizeXY().X) && (ResultPosition.Y > 0) && (ResultPosition.Y < Viewport->GetSizeXY().Y))
				{
					WorldWidget.Value->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					// CanvasPanelSlot->SetPosition(ResultPosition);
					WorldWidget.Value->SetRenderTranslation(ResultPosition);
					continue;
				}
			}
		}

		WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void FEditorWorldWidgetPanel::NativeOnDestroy()
{
	FWorldWidgetPanel::NativeOnDestroy();

	RemovePanelFromViewport();

	ConstraintCanvas.Reset();
	LevelEditorViewportClient = nullptr;
}

void FEditorWorldWidgetPanel::NativeOnActived()
{
	FWorldWidgetPanel::NativeOnActived();
}

void FEditorWorldWidgetPanel::NativeOnInactived()
{
	FWorldWidgetPanel::NativeOnInactived();
}

void FEditorWorldWidgetPanel::AddPanelToViewport()
{
	if (ConstraintCanvas.IsValid() && LevelEditorViewportClient)
	{
		FStaticFunctions_LevelEditor::AddToViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}
}

void FEditorWorldWidgetPanel::RemovePanelFromViewport()
{
	if (ConstraintCanvas.IsValid() && LevelEditorViewportClient)
	{
		FStaticFunctions_LevelEditor::RemoveFromViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef());
	}
}

void FEditorWorldWidgetPanel::AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!IsValid(InWorldWidgetPoint) || !InWorldWidgetPoint->bPreview || !IsValid(InWorldWidgetPoint->WorldWidget) || !ConstraintCanvas.IsValid())
	{
		return;
	}

	if (!WorldWidgets.Contains(InWorldWidgetPoint))
	{
		UWorldWidget* DuplicateWorldWidget = DuplicateObject(InWorldWidgetPoint->WorldWidget, InWorldWidgetPoint);
		WorldWidgets.Add(InWorldWidgetPoint, DuplicateWorldWidget);

		ConstraintCanvas->AddSlot()
			.AutoSize(true)
			.Anchors(FAnchors())
			.Alignment(FVector2D())
			.Offset(FMargin())
			[
				DuplicateWorldWidget->TakeWidget()
			];
	}
}

void FEditorWorldWidgetPanel::RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (WorldWidgets.Contains(InWorldWidgetPoint) && ConstraintCanvas.IsValid())
	{
		ConstraintCanvas->RemoveSlot(WorldWidgets.FindRef(InWorldWidgetPoint)->TakeWidget());
		WorldWidgets.Remove(InWorldWidgetPoint);
	}
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

UWorldWidgetEdManager::UWorldWidgetEdManager()
{
	DisplayName = LOCTEXT("DisplayName", "World Widget Editor Manager");
	ProcedureOrder = 0;
}

void UWorldWidgetEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	/* 在世界被创建时和世界切换时更新 */
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdManager::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UWorldWidgetEdManager::OnLevelViewportClientListChanged);
	BlueprintCompiledHandle = GEditor->OnBlueprintCompiled().AddUObject(this, &UWorldWidgetEdManager::OnBlueprintCompiled);
	LevelActorDeletedHandle = GEditor->OnLevelActorDeleted().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorDeleted);
	FWorldWidgetDelegates::OnWorldWidgetPointConstruction.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetPointConstruction);
}

void UWorldWidgetEdManager::Deinitialize()
{
	Super::Deinitialize();
}

UWorldWidgetEdManager* UWorldWidgetEdManager::Get()
{
	return FManagerCollection::Get()->GetManager<UWorldWidgetEdManager>();
}

void UWorldWidgetEdManager::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	if (IsValid(GetWorld()) && IsWorldType(EWorldType::Editor) && !WorldWidgetPanels.IsEmpty())
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

void UWorldWidgetEdManager::NativeOnActived()
{
	Super::NativeOnActived();

	if (IsWorldType(EWorldType::Editor))
	{
		OnLevelViewportClientListChanged();
		CollectWorldWidgetPoints();
	}
}

void UWorldWidgetEdManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	if (IsWorldType(EWorldType::Editor))
	{
		EditorWorldWidgetPanelMapping.Reset();
	}
}

void UWorldWidgetEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	RefreshAllPanelWorldWidgetPoint();
}

void UWorldWidgetEdManager::OnLevelViewportClientListChanged()
{
	for (const auto& LevelEditorViewportClient : GEditor->GetLevelViewportClients())
	{
		if (LevelEditorViewportClient && !EditorWorldWidgetPanelMapping.Contains(LevelEditorViewportClient))
		{
			CreateEditorWorldWidgetPanel(LevelEditorViewportClient);
		}
	}
}

void UWorldWidgetEdManager::OnBlueprintCompiled()
{
	ReCreateEditorWorldWidgetPanel();
}

void UWorldWidgetEdManager::OnLevelActorDeleted(AActor* InActor)
{
	if (AWorldWidgetPoint* WorldWidgetPoint = Cast<AWorldWidgetPoint>(InActor))
	{
		ReCreateEditorWorldWidgetPanel();
	}
}

void UWorldWidgetEdManager::OnWorldWidgetPointConstruction(AWorldWidgetPoint* InWorldWidgetPoint)
{
	RefreshWolrdWidgetPoint(InWorldWidgetPoint);
}

void UWorldWidgetEdManager::ReCreateEditorWorldWidgetPanel()
{
	ClearWorldWidgetPanel();
	WorldWidgetPoints.Reset();
	EditorWorldWidgetPanelMapping.Reset();

	OnLevelViewportClientListChanged();
	CollectWorldWidgetPoints();
}

FEditorWorldWidgetPanel* UWorldWidgetEdManager::CreateEditorWorldWidgetPanel(FLevelEditorViewportClient* InLevelEditorViewportClient)
{
	FEditorWorldWidgetPanel* NewWorldWidgetPanel = new FEditorWorldWidgetPanel(this, InLevelEditorViewportClient);
	NewWorldWidgetPanel->NativeOnCreate();
	WorldWidgetPanels.Add(NewWorldWidgetPanel);
	EditorWorldWidgetPanelMapping.Add(InLevelEditorViewportClient, NewWorldWidgetPanel);
	NewWorldWidgetPanel->NativeOnActived();

	return NewWorldWidgetPanel;
}

void UWorldWidgetEdManager::CollectWorldWidgetPoints()
{
	if (GetWorld())
	{
		for (TActorIterator<AWorldWidgetPoint> It(GetWorld()); It; ++It)
		{
			if (!WorldWidgetPoints.Contains(*It))
			{
				WorldWidgetPoints.Add(*It);

				for (const auto& WorldWidgetPanel : WorldWidgetPanels)
				{
					WorldWidgetPanel->AddWorldWidget(*It);
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
