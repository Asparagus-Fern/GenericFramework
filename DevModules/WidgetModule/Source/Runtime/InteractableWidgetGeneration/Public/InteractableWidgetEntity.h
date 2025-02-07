// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/WidgetEntity.h"
#include "InteractableWidgetEntity.generated.h"

class UInteractableWidgetBase;
class UInteractableWidgetEntity;

DECLARE_MULTICAST_DELEGATE_OneParam(FInteractableWidgetEntityEvent, UInteractableWidgetEntity*)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEntitySelectionChanged, UInteractableWidgetEntity*, bool)

/**
 * 
 */
UCLASS(Abstract)
class INTERACTABLEWIDGETGENERATION_API UInteractableWidgetEntity : public UWidgetEntity
{
	GENERATED_BODY()

	friend class UInteractableWidgetEntityGroup;

	/* IWidgetEntityInterface */
public:
	virtual void OpenEntityWidget_Implementation() override;
	virtual void CloseEntityWidget_Implementation() override;

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
	UFUNCTION(BlueprintCallable)
	void Pressed();

	UFUNCTION(BlueprintCallable)
	void Released();

	UFUNCTION(BlueprintCallable)
	void Hovered();

	UFUNCTION(BlueprintCallable)
	void Unhovered();

	UFUNCTION(BlueprintCallable)
	void Clicked();

	UFUNCTION(BlueprintCallable)
	void DoubleClicked();

	UFUNCTION(BlueprintCallable)
	void ChangeSelection(bool Selection);

protected:
	virtual void InternalPressed();
	virtual void InternalReleased();
	virtual void InternalHovered();
	virtual void InternalUnhovered();
	virtual void InternalClicked();
	virtual void InternalDoubleClicked();
	virtual void InternalChangeSelection(bool Selection);

	/* Binding From Widget (If Exist) */
private:
	UFUNCTION()
	void HandleOnEntityPressed(UInteractableWidgetBase* Button);

	UFUNCTION()
	void HandleOnEntityReleased(UInteractableWidgetBase* Button);

	UFUNCTION()
	void HandleOnEntityHovered(UInteractableWidgetBase* Button);

	UFUNCTION()
	void HandleOnEntityUnhovered(UInteractableWidgetBase* Button);

	UFUNCTION()
	void HandleOnEntityClicked(UInteractableWidgetBase* Button);

	UFUNCTION()
	void HandleOnEntityDoubleClicked(UInteractableWidgetBase* Button);

	UFUNCTION()
	void HandleOnEntitySelectionChanged(UInteractableWidgetBase* Button, bool Selection);

	/* Implementation Event */
protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnEntityPressed();

	UFUNCTION(BlueprintNativeEvent)
	void OnEntityReleased();

	UFUNCTION(BlueprintNativeEvent)
	void OnEntityHovered();

	UFUNCTION(BlueprintNativeEvent)
	void OnEntityUnhovered();

	UFUNCTION(BlueprintNativeEvent)
	void OnEntityClicked();

	UFUNCTION(BlueprintNativeEvent)
	void OnEntityDoubleClicked();

	UFUNCTION(BlueprintNativeEvent)
	void OnEntitySelectionChanged(bool Selection);

public:
	FInteractableWidgetEntityEvent& GetOnEntityPressed() { return OnEntityPressedDelegate; }
	FInteractableWidgetEntityEvent& GetOnEntityReleased() { return OnEntityReleasedDelegate; }
	FInteractableWidgetEntityEvent& GetOnEntityHovered() { return OnEntityHoveredDelegate; }
	FInteractableWidgetEntityEvent& GetOnEntityUnhovered() { return OnEntityUnhoveredDelegate; }
	FInteractableWidgetEntityEvent& GetOnEntityClicked() { return OnEntityClickedDelegate; }
	FInteractableWidgetEntityEvent& GetOnEntityDoubleClicked() { return OnEntityDoubleClickedDelegate; }
	FOnEntitySelectionChanged& GetOnEntitySelectionChanged() { return OnEntitySelectionChangedDelegate; }

protected:
	FInteractableWidgetEntityEvent OnEntityPressedDelegate;
	FInteractableWidgetEntityEvent OnEntityReleasedDelegate;
	FInteractableWidgetEntityEvent OnEntityHoveredDelegate;
	FInteractableWidgetEntityEvent OnEntityUnhoveredDelegate;
	FInteractableWidgetEntityEvent OnEntityClickedDelegate;
	FInteractableWidgetEntityEvent OnEntityDoubleClickedDelegate;
	FOnEntitySelectionChanged OnEntitySelectionChangedDelegate;
};
