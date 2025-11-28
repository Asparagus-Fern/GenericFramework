// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WorldWidgetComponent.h"

#include "WidgetType.h"
#include "Animation/WidgetAnimation.h"
#include "Base/GenericWidget.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Components/WidgetComponent.h"
#include "Type/DebugType.h"
#include "Kismet/KismetMathLibrary.h"

#if WITH_EDITOR
#include "LevelEditorViewport.h"
#endif

UE_DEFINE_GAMEPLAY_TAG(TAG_WorldWidget, "UI.WorldWidget");

UWorldWidgetComponent::UWorldWidgetComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
	bAutoActivate = true;

	Space = EWidgetSpace::Screen;
	bDrawAtDesiredSize = false;
	BlendMode = EWidgetBlendMode::Transparent;
	TintColorAndOpacity = FLinearColor::White;
	bManuallyRedraw = false;
	DrawSize = FIntPoint::ZeroValue;
	bReceiveHardwareInput = true;

	WidgetVisibility = bAutoActivate;

	bIsActived = bAutoActivate;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TranslucentMaterial_OneSided_Finder(TEXT("/Script/Engine.MaterialInstanceConstant'/GenericWidget/Material/Widget3DPassThrough_Translucent_OneSided.Widget3DPassThrough_Translucent_OneSided'"));
	if (TranslucentMaterial_OneSided_Finder.Succeeded())
	{
		TranslucentMaterial_OneSided = TranslucentMaterial_OneSided_Finder.Object;
	}
}

void UWorldWidgetComponent::OnRegister()
{
	Super::OnRegister();
	UpdateWorldWidget();
	OnWorldWidgetComponentRegister.Broadcast(this);
}

void UWorldWidgetComponent::OnUnregister()
{
	Super::OnUnregister();
	OnWorldWidgetComponentUnRegister.Broadcast(this);
}

void UWorldWidgetComponent::SetActive(bool bNewActive, bool bReset)
{
	bIsActived = bNewActive;

	if (bNewActive)
	{
		Super::SetActive(bNewActive, bReset);
	}
	else
	{
		ChangeWidgetActiveState(false);
	}
}

void UWorldWidgetComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	ChangeWidgetActiveState(true);
}

void UWorldWidgetComponent::Deactivate()
{
	Super::Deactivate();
}

void UWorldWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateWorldWidgetLookAtRotation();
}

void UWorldWidgetComponent::SetWorldWidgetPaintMethod(EWorldWidgetPaintMethod InMethod)
{
	WorldWidgetPaintMethod = InMethod;
	UpdateWorldWidget();
}

void UWorldWidgetComponent::SetWorldWidgetLookAtSetting(const FWorldWidgetLookAtSetting& InSetting)
{
	WorldWidgetLookAtSetting = InSetting;
}

void UWorldWidgetComponent::SetWorldWidgetByClass(TSubclassOf<UGenericWidget> InWorldWidgetClass)
{
	if (!InWorldWidgetClass)
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWorldWidgetClass Is InValid"))
		return;
	}

	WorldWidget = CreateWidget<UGenericWidget>(UBPFunctions_Gameplay::GetPlayerControllerByIndex(this, APlayerController::StaticClass(), 0), InWorldWidgetClass);
	UpdateWorldWidget();
}

void UWorldWidgetComponent::SetWorldWidget(UGenericWidget* InWorldWidget)
{
	if (!IsValid(InWorldWidget))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWorldWidget Is InValid"))
		return;
	}

	WorldWidget = InWorldWidget;
	UpdateWorldWidget();
}

void UWorldWidgetComponent::SetWidgetVisibility(const bool InWidgetVisibility)
{
	if (WidgetVisibility != InWidgetVisibility)
	{
		WidgetVisibility = InWidgetVisibility;
		ChangeWidgetActiveState(WidgetVisibility);
	}
}

void UWorldWidgetComponent::ChangeWidgetActiveState(bool IsActive)
{
	if (!IsValid(WorldWidget))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("WorldWidget Is InValid"))
		SetDrawSize(FIntPoint::ZeroValue);
		return;
	}

	if (WidgetActiveAnimationFinishBinding.IsBound() && WidgetActiveAnimationFinishBinding.GetUObject() != WorldWidget)
	{
		WidgetActiveAnimationFinishBinding.Unbind();
	}

	if (WidgetInactiveAnimationFinishBinding.IsBound() && WidgetInactiveAnimationFinishBinding.GetUObject() != WorldWidget)
	{
		WidgetInactiveAnimationFinishBinding.Unbind();
	}

	UWidgetAnimation* ActiveAnimation = WorldWidget->GetActiveAnimation();
	UWidgetAnimation* InactiveAnimation = WorldWidget->GetInactiveAnimation();

	if (IsActive && IsValid(ActiveAnimation))
	{
		WidgetActiveAnimationFinishBinding.BindDynamic(this, &UWorldWidgetComponent::OnWidgetActiveAnimationFinish);
		WorldWidget->BindToAnimationFinished(ActiveAnimation, WidgetActiveAnimationFinishBinding);
	}
	else if (!IsActive && IsValid(InactiveAnimation))
	{
		WidgetInactiveAnimationFinishBinding.BindDynamic(this, &UWorldWidgetComponent::OnWidgetInactiveAnimationFinish);
		WorldWidget->BindToAnimationFinished(InactiveAnimation, WidgetInactiveAnimationFinishBinding);
	}

	UpdateWorldWidget();
	WorldWidget->SetIsActived(IsActive);
}

void UWorldWidgetComponent::UpdateWorldWidget()
{
	if (IsValid(WorldWidget))
	{
		WorldWidget->TakeWidget()->SlatePrepass();

		if (WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen)
		{
			SetWidgetSpace(EWidgetSpace::Screen);
			SetDrawAtDesiredSize(true);
			SetWidget(WorldWidget);
		}
		else if (WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld)
		{
			SetWidgetSpace(EWidgetSpace::World);
			SetDrawAtDesiredSize(false);
			SetDrawSize(WorldWidget->GetDesiredSize());
			SetPivot(WorldWidget->Anchor);
			SetWidget(WorldWidget);
		}

		UpdateWidget();
	}
}

void UWorldWidgetComponent::UpdateWorldWidgetLookAtRotation()
{
	if (!WorldWidgetLookAtSetting.bEnableLookAtPlayerCamera)
	{
		return;
	}

	const UWorld* World = GetWorld();
	if (!World->IsGameWorld())
	{
#if WITH_EDITOR
		EditorUpdateWorldWidgetLookAtRotation();
#endif
		return;
	}

	APlayerController* PC = UBPFunctions_Gameplay::GetPlayerControllerByIndex(World, APlayerController::StaticClass(), WorldWidgetLookAtSetting.LookAtPlayerIndex);
	if (!IsValid(PC))
	{
		/* Can Not Find PlayerController */
		return;
	}

	const FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	UpdateWorldWidgetLookAtRotation(CameraLocation);
}

void UWorldWidgetComponent::UpdateWorldWidgetLookAtRotation(FVector InLocation)
{
	if (WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen)
	{
	}
	else if (WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld)
	{
		const FRotator FollowRotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), InLocation);
		FRotator WidgetComponentRotation = FRotator::ZeroRotator;

		if (WorldWidgetLookAtSetting.LookAtPitch)
		{
			WidgetComponentRotation.Pitch = FollowRotation.Pitch;
		}
		if (WorldWidgetLookAtSetting.LookAtYaw)
		{
			WidgetComponentRotation.Yaw = FollowRotation.Yaw;
		}
		if (WorldWidgetLookAtSetting.LookAtRoll)
		{
			WidgetComponentRotation.Roll = FollowRotation.Roll;
		}

		SetRelativeRotation(WidgetComponentRotation);
	}
}

void UWorldWidgetComponent::OnWidgetActiveAnimationFinish()
{
	WidgetActiveAnimationFinishBinding.Unbind();
}

void UWorldWidgetComponent::OnWidgetInactiveAnimationFinish()
{
	WidgetInactiveAnimationFinishBinding.Unbind();

	if (!bIsActived)
	{
		SetDrawSize(FIntPoint::ZeroValue);
		Deactivate();
	}
}

#if WITH_EDITOR

void UWorldWidgetComponent::EditorUpdateWorldWidgetLookAtRotation()
{
	if (WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInScreen)
	{
	}
	else if (WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld)
	{
		UpdateWorldWidgetLookAtRotation(GCurrentLevelEditingViewportClient->GetViewLocation());
	}
}

#endif
