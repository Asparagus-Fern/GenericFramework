// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WorldWidgetEdSubsystem.h"

#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "SEditorWorldWidget.h"
#include "WidgetType.h"
#include "WorldWidgetComponent.h"
#include "Base/GenericWidget.h"
#include "BPFunctions/BPFunctions_EditorScene.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "Type/DebugType.h"
#include "Widgets/Layout/SConstraintCanvas.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetEdGenerationModule"

FEditorWorldWidget::FEditorWorldWidget()
	: bInitialized(false)
{
}

void UWorldWidgetEdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdSubsystem::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UWorldWidgetEdSubsystem::OnLevelViewportClientListChanged);
	OnBlueprintCompiledHandle = GEditor->OnBlueprintCompiled().AddUObject(this, &UWorldWidgetEdSubsystem::OnBlueprintCompiled);

	GenerateEditorWorldWidgets();
	InitializeEditorWorldWidgets();
}

void UWorldWidgetEdSubsystem::Deinitialize()
{
	Super::Deinitialize();

	DeinitializeEditorWorldWidgets();
	EditorWorldWidgets.Reset();

	LevelEditorCreatedHandle.Reset();
	LevelViewportClientListChangedHandle.Reset();
	OnBlueprintCompiledHandle.Reset();
}

bool UWorldWidgetEdSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UWorldWidgetEdSubsystem::Tick(float DeltaTime)
{
	TArray<FEditorWorldWidget> TempEditorWorldWidgets = EditorWorldWidgets;
	for (auto& EditorWorldWidget : TempEditorWorldWidgets)
	{
		const FViewport* Viewport = EditorWorldWidget.LevelEditorViewportClient->Viewport;

		for (const auto& EditorWidget : EditorWorldWidget.EditorWorldWidgets)
		{
			if (!EditorWorldWidget.LevelEditorViewportClient->IsPerspective())
			{
				EditorWidget.Value->SetVisibility(EVisibility::Collapsed);
				continue;
			}

			FVector2D ScreenPosition;
			if (UBPFunctions_EditorWidget::EditorProjectWorldToScreen(EditorWorldWidget.LevelEditorViewportClient, EditorWidget.Key->GetComponentLocation(), ScreenPosition))
			{
				const FVector2D EditorWidgetSize = EditorWidget.Value->GetDesiredSize();
				const FVector2D EditorWidgetAnchor = EditorWidget.Key->WorldWidget->Anchor;

				const FVector2D ResultPosition = ScreenPosition + FVector2D(-(EditorWidgetSize.X * EditorWidgetAnchor.X), -(EditorWidgetSize.Y * EditorWidgetAnchor.Y));

				/* 超出屏幕大小时隐藏 */
				if (ResultPosition.X > -EditorWidgetSize.X && ResultPosition.X < Viewport->GetSizeXY().X && ResultPosition.Y > -EditorWidgetSize.Y && ResultPosition.Y < Viewport->GetSizeXY().Y)
				{
					EditorWidget.Value->SetVisibility(EVisibility::SelfHitTestInvisible);
					EditorWorldWidget.EditorWorldWidgetSlots.FindRef(EditorWidget.Key)->SetOffset(FMargin(ResultPosition.X, ResultPosition.Y, 0, 0));
					continue;
				}
			}

			EditorWidget.Value->SetVisibility(EVisibility::Collapsed);
		}
	}
}

void UWorldWidgetEdSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	if (InWorld.WorldType == EWorldType::PIE)
	{
		for (const auto& WorldWidgetComponent : WorldWidgetComponents)
		{
			RemoveWorldWidgetFromScreen(WorldWidgetComponent);
		}
	}
}

void UWorldWidgetEdSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	Super::OnWorldBeginTearDown(InWorld);

	InWorld->OnWorldBeginPlay.RemoveAll(this);
	if (InWorld->WorldType == EWorldType::PIE)
	{
		for (const auto& WorldWidgetComponent : WorldWidgetComponents)
		{
			AddWorldWidgetToScreen(WorldWidgetComponent);
		}
	}
}

void UWorldWidgetEdSubsystem::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	InitializeEditorWorldWidgets();
}

void UWorldWidgetEdSubsystem::OnLevelViewportClientListChanged()
{
	TArray<FEditorWorldWidget> TempEditorWorldWidgets = EditorWorldWidgets;
	for (auto& EditorWorldWidget : TempEditorWorldWidgets)
	{
		if (!UBPFunctions_EditorWidget::GetLevelEditorViewportClients().Contains(EditorWorldWidget.LevelEditorViewportClient))
		{
			UBPFunctions_EditorWidget::RemoveFromEditorViewport(EditorWorldWidget.LevelEditorViewportClient, EditorWorldWidget.ConstraintCanvas.ToSharedRef());
			EditorWorldWidgets.Remove(EditorWorldWidget);
		}
	}

	GenerateEditorWorldWidgets();
}

void UWorldWidgetEdSubsystem::OnBlueprintCompiled()
{
	for (const auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		RemoveWorldWidgetFromScreen(WorldWidgetComponent);
	}

	for (const auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		AddWorldWidgetToScreen(WorldWidgetComponent);
	}
}

void UWorldWidgetEdSubsystem::GenerateEditorWorldWidgets()
{
	for (const auto& LevelEditorViewportClient : UBPFunctions_EditorWidget::GetLevelEditorViewportClients())
	{
		if (!EditorWorldWidgets.Contains(LevelEditorViewportClient))
		{
			const TSharedRef<SConstraintCanvas> ConstraintCanvas = SNew(SConstraintCanvas);

			FEditorWorldWidget NewEditorWorldWidget = FEditorWorldWidget();
			NewEditorWorldWidget.LevelEditorViewportClient = LevelEditorViewportClient;
			NewEditorWorldWidget.ConstraintCanvas = ConstraintCanvas;
			EditorWorldWidgets.Add(NewEditorWorldWidget);
		}
	}
}

void UWorldWidgetEdSubsystem::InitializeEditorWorldWidgets()
{
	for (auto& EditorWorldWidget : EditorWorldWidgets)
	{
		if (!EditorWorldWidget.bInitialized)
		{
			UBPFunctions_EditorWidget::AddToEditorViewport(EditorWorldWidget.LevelEditorViewportClient, EditorWorldWidget.ConstraintCanvas.ToSharedRef());
			EditorWorldWidget.bInitialized = true;
		}
	}

	for (const auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		AddWorldWidgetToScreen(WorldWidgetComponent);
	}
}

void UWorldWidgetEdSubsystem::DeinitializeEditorWorldWidgets()
{
	for (const auto& WorldWidgetComponent : WorldWidgetComponents)
	{
		RemoveWorldWidgetFromScreen(WorldWidgetComponent);
	}

	for (auto& EditorWorldWidget : EditorWorldWidgets)
	{
		if (EditorWorldWidget.bInitialized)
		{
			UBPFunctions_EditorWidget::RemoveFromEditorViewport(EditorWorldWidget.LevelEditorViewportClient, EditorWorldWidget.ConstraintCanvas.ToSharedRef());
			EditorWorldWidget.bInitialized = false;
		}
	}
}

void UWorldWidgetEdSubsystem::RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	Super::RegisterWorldWidgetComponent(InWorldWidgetComponent);
	AddWorldWidgetToScreen(InWorldWidgetComponent);
}

void UWorldWidgetEdSubsystem::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	Super::UnRegisterWorldWidgetComponent(InWorldWidgetComponent);
	RemoveWorldWidgetFromScreen(InWorldWidgetComponent);
}

void UWorldWidgetEdSubsystem::AddWorldWidgetToScreen(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("WorldWidgetComponent Is InValid"))
		return;
	}

	if (InWorldWidgetComponent->WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen && IsValid(InWorldWidgetComponent->WorldWidget))
	{
		for (auto& EditorWorldWidget : EditorWorldWidgets)
		{
			if (EditorWorldWidget.EditorWorldWidgets.Contains(InWorldWidgetComponent))
			{
				continue;
			}

			UGenericWidget* DuplicateWorldWidget = DuplicateObject(InWorldWidgetComponent->WorldWidget, InWorldWidgetComponent);
			TSharedPtr<SEditorWorldWidget> NewEditorWorldWidget = SNew(SEditorWorldWidget)
				.OnWorldWidgetMiddleClicked_UObject(this, &UWorldWidgetEdSubsystem::OnWorldWidgetClicked)
				[
					DuplicateWorldWidget->TakeWidget()
				];

			SConstraintCanvas::FSlot* NewSlot;
			EditorWorldWidget.ConstraintCanvas->AddSlot()
				.Expose(NewSlot)
				.AutoSize(true)
				.Anchors(FAnchors())
				.Alignment(FVector2D())
				.Offset(FMargin())
				.ZOrder(DuplicateWorldWidget->ZOrder)
				[
					NewEditorWorldWidget.ToSharedRef()
				];

			EditorWorldWidget.EditorWorldWidgets.FindOrAdd(InWorldWidgetComponent, NewEditorWorldWidget);
			EditorWorldWidget.EditorWorldWidgetSlots.FindOrAdd(InWorldWidgetComponent, NewSlot);
		}
	}
}

void UWorldWidgetEdSubsystem::RemoveWorldWidgetFromScreen(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("WorldWidgetComponent Is InValid"))
		return;
	}

	if (IsValid(InWorldWidgetComponent->WorldWidget))
	{
		for (auto& EditorWorldWidget : EditorWorldWidgets)
		{
			if (EditorWorldWidget.EditorWorldWidgets.Contains(InWorldWidgetComponent))
			{
				TSharedPtr<SEditorWorldWidget> RemoveWidget = EditorWorldWidget.EditorWorldWidgets.FindRef(InWorldWidgetComponent);
				EditorWorldWidget.ConstraintCanvas->RemoveSlot(RemoveWidget.ToSharedRef());

				EditorWorldWidget.EditorWorldWidgets.Remove(InWorldWidgetComponent);
				EditorWorldWidget.EditorWorldWidgetSlots.Remove(InWorldWidgetComponent);
			}
		}
	}
}

void UWorldWidgetEdSubsystem::OnWorldWidgetClicked(TSharedPtr<SEditorWorldWidget> ClickedWorldWidget)
{
	if (!ClickedWorldWidget.IsValid())
	{
		return;
	}

	AActor* SelectedActor = nullptr;
	for (auto& EditorWorldWidget : EditorWorldWidgets)
	{
		TArray<TSharedPtr<SEditorWorldWidget>> Values;
		EditorWorldWidget.EditorWorldWidgets.GenerateValueArray(Values);

		for (auto& KeyValue : EditorWorldWidget.EditorWorldWidgets)
		{
			if (KeyValue.Value == ClickedWorldWidget)
			{
				SelectedActor = KeyValue.Key->GetOwner();
				break;
			}
		}
	}

	if (IsValid(SelectedActor))
	{
		UBPFunctions_EditorScene::SelectNone();
		UBPFunctions_EditorScene::SelectActor(SelectedActor, true);
	}
}

#undef LOCTEXT_NAMESPACE
