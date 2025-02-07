// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuEntityBase.h"
#include "MenuGroupEntity.generated.h"

class UInteractableWidgetEntityGroup;
class UMenuContainer;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuGroupEntity : public UMenuEntityBase
{
	GENERATED_BODY()

public:
	UMenuGroupEntity(const FObjectInitializer& ObjectInitializer);
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:
	UPROPERTY(EditAnywhere)
	FDisplayWidget ChildWidget;

	/* IStateInterface */
public:
	virtual void OnActived_Implementation() override;
	virtual void OnInactived_Implementation() override;
	
public:
	UFUNCTION(BlueprintPure)
	TArray<UMenuEntityBase*> GetChildrenEntities() const;

protected:
	UPROPERTY(Transient)
	TObjectPtr<UInteractableWidgetEntityGroup> EntityGroup = nullptr;
};
