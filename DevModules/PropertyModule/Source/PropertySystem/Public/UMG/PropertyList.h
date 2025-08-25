// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyList.generated.h"

class UPropertyListItemObject;
class UPropertyListItemAsset;
class UGenericListView;

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UPropertyList : public UGenericWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetPropertyListItemAsset(UPropertyListItemAsset* InAsset);

	UFUNCTION(BlueprintCallable)
	void UpdatePropertyListView();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyListItemAsset> PropertyListItemAsset = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericListView> GenericListView_Property;

	UPROPERTY()
	TArray<TObjectPtr<UPropertyListItemObject>> PropertyListItemObjects;
};
