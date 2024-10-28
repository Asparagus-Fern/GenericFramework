// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreEdManager.h"
#include "BuildingsInteractionEdManager.generated.h"

class UFloorMarkPointComponent;
class UFloorBodyComponent;

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONEDSYSTEM_API UBuildingsInteractionEdManager : public UCoreEdManager
{
	GENERATED_BODY()

public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

protected:
	virtual void OnFloorBodyRefresh(UFloorBodyComponent* InFloorBodyComponent);
};
