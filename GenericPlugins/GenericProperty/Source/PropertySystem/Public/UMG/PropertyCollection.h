// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyCollection.generated.h"

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
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetPropertyCollectionViewModel(UPropertyCollectionViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyListViewModelsChanged(const TArray<UPropertyListViewModel*>& InViewModels);

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ApplyPropertyChanged();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ResetPropertyChanged();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Spacing = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TObjectPtr<UPropertyCollectionViewModel> PropertyCollectionViewModel = nullptr;
 
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<TObjectPtr<UPropertyList>> PropertyLists;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UScrollBox> ScrollBox_PropertyCollection;
};
