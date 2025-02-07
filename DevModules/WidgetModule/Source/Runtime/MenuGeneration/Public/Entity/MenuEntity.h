// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuEntityBase.h"
#include "MenuType.h"
#include "MenuEntity.generated.h"

class UMenuStyle;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuEntity : public UMenuEntityBase
{
	GENERATED_BODY()

public:
	UMenuEntity(const FObjectInitializer& ObjectInitializer);
	virtual void Initialize() override;
	virtual void DeInitialize() override;

	/* IWidgetEntityInterface */
protected:
	virtual void OnEntityWidgetInitialized() override;
	virtual void OnEntityWidgetDeinitialized() override;
	
	/* IStateInterface */
protected:
	virtual void OnActived_Implementation() override;
	virtual void OnInactived_Implementation() override;
};
