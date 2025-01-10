// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "InteractableUserWidgetGroup.generated.h"

class UCommonButtonGroup;
class UInteractableUserWidgetBase;

/**
 * 
 */
UCLASS()
class INTERACTABLEWIDGETGENERATION_API UInteractableUserWidgetGroup : public UUserWidgetBase
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
	void AddWidget(UInteractableUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(UInteractableUserWidgetBase* InWidget);

	UFUNCTION(BlueprintPure)
	UInteractableUserWidgetBase* GetWidget(int32 Index);

protected:
	UPROPERTY(BlueprintReadOnly)
	UCommonButtonGroup* CommonButtonGroup;

	UPROPERTY(BlueprintReadOnly)
	TArray<UInteractableUserWidgetBase*> InteractableUserWidgets;

protected:
	UFUNCTION(BlueprintNativeEvent)
	UInteractableUserWidgetBase* OnWidgetCreated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetAdded(UInteractableUserWidgetBase* InWidget, UPanelSlot* InSlot, int32 Index);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetRemoved(UInteractableUserWidgetBase* InWidget);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPanelWidget> Panel_Content;
};
