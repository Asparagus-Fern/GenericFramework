// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Components/WidgetComponent.h"
#include "WorldWidgetComponent.generated.h"

class SEditorWorldWidget;
class UWidgetComponent;
class UGenericWidget;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_WorldWidget);

/**
 * 
 */
UENUM(BlueprintType)
enum class EWorldWidgetPaintMethod : uint8
{
	PaintInScreen,
	PaintInWorld
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWorldWidgetLookAtSetting
{
	GENERATED_BODY()

public:
	bool operator==(const FWorldWidgetLookAtSetting Other) const
	{
		return bEnableLookAtPlayerCamera == Other.bEnableLookAtPlayerCamera
			&& LookAtPlayerIndex == Other.LookAtPlayerIndex
			&& LookAtPitch == Other.LookAtPitch
			&& LookAtYaw == Other.LookAtYaw
			&& LookAtRoll == Other.LookAtRoll;
	}

	bool operator!=(const FWorldWidgetLookAtSetting Other) const
	{
		return !(*this == Other);
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableLookAtPlayerCamera = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableLookAtPlayerCamera"))
	int32 LookAtPlayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableLookAtPlayerCamera"))
	bool LookAtPitch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableLookAtPlayerCamera"))
	bool LookAtYaw = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableLookAtPlayerCamera"))
	bool LookAtRoll = false;
};

/**
 * 
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), ShowCategories=(Activation), HideCategories=(UserInterface), MinimalAPI)
class UWorldWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UWorldWidgetComponent(const FObjectInitializer& ObjectInitializer);
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void SetActive(bool bNewActive, bool bReset) override;
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	DECLARE_EVENT_OneParam(UWorldWidgetComponent, FWorldWidgetComponentDelegate, UWorldWidgetComponent*);

	WORLDWIDGETGENERATION_API inline static FWorldWidgetComponentDelegate OnWorldWidgetComponentRegister;
	WORLDWIDGETGENERATION_API inline static FWorldWidgetComponentDelegate OnWorldWidgetComponentUnRegister;

public:
	/* Unique Tag */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.WorldWidget"))
	FGameplayTag WorldWidgetTag = FGameplayTag::EmptyTag;

	/* Group Tag, The Same GroupTag Will Be Register In WorldWidgetGroupManager */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(Categories="UI.WorldWidget"))
	FGameplayTag GroupTag = FGameplayTag::EmptyTag;

	/* Method Decide How The Widget Paint */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWorldWidgetPaintMethod WorldWidgetPaintMethod = EWorldWidgetPaintMethod::PaintInScreen;

	/* If True, The Widget Will Always In The Front Of Other Actor In World */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld"))
	bool bAlwaysInFront = true;

	/* Setting Decide How The Widget Look at Player */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "WorldWidgetPaintMethod == EWorldWidgetPaintMethod::PaintInWorld"))
	FWorldWidgetLookAtSetting WorldWidgetLookAtSetting;

	/* UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UGenericWidget* WorldWidget = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool WidgetVisibility;

public:
	UFUNCTION(BlueprintCallable)
	WORLDWIDGETGENERATION_API void SetWorldWidgetPaintMethod(EWorldWidgetPaintMethod InMethod);

	UFUNCTION(BlueprintCallable)
	WORLDWIDGETGENERATION_API void SetAlwaysInFront(bool AlwaysInFront);

	UFUNCTION(BlueprintCallable)
	WORLDWIDGETGENERATION_API void SetWorldWidgetLookAtSetting(const FWorldWidgetLookAtSetting& InSetting);

	UFUNCTION(BlueprintCallable)
	WORLDWIDGETGENERATION_API void SetWorldWidgetByClass(TSubclassOf<UGenericWidget> InWorldWidgetClass);

	UFUNCTION(BlueprintCallable)
	WORLDWIDGETGENERATION_API void SetWorldWidget(UGenericWidget* InWorldWidget);

	UFUNCTION(BlueprintCallable)
	WORLDWIDGETGENERATION_API void SetWidgetVisibility(bool InWidgetVisibility);

protected:
	virtual void ChangeWidgetActiveState(bool IsActive);
	virtual void UpdateWorldWidget();
	virtual void UpdateWorldWidgetLookAtRotation();
	virtual void UpdateWorldWidgetLookAtRotation(FVector InLocation);

	UFUNCTION()
	virtual void OnWidgetActiveAnimationFinish();

	UFUNCTION()
	virtual void OnWidgetInactiveAnimationFinish();

private:
	bool bIsActived;
	FWidgetAnimationDynamicEvent WidgetActiveAnimationFinishBinding;
	FWidgetAnimationDynamicEvent WidgetInactiveAnimationFinishBinding;

#if WITH_EDITOR

protected:
	virtual void EditorUpdateWorldWidgetLookAtRotation();

#endif
};
