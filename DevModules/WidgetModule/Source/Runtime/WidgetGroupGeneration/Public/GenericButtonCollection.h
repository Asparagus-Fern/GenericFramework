// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Generic/GenericObject.h"
#include "Interface/StateInterface.h"
#include "GenericButtonCollection.generated.h"

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

public:
#if WITH_EDITOR
	WIDGETGROUPGENERATION_API void GenerateButtons();
	WIDGETGROUPGENERATION_API void ClearButtons();
#endif

protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	FGameplayTagContainer GameplayTagContainer;
#endif

public:
	WIDGETGROUPGENERATION_API FGameplayTag GetRootGameplayTag() const;
	WIDGETGROUPGENERATION_API UDataTable* GetDataTable() const;
	WIDGETGROUPGENERATION_API TArray<FGameplayTag> GetAllButtonTags();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Button"))
	FGameplayTag RootButtonTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> ButtonTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta = (TitleProperty = "ButtonTag"))
	TArray<TObjectPtr<UGenericButtonBuilder>> ButtonBuilders;

protected:
	void OnButtonGroupBuild(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup);
	void OnButtonGroupDestroy(FGameplayTag InButtonTag, UGenericButtonGroup* InButtonGroup);

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
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool IsContainButtonTag(FGameplayTag InButtonTag);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonBuilder* GetButtonBuilder(FGameplayTag InButtonTag);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API TArray<UGenericButtonBuilder*> GetChildButtonBuilder(FGameplayTag InButtonTag);

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UGenericButtonGroup>> ButtonGroups;
};
