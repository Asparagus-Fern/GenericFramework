// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyEntity.h"
#include "PropertyValueBase.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyValueBase : public UPropertyEntity
{
	GENERATED_BODY()

public:
	virtual void StoreInitial() PURE_VIRTUAL(,);
	virtual void ResetToDefault() PURE_VIRTUAL(,);
	virtual void RestoreToInitial() PURE_VIRTUAL(,);
};
