// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factory/AssetFactory.h"
#include "GameplayProcedureFactory.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UGameplayProcedureFactory : public UAssetFactory
{
	GENERATED_BODY()

public:
	UGameplayProcedureFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

protected:
	virtual void ConfigureFilter(TSharedRef<FAssetFilter>& Filter) override;
};
