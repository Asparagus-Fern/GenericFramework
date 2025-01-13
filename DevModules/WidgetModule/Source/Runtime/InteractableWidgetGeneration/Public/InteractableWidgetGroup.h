// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "InteractableWidgetGroup.generated.h"

class UCommonButtonGroup;
class UInteractableWidgetBase;

/**
 * 
 */
UCLASS()
class INTERACTABLEWIDGETGENERATION_API UInteractableWidgetGroup : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn))
	int32 Num = 0;

public:
	UFUNCTION(BlueprintCallable)
	void AddWidget(UInteractableWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(UInteractableWidgetBase* InWidget);

	UFUNCTION(BlueprintPure)
	UInteractableWidgetBase* GetWidget(int32 Index);

protected:
	UPROPERTY(BlueprintReadOnly)
	UCommonButtonGroup* CommonButtonGroup;

	UPROPERTY(BlueprintReadOnly)
	TArray<UInteractableWidgetBase*> InteractableUserWidgets;

protected:
	UFUNCTION(BlueprintNativeEvent)
	UInteractableWidgetBase* OnWidgetCreated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetAdded(UInteractableWidgetBase* InWidget, UPanelSlot* InSlot, int32 Index);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetRemoved(UInteractableWidgetBase* InWidget);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_Content;
};
