// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/PropertyEntity.h"
#include "PropertyCollection.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyCollection : public UPropertyEntity
{
	GENERATED_BODY()

public:
	virtual TArray<UPropertyEntity*> GetChildProperties() override { return ChildProperties; }

	UFUNCTION(BlueprintCallable)
	void AddProperty(UPropertyEntity* InProperty);

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyEntity>> ChildProperties;
};
