// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericButtonWidget.h"
#include "Generic/GenericObject.h"
#include "GenericButtonBuilder.generated.h"

class UGenericButtonContainer;
class UGenericButtonWidget;
class UGenericButtonGroup;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnButtonGroupBuild, FGameplayTag, UGenericButtonGroup*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnButtonGroupDestroy, FGameplayTag, UGenericButtonGroup*);

UENUM(BlueprintType)
enum class EBuildButtonMethod : uint8
{
	UseButtonClass,
	UseButtonRef
};

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericButtonBuilder : public UGenericObject
{
	GENERATED_BODY()

public:
	UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer);

	void BuildButtonGroup(const TArray<UGenericButtonBuilder*>& Children);
	void DestroyButtonGroup(const TArray<UGenericButtonBuilder*>& Children);

	UGenericButtonContainer* BuildButtonGroupWidget(bool bUpdate = false);
	UGenericButtonWidget* BuildButtonWidget(bool bUpdate = false);

public:
	UFUNCTION(BlueprintPure)
	FGameplayTag GetButtonTag() const;

	UFUNCTION(BlueprintCallable)
	void SetButtonTag(FGameplayTag InButtonTag);

public:
	FOnButtonGroupBuild& GetOnButtonGroupBuilt() { return OnButtonGroupBuiltEvent; }
	FOnButtonGroupDestroy& GetOnButtonGroupDestroy() { return OnButtonGroupDestroyEvent; }

protected:
	UPROPERTY(VisibleAnywhere, meta=(Categories="UI.Button"))
	FGameplayTag ButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	EBuildButtonMethod BuildButtonGroupMethod = EBuildButtonMethod::UseButtonRef;

	UPROPERTY(EditDefaultsOnly, meta=(EditConditionHides, EditCondition="BuildButtonGroupMethod == EBuildButtonMethod::UseButtonClass"))
	TSubclassOf<UGenericButtonContainer> ButtonGroupClass;

	UPROPERTY(EditDefaultsOnly, Instanced, meta=(EditConditionHides, EditCondition="BuildButtonGroupMethod == EBuildButtonMethod::UseButtonRef"))
	TObjectPtr<UGenericButtonContainer> ButtonGroupRef = nullptr;

	UPROPERTY(EditDefaultsOnly)
	EBuildButtonMethod BuildButtonMethod = EBuildButtonMethod::UseButtonRef;

	UPROPERTY(EditDefaultsOnly, meta=(EditConditionHides, EditCondition="BuildButtonMethod == EBuildButtonMethod::UseButtonClass"))
	TSubclassOf<UGenericButtonWidget> ButtonClass;

	UPROPERTY(EditDefaultsOnly, Instanced, meta=(EditConditionHides, EditCondition="BuildButtonMethod == EBuildButtonMethod::UseButtonRef"))
	TObjectPtr<UGenericButtonWidget> ButtonRef = nullptr;

	
protected:
	FOnButtonGroupBuild OnButtonGroupBuiltEvent;
	FOnButtonGroupDestroy OnButtonGroupDestroyEvent;

private:
	UPROPERTY()
	TObjectPtr<UGenericButtonGroup> ButtonGroup = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericButtonContainer> ButtonContainer = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericButtonWidget> Button = nullptr;
};
