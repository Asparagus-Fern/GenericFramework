// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/ProcedureInterface.h"
#include "UObject/Object.h"
#include "WidgetAnimationEvent.generated.h"

class UWidget;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew)
class SCREENWIDGETGENERATION_API UWidgetAnimationEvent : public UObject, public IProcedureInterface
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(Getter, Setter, BlueprintGetter="GetTargetWidget", BlueprintSetter="SetTargetWidget")
	UWidget* TargetWidget;

public:
	UFUNCTION(BlueprintCallable)
	void RequestAnimationFinish();

	UFUNCTION(BlueprintPure)
	UWidget* GetTargetWidget() const;

	UFUNCTION(BlueprintCallable)
	void SetTargetWidget(UWidget* InWidget);
};
