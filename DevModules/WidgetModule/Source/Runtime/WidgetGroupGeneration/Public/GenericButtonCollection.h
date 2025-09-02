// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Generic/GenericObject.h"
#include "Interface/StateInterface.h"
#include "GenericButtonCollection.generated.h"

class UGenericButtonContainer;
class UGenericButtonAsset;
class UGenericWidgetDecorator;
class UGenericButtonWidget;
class UGenericButtonGroup;
class UGenericButtonBuilder;

class WIDGETGROUPGENERATION_API FButtonCollectionEvent
{
public:
	static FName OnPressedEventName;
	static FName OnReleasedEventName;
	static FName OnHoveredEventName;
	static FName OnUnhoveredEventName;
	static FName OnClickedEventName;
	static FName OnDoubleClickedEventName;
	static FName OnSelectionChangedEventName;

	static FName GetEventNodeName(FName EventName, FGameplayTag ButtonTag);
};

UCLASS(Abstract, MinimalAPI, Blueprintable)
class UGenericButtonCollection : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

	/* IStateInterface */
public:
	WIDGETGROUPGENERATION_API virtual void NativeOnCreate() override;
	WIDGETGROUPGENERATION_API virtual void NativeOnActived() override;
	WIDGETGROUPGENERATION_API virtual void NativeOnInactived() override;
	WIDGETGROUPGENERATION_API virtual void NativeOnDestroy() override;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API virtual bool GetIsActived() const override;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API virtual void SetIsActived(const bool InActived) override;
	
	/* UGenericButtonCollection */
protected:
	WIDGETGROUPGENERATION_API void BuildChildButtonGroup(FGameplayTag InButtonTag);
	WIDGETGROUPGENERATION_API void DestroyChildButtonGroup(FGameplayTag InButtonTag);

	WIDGETGROUPGENERATION_API UGenericButtonContainer* BuildButtonGroupWidget(FGameplayTag InButtonTag, UGenericButtonWidget* ButtonWidget) const;
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonGroupBuilt(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup, UGenericButtonBuilder* InBuilder);

	WIDGETGROUPGENERATION_API UGenericButtonWidget* BuildButtonWidget(FGameplayTag InButtonTag, UGenericButtonContainer* GroupWidget) const;
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonBuilt(FGameplayTag InButtonTag, UGenericButtonWidget* InButtonWidget, UGenericButtonBuilder* InBuilder);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonGroupDestroy(FGameplayTag InButtonTag);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void PostButtonGroupDestroy(FGameplayTag InButtonTag);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonDestroy(FGameplayTag InButtonTag);

private:
	bool RegisterButtonGroup(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup);
	bool UnRegisterButtonGroup(FGameplayTag InButtonTag);

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonPressed(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonReleased(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonHovered(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonUnhovered(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonClicked(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonDoubleClicked(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void OnButtonSelectionChanged(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool Selection);

public:
	WIDGETGROUPGENERATION_API TArray<FGameplayTag> GetAllButtonTags() const;
	WIDGETGROUPGENERATION_API FGameplayTag GetRootButtonTag() const;
	WIDGETGROUPGENERATION_API TArray<UGenericButtonBuilder*> GetAllButtonBuilder() const;
	WIDGETGROUPGENERATION_API UGenericButtonBuilder* GetButtonBuilder(FGameplayTag InButtonTag) const;
	WIDGETGROUPGENERATION_API TArray<UGenericButtonBuilder*> GetChildButtonBuilder(FGameplayTag InButtonTag) const;

	UFUNCTION(BlueprintPure)
	APlayerController* GetOwnerPlayer() const;
	
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API TArray<UGenericButtonGroup*> GetAllButtonGroup() const;

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.Button"))
	WIDGETGROUPGENERATION_API UGenericButtonGroup* GetButtonGroup(FGameplayTag InButtonTag) const;

private:
	WIDGETGROUPGENERATION_API FGameplayTagContainer GetChildrenButtonTag(FGameplayTag InButtonTag) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGenericButtonAsset> WidgetAsset = nullptr;
	
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UGenericButtonGroup>> ButtonGroups;
};
