// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyList.generated.h"

class UPropertyProxy;
class UGenericListView;
class UPropertyListItemObject;


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
	void SetPropertyProxyClass(TSubclassOf<UPropertyProxy> InClass);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPropertyProxy> PropertyProxyClass = nullptr;

	UPROPERTY()
	TObjectPtr<UPropertyProxy> PropertyProxy = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericListView> GenericListView_Property;
};
