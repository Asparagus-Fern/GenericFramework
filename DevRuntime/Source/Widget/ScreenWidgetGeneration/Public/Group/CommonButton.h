// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ScreenWidgetType.h"
#include "UserWidget/Base/UserWidgetInterface.h"
#include "CommonButton.generated.h"

class UCommonButtonEvent;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCommonButton : public UCommonButtonBase, public IUserWidgetInterface
{
	GENERATED_BODY()

	/* UCommonButtonBase */
public:
	UCommonButton(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	virtual void NativeOnClicked() override;
	virtual void NativeOnPressed() override;
	virtual void NativeOnReleased() override;
	virtual void NativeOnSelected(bool bBroadcast) override;
	virtual void NativeOnDeselected(bool bBroadcast) override;

	/* IUserWidgetInterface */
public:
	virtual void NativeOnOpen() override;
	virtual void NativeOnClose() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInteraction;

	UPROPERTY(EditAnywhere, Instanced, Getter, Setter, BlueprintGetter="GetEvents", BlueprintSetter="SetEvents")
	TArray<UCommonButtonEvent*> Events;

public:
	UFUNCTION(BlueprintPure)
	TArray<UCommonButtonEvent*> GetEvents() const;

	UFUNCTION(BlueprintCallable)
	void SetEvents(TArray<UCommonButtonEvent*> InEvents);

protected:
	void ResponseButtonEvent(ECommonButtonResponseEvent InResponseEvent);
};
