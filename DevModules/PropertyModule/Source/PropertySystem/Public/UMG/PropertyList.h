// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyList.generated.h"

class UPropertyListViewModel;
class UTextBlock;
class UPropertyProxy;
class UGenericListView;
class UPropertyListItemObject;


/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyList : public UGenericWidget
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativePreConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyListViewModel(UPropertyListViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyCategoryChanged(const FText& InCategory);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyProxyClassChanged(TSubclassOf<UPropertyProxy> InClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TObjectPtr<UPropertyListViewModel> PropertyListViewModel = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyProxy> PropertyProxy = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_PropertyCategory;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericListView> GenericListView_Property;
};
