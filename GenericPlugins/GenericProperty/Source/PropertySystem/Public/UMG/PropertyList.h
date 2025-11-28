// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyList.generated.h"

class UPropertyDataSourceCollection;
class UPropertyVisualData;
class UListView;
class UTextBlock;
class UPropertyProxy;
class UPropertyListViewModel;
class UPropertyListItemObject;

/**
 * Property List Contain a Property Category And a List Of Property
 * One Property List Has a Standalone Property Proxy
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyList : public UGenericWidget
{
	GENERATED_UCLASS_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyListViewModel* GetPropertyListViewModel();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyListViewModel(UPropertyListViewModel* InViewModel);

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyProxy* GetPropertyProxy();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void RefreshPropertyList();

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyCategoryChanged(const FText& InCategory);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyDataSourceCollectionClassChanged(TSubclassOf<UPropertyDataSourceCollection> InClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyVisualData> PropertyVisualData = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPropertyListViewModel> PropertyListViewModel = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyProxy> PropertyProxy = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyListItemObject>> PropertyListItemObjects;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_PropertyCategory;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UListView> ListView_Property;
};
