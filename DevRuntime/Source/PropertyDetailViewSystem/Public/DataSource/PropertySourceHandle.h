// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/CommonObject.h"
#include "PropertySourceHandle.generated.h"

class UPropertyCollection;

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class PROPERTYDETAILVIEWSYSTEM_API UPropertySourceHandle : public UCommonObject
{
	GENERATED_BODY()

public:
	void Initialize();

	UFUNCTION(BlueprintPure)
	UPropertyCollection* GetPropertyCollection() const;

protected:
	virtual void InitializePropertyCollection(UPropertyCollection*& Collection) PURE_VIRTUAL(,);

private:
	UPROPERTY()
	UPropertyCollection* PropertyCollection;
};
