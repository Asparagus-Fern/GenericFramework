// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/WidgetEntity.h"
#include "InteractableWidgetEntity.generated.h"

class UInteractableWidgetEntity;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEntitySelectionChanged, UInteractableWidgetEntity*, bool)

/**
 * 
 */
UCLASS(Abstract)
class INTERACTABLEWIDGETGENERATION_API UInteractableWidgetEntity : public UWidgetEntity
{
	GENERATED_BODY()

public:
	/* 坍塌，不可视，且不占据布局 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCollapsed = false;

	/* 隐藏，不可视，但占据布局 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bCollapsed"))
	bool bHidden = false;

	/* 可视，但是否无效化，当为false时，所有的交互将无效化 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bCollapsed && !bHidden"))
	bool bIsEnable = true;

	/* 可视，是否可被选择，当为false时，OnSelected/OnDeselected不再有效 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSelectable = true;

	/* 是否在选中时再次点击取消选中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bSelectable"))
	bool bToggleable = false;

	/* 是否默认选中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bSelectable"))
	bool bDefaultSelected = false;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnSelected();
	void NativeOnSelected();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeSelected();
	void NativeOnDeSelected();

public:
	FOnEntitySelectionChanged GetOnEntitySelectionChanged() { return OnEntitySelectionChanged; }

protected:
	FOnEntitySelectionChanged OnEntitySelectionChanged;
};
