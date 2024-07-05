// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldWidgetEdManager.h"

#include "EngineUtils.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "WorldWidget.h"
#include "WorldWidgetPoint.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager/ManagerEdGlobal.h"
#include "StaticFunctions/StaticFunctions_LevelEditor.h"
#include "Widgets/Layout/SConstraintCanvas.h"

void UEditorWorldWidgetPanel::NativeOnCreate()
{
	UWorldWidgetPanel::NativeOnCreate();

	ConstraintCanvas = SNew(SConstraintCanvas);
	if (LevelEditorViewportClient)
	{
		AddPanelToViewport();
	}
}

void UEditorWorldWidgetPanel::NativeOnRefresh()
{
	if (!ConstraintCanvas.IsValid() || !LevelEditorViewportClient)
	{
		return;
	}

	for (const auto& WorldWidget : WorldWidgets)
	{
		if (!IsValid(WorldWidget.Value))
		{
			continue;
		}

		if (WorldWidget.Key->IsActorBeingDestroyed())
		{
			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		if (WorldWidget.Key->IsHiddenEd() || WorldWidget.Key->IsHidden())
		{
			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		if (!LevelEditorViewportClient->IsPerspective())
		{
			WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		if (const FViewport* Viewport = LevelEditorViewportClient->Viewport)
		{
			/* 获取世界坐标转屏幕坐标 */
			FVector2D ScreenPosition;
			if (FStaticFunctions_LevelEditor::EditorProjectWorldToScreen(LevelEditorViewportClient, WorldWidget.Key->GetActorLocation(), ScreenPosition))
			{
				const FVector2D ResultPosition = ScreenPosition + WorldWidget.Value->GetAnchorOffset();

				/* 超出屏幕大小时隐藏 */
				if (ResultPosition.X > 0 && ResultPosition.X < Viewport->GetSizeXY().X && ResultPosition.Y > 0 && ResultPosition.Y < Viewport->GetSizeXY().Y)
				{
					WorldWidget.Value->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					WorldWidget.Value->SetRenderTranslation(ResultPosition);
					continue;
				}
			}
		}

		WorldWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UEditorWorldWidgetPanel::NativeOnDestroy()
{
	UWorldWidgetPanel::NativeOnDestroy();

	RemovePanelFromViewport();
	ConstraintCanvas.Reset();
	LevelEditorViewportClient = nullptr;
}

void UEditorWorldWidgetPanel::NativeOnActived()
{
	UWorldWidgetPanel::NativeOnActived();

	if (ConstraintCanvas.IsValid())
	{
		ConstraintCanvas->SetVisibility(EVisibility::SelfHitTestInvisible);
	}
}

void UEditorWorldWidgetPanel::NativeOnInactived()
{
	UWorldWidgetPanel::NativeOnInactived();

	if (ConstraintCanvas.IsValid())
	{
		ConstraintCanvas->SetVisibility(EVisibility::Collapsed);
	}
}

bool UEditorWorldWidgetPanel::AddPanelToViewport()
{
	if (ConstraintCanvas.IsValid() && LevelEditorViewportClient)
	{
		if (FStaticFunctions_LevelEditor::AddToViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef()))
		{
			bRegisterInViewport = true;
			return true;
		}
	}

	return false;;
}

bool UEditorWorldWidgetPanel::RemovePanelFromViewport()
{
	if (ConstraintCanvas.IsValid() && LevelEditorViewportClient)
	{
		if (FStaticFunctions_LevelEditor::RemoveFromViewport(LevelEditorViewportClient, ConstraintCanvas.ToSharedRef()))
		{
			bRegisterInViewport = false;
			return true;
		}
	}

	return false;;
}

void UEditorWorldWidgetPanel::AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (!IsValid(InWorldWidgetPoint) || !InWorldWidgetPoint->bPreview || !IsValid(InWorldWidgetPoint->WorldWidget) || !ConstraintCanvas.IsValid())
	{
		return;
	}

	if (!bRegisterInViewport)
	{
		if (!AddPanelToViewport())
		{
			return;
		}
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

void UEditorWorldWidgetPanel::RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint)
{
	if (WorldWidgets.Contains(InWorldWidgetPoint) && ConstraintCanvas.IsValid() && bRegisterInViewport)
	{
		ConstraintCanvas->RemoveSlot(WorldWidgets.FindRef(InWorldWidgetPoint)->TakeWidget());
		UWorldWidget* RemoveWidget = WorldWidgets.FindAndRemoveChecked(InWorldWidgetPoint);
		RemoveWidget->MarkAsGarbage();
	}
}

#define LOCTEXT_NAMESPACE "UWorldWidgetManager"

UWorldWidgetEdManager::UWorldWidgetEdManager()
{
	bInitializeEditorWorldWidgetPanel = false;
}

FText UWorldWidgetEdManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "World Widget Editor Manager");
}

bool UWorldWidgetEdManager::DoesSupportWorldType(EWorldType::Type InWorldType)
{
	return Super::DoesSupportWorldType(InWorldType) || EWorldType::Editor;
}

void UWorldWidgetEdManager::NativeOnCreate()
{
	Super::NativeOnCreate();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorCreatedHandle = LevelEditorModule.OnLevelEditorCreated().AddUObject(this, &UWorldWidgetEdManager::OnLevelEditorCreated);

	LevelViewportClientListChangedHandle = GEditor->OnLevelViewportClientListChanged().AddUObject(this, &UWorldWidgetEdManager::OnLevelViewportClientListChanged);
}

void UWorldWidgetEdManager::NativeOnDestroy()
{
	Super::NativeOnDestroy();

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.OnLevelEditorCreated().Remove(LevelEditorCreatedHandle);

	GEditor->OnLevelViewportClientListChanged().Remove(LevelViewportClientListChangedHandle);
}

void UWorldWidgetEdManager::NativeOnRefresh()
{
	Super::NativeOnRefresh();

	if (!IsValid(GetWorld()) && IsValid(FManagerEdGlobal::GetEditorWorld()))
	{
		if (!WorldWidgetPanels.IsEmpty())
		{
			for (const auto& WorldWidgetPanel : WorldWidgetPanels)
			{
				if (FLevelEditorViewportClient* FoundLevelEditorViewportClient = *EditorWorldWidgetPanelMapping.FindKey(WorldWidgetPanel))
				{
					if (!HandleLevelEditorViewportClients.Contains(FoundLevelEditorViewportClient))
					{
						if (WorldWidgetPanel->GetIsActive())
						{
							WorldWidgetPanel->NativeOnRefresh();
						}
					}
				}
			}
		}
	}
}

void UWorldWidgetEdManager::NativeOnEditorActived()
{
	IManagerEdInterface::NativeOnEditorActived();

	BlueprintCompiledHandle = GEditor->OnBlueprintCompiled().AddUObject(this, &UWorldWidgetEdManager::OnBlueprintCompiled);
	LevelActorDeletedHandle = GEditor->OnLevelActorDeleted().AddUObject(this, &UWorldWidgetEdManager::OnLevelActorDeleted);

	WorldWidgetPointConstructionHandle = FWorldWidgetDelegates::OnWorldWidgetPointConstruction.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetPointConstruction);
	WorldWidgetPointDestroyedHandle = FWorldWidgetDelegates::OnWorldWidgetPointDestroy.AddUObject(this, &UWorldWidgetEdManager::OnWorldWidgetPointDestroyed);

	CollectWorldWidgetPoints();
	OnLevelViewportClientListChanged();
	RefreshAllPanelWorldWidgetPoint();
}

void UWorldWidgetEdManager::NativeOnEditorInactived()
{
	IManagerEdInterface::NativeOnEditorInactived();

	ClearupWorldWidgetPanel();

	bInitializeEditorWorldWidgetPanel = false;
	HandleLevelEditorViewportClients.Reset();
	WorldWidgetPoints.Reset();
	EditorWorldWidgetPanelMapping.Reset();

	GEditor->OnBlueprintCompiled().Remove(BlueprintCompiledHandle);
	GEditor->OnLevelActorDeleted().Remove(LevelActorDeletedHandle);

	FWorldWidgetDelegates::OnWorldWidgetPointConstruction.Remove(WorldWidgetPointConstructionHandle);
	FWorldWidgetDelegates::OnWorldWidgetPointDestroy.Remove(WorldWidgetPointDestroyedHandle);
}

void UWorldWidgetEdManager::OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor)
{
	// CollectWorldWidgetPoints();
	// RefreshAllPanelWorldWidgetPoint();
}

void UWorldWidgetEdManager::OnLevelViewportClientListChanged()
{
	const TArray<FLevelEditorViewportClient*> PreLevelEditorViewportClientsArray = GEditor->GetLevelViewportClients();
	TArray<FLevelEditorViewportClient*> CurrentLevelEditorViewportClientsArray;
	EditorWorldWidgetPanelMapping.GetKeys(CurrentLevelEditorViewportClientsArray);

	const TSet<FLevelEditorViewportClient*> PreLevelEditorViewportClients(PreLevelEditorViewportClientsArray);
	const TSet<FLevelEditorViewportClient*> CurrentLevelEditorViewportClients(CurrentLevelEditorViewportClientsArray);

	TSet<FLevelEditorViewportClient*> Intersection;
	if (PreLevelEditorViewportClients.Num() > CurrentLevelEditorViewportClients.Num())
	{
		Intersection = PreLevelEditorViewportClients.Intersect(CurrentLevelEditorViewportClients);
		HandleLevelEditorViewportClients = PreLevelEditorViewportClients.Difference(Intersection).Array();
	}
	else
	{
		Intersection = CurrentLevelEditorViewportClients.Intersect(PreLevelEditorViewportClients);
		HandleLevelEditorViewportClients = CurrentLevelEditorViewportClients.Difference(Intersection).Array();
	}

	if (FManagerEdGlobal::GetEditorWorld())
	{
		LevelViewportClientListChangedNextTickHandle = FManagerEdGlobal::GetEditorWorld()->GetTimerManager().SetTimerForNextTick(this, &UWorldWidgetEdManager::HandleLevelViewportClientListChangedNextTick);
	}
}

void UWorldWidgetEdManager::HandleLevelViewportClientListChangedNextTick()
{
	for (const auto& HandleLevelEditorViewportClient : HandleLevelEditorViewportClients)
	{
		FLevelViewportActorLock& ActorLock = HandleLevelEditorViewportClient->GetActorLock();
		const AActor* Actor = ActorLock.GetLockedActor();
		if (IsValid(Actor))
		{
			continue;
		}

		if (HandleLevelEditorViewportClient)
		{
			if (!EditorWorldWidgetPanelMapping.Contains(HandleLevelEditorViewportClient))
			{
				CreateEditorWorldWidgetPanel(HandleLevelEditorViewportClient);
			}
			else
			{
				RemoveEditorWorldWidgetPanel(HandleLevelEditorViewportClient);
			}
		}
	}

	HandleLevelEditorViewportClients.Reset();

	if (!bInitializeEditorWorldWidgetPanel)
	{
		bInitializeEditorWorldWidgetPanel = !bInitializeEditorWorldWidgetPanel;
		CollectWorldWidgetPoints();
		RefreshAllPanelWorldWidgetPoint();
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

void UWorldWidgetEdManager::OnWorldWidgetPointDestroyed(AWorldWidgetPoint* InWorldWidgetPoint)
{
	RefreshWolrdWidgetPoint(InWorldWidgetPoint);
}

void UWorldWidgetEdManager::ReCreateEditorWorldWidgetPanel()
{
	ClearupWorldWidgetPanel();
	WorldWidgetPoints.Reset();
	EditorWorldWidgetPanelMapping.Reset();

	OnLevelViewportClientListChanged();
	CollectWorldWidgetPoints();
}

UEditorWorldWidgetPanel* UWorldWidgetEdManager::CreateEditorWorldWidgetPanel(FLevelEditorViewportClient* InLevelEditorViewportClient)
{
	UEditorWorldWidgetPanel* NewWorldWidgetPanel = NewObject<UEditorWorldWidgetPanel>(this);
	NewWorldWidgetPanel->LevelEditorViewportClient = InLevelEditorViewportClient;
	WorldWidgetPanels.Add(NewWorldWidgetPanel);
	EditorWorldWidgetPanelMapping.Add(InLevelEditorViewportClient, NewWorldWidgetPanel);

	NewWorldWidgetPanel->NativeOnCreate();
	NewWorldWidgetPanel->NativeOnActived();

	return NewWorldWidgetPanel;
}

void UWorldWidgetEdManager::RemoveEditorWorldWidgetPanel(FLevelEditorViewportClient* InLevelEditorViewportClient)
{
	if (EditorWorldWidgetPanelMapping.Contains(InLevelEditorViewportClient))
	{
		if (UWorldWidgetPanel* FoundWorldWidgetPanel = EditorWorldWidgetPanelMapping.FindRef(InLevelEditorViewportClient))
		{
			FoundWorldWidgetPanel->NativeOnDestroy();
			WorldWidgetPanels.Remove(FoundWorldWidgetPanel);
			EditorWorldWidgetPanelMapping.Remove(InLevelEditorViewportClient);
		}
	}
}

void UWorldWidgetEdManager::CollectWorldWidgetPoints()
{
	if (FManagerEdGlobal::GetEditorWorld())
	{
		for (TActorIterator<AWorldWidgetPoint> It(FManagerEdGlobal::GetEditorWorld()); It; ++It)
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
