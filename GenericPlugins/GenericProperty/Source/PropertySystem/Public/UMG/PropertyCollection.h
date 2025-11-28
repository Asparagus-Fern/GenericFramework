// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyCollection.generated.h"

class UPropertyProxy;
class UPropertyCollectionAsset;
class UScrollBox;
class UPropertyList;
class UPropertyListViewModel;
class UPropertyCollectionViewModel;

/**
 * Property Collection is a Container Has Multi Property List
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyCollection : public UGenericWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyCollectionAsset(UPropertyCollectionAsset* InPropertyCollectionAsset);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyCollectionViewModel(UPropertyCollectionViewModel* InViewModel);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ClearPropertyCollectionViewModel();

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API void GetAllPropertyProxy(TArray<UPropertyProxy*>& Result) const;

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ApplyPropertyChanged();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ResetPropertyChanged();

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyListViewModelsChanged(const TArray<UPropertyListViewModel*>& InViewModels);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Spacing = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsEditable = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyCollectionAsset> PropertyDataCollection = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyCollectionViewModel> PropertyCollectionViewModel = nullptr;

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<TObjectPtr<UPropertyList>> PropertyListArray;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyProxy>> PropertyProxyArray;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScrollBox> ScrollBox_PropertyCollection;
};
