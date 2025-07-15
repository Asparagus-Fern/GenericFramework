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

UCLASS(MinimalAPI)
class UGenericButtonCollection : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

	/* IStateInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
	virtual void NativeOnDestroy() override;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API virtual bool GetIsActived() const override;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API virtual void SetIsActived(const bool InActived) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGenericButtonAsset> WidgetAsset = nullptr;

protected:
	void BuildChildButtonGroup(FGameplayTag InButtonTag);
	void DestroyChildButtonGroup(FGameplayTag InButtonTag);

	UGenericButtonContainer* BuildButtonGroupWidget(FGameplayTag InButtonTag) const;
	UGenericButtonWidget* BuildButtonWidget(FGameplayTag InButtonTag,UGenericButtonContainer* GroupWidget) const;

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
	TArray<UGenericButtonBuilder*> GetAllButtonBuilder() const;
	UGenericButtonBuilder* GetButtonBuilder(FGameplayTag InButtonTag) const;
	TArray<UGenericButtonBuilder*> GetChildButtonBuilder(FGameplayTag InButtonTag) const;

public:
	UFUNCTION(BlueprintPure)
	TArray<UGenericButtonGroup*> GetAllButtonGroup() const;

	UFUNCTION(BlueprintPure)
	UGenericButtonGroup* GetButtonGroup(FGameplayTag InButtonTag) const;

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UGenericButtonGroup>> ButtonGroups;
};
