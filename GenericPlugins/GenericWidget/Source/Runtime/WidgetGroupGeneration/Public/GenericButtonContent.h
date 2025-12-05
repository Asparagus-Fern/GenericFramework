// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interface/StateInterface.h"
#include "Obect/GenericObject.h"
#include "GenericButtonContent.generated.h"

class UWidget;
class UGenericButtonWidget;

USTRUCT(BlueprintType)
struct FButtonContentTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Button"))
	FName ButtonTag;
};

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericButtonContent : public UGenericObject
{
	GENERATED_BODY()

	friend class UGenericButtonWidget;

public:
	WIDGETGROUPGENERATION_API bool Initialize(UWidget* InWidget, UDataTable* InDataTable);
	WIDGETGROUPGENERATION_API void Deinitialize();

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonWidget* GetButtonWidget() const;

	UFUNCTION(BlueprintPure, meta=(DeterminesOutputType = "InClass"))
	WIDGETGROUPGENERATION_API UGenericButtonWidget* GetButtonWidgetByClass(TSubclassOf<UGenericButtonWidget> InClass) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	WIDGETGROUPGENERATION_API FGameplayTag GetButtonTag() const;

protected:
	WIDGETGROUPGENERATION_API virtual bool OnInitialized();
	WIDGETGROUPGENERATION_API virtual TSubclassOf<UWidget> GetContentSupportClass() const;
	WIDGETGROUPGENERATION_API virtual UStruct* GetContentRowSupportClass() const;
	WIDGETGROUPGENERATION_API virtual void OnDeinitialized();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonHovered(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonUnhovered(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonSelectionChanged(UGenericButtonWidget* InButton, bool InSelection);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWidget> ButtonContent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDataTable> ButtonContentDataTable = nullptr;
};
