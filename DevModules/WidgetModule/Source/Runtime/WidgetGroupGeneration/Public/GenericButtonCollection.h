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

UCLASS(MinimalAPI, Blueprintable)
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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGenericButtonAsset> WidgetAsset = nullptr;

protected:
	WIDGETGROUPGENERATION_API void BuildChildButtonGroup(FGameplayTag InButtonTag);
	WIDGETGROUPGENERATION_API void DestroyChildButtonGroup(FGameplayTag InButtonTag);

	WIDGETGROUPGENERATION_API UGenericButtonContainer* BuildButtonGroupWidget(FGameplayTag InButtonTag, UGenericButtonWidget* ButtonWidget) const;
	WIDGETGROUPGENERATION_API UGenericButtonWidget* BuildButtonWidget(FGameplayTag InButtonTag, UGenericButtonContainer* GroupWidget) const;

private:
	void RegisterButtonGroup(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup);
	void UnRegisterButtonGroup(FGameplayTag InButtonTag);

	UFUNCTION()
	void OnButtonPressed(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION()
	void OnButtonReleased(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION()
	void OnButtonHovered(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION()
	void OnButtonUnhovered(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION()
	void OnButtonClicked(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION()
	void OnButtonDoubleClicked(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton);

	UFUNCTION()
	void OnButtonSelectionChanged(UGenericButtonGroup* InButtonGroup, UGenericButtonWidget* InButton, bool Selection);

public:
	WIDGETGROUPGENERATION_API TArray<FGameplayTag> GetAllButtonTags() const;
	WIDGETGROUPGENERATION_API FGameplayTag GetRootButtonTag() const;
	WIDGETGROUPGENERATION_API TArray<UGenericButtonBuilder*> GetAllButtonBuilder() const;
	WIDGETGROUPGENERATION_API UGenericButtonBuilder* GetButtonBuilder(FGameplayTag InButtonTag) const;
	WIDGETGROUPGENERATION_API TArray<UGenericButtonBuilder*> GetChildButtonBuilder(FGameplayTag InButtonTag) const;

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API TArray<UGenericButtonGroup*> GetAllButtonGroup() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonGroup* GetButtonGroup(FGameplayTag InButtonTag) const;

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UGenericButtonGroup>> ButtonGroups;
};
