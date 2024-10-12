// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataSource/PropertySourceHandle.h"
#include "GameSettingSource.generated.h"

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UGameSettingSource : public UPropertySourceHandle
{
	GENERATED_BODY()

protected:
	virtual void InitializePropertyCollection(UPropertyCollection*& Collection) override;
};
