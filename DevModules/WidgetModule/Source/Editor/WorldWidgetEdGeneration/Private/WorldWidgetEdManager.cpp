// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WorldWidgetEdManager.h"

#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "SEditorWorldWidget.h"
#include "WidgetType.h"
#include "WorldWidgetComponent.h"
#include "Base/GenericWidget.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"

#define LOCTEXT_NAMESPACE "FWorldWidgetEdGenerationModule"

FEditorWorldWidget::FEditorWorldWidget()
	: bInitialized(false)
{
}

bool UWorldWidgetEdManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWorldWidgetEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdManager::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UWorldWidgetEdManager::OnLevelViewportClientListChanged);

	GenerateEditorWorldWidgets();
	InitializeEditorWorldWidgets();
}

void UWorldWidgetEdManager::Deinitialize()
{
	Super::Deinitialize();

	DeinitializeEditorWorldWidgets();
	EditorWorldWidgets.Reset();

	LevelEditorCreatedHandle.Reset();
	LevelViewportClientListChangedHandle.Reset();
}

bool UWorldWidgetEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UWorldWidgetEdManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void UWorldWidgetEdManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	Super::HandleOnWorldBeginPlay(InWorld);

	for (const auto& EditorWorldWidget : EditorWorldWidgets)
	{
		UBPFunctions_EditorWidget::RemoveFromEditorViewport(EditorWorldWidget.LevelEditorViewportClient, EditorWorldWidget.ConstraintCanvas.ToSharedRef());
	}
}

void UWorldWidgetEdManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	Super::HandleOnWorldEndPlay(InWorld);

	for (const auto& EditorWorldWidget : EditorWorldWidgets)
	{
		UBPFunctions_EditorWidget::AddToEditorViewport(EditorWorldWidget.LevelEditorViewportClient, EditorWorldWidget.ConstraintCanvas.ToSharedRef());
	}
}

void UWorldWidgetEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	InitializeEditorWorldWidgets();
}

void UWorldWidgetEdManager::OnLevelViewportClientListChanged()
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

void UWorldWidgetEdManager::GenerateEditorWorldWidgets()
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

void UWorldWidgetEdManager::InitializeEditorWorldWidgets()
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

void UWorldWidgetEdManager::DeinitializeEditorWorldWidgets()
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

void UWorldWidgetEdManager::RegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	Super::RegisterWorldWidgetComponent(InWorldWidgetComponent);
	AddWorldWidgetToScreen(InWorldWidgetComponent);
}

void UWorldWidgetEdManager::UnRegisterWorldWidgetComponent(UWorldWidgetComponent* InWorldWidgetComponent)
{
	Super::UnRegisterWorldWidgetComponent(InWorldWidgetComponent);
	RemoveWorldWidgetFromScreen(InWorldWidgetComponent);
}

void UWorldWidgetEdManager::AddWorldWidgetToScreen(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("WorldWidgetComponent Is NULL"))
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

void UWorldWidgetEdManager::RemoveWorldWidgetFromScreen(UWorldWidgetComponent* InWorldWidgetComponent)
{
	if (!IsValid(InWorldWidgetComponent))
	{
		GenericLOG(GenericLogUI, Error, TEXT("WorldWidgetComponent Is NULL"))
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

#undef LOCTEXT_NAMESPACE
