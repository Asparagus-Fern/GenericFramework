// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/PropertyEntity.h"
#include "PropertyValueEntity.generated.h"

/**
 * Property Value Defined:
 * Default Value : The First Value Developer Defined.It Can't Changed,And Only Reset To It.
 * Initial Value : It May Different From Default Value After User Changed The Value And Save It.
 * Current Value : The Value being Modified. If Apply,It Will Store To Initial Value. If Not,It Will Reset To Initial Value.
 */
UCLASS(MinimalAPI)
class UPropertyValueEntity : public UPropertyEntity
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName="ResetToDefault")
	void BP_ResetToDefault();

	UFUNCTION(BlueprintCallable, DisplayName="StoreToInitial")
	void BP_StoreToInitial();

	UFUNCTION(BlueprintCallable, DisplayName="ResetToInitial")
	void BP_ResetToInitial();

public:
	/* Reset The Value To Default */
	PROPERTYENTITYSYSTEM_API virtual void ResetToDefault() PURE_VIRTUAL(,);

	/* Save The Value To Initial */
	PROPERTYENTITYSYSTEM_API virtual void StoreToInitial() PURE_VIRTUAL(,);

	/* Reset The Value To Initial */
	PROPERTYENTITYSYSTEM_API virtual void ResetToInitial() PURE_VIRTUAL(,);
};
