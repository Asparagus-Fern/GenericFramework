// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Common/CommonObject.h"
#include "PropertyEditCondition.generated.h"

class UPropertyEntity;
class UPropertyEditableState;

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYENTITYSYSTEM_API UPropertyEditCondition : public UCommonObject
{
	GENERATED_BODY()

public:
	UPropertyEditCondition(const FObjectInitializer& ObjectInitializer);

public:
	/* Call When Property Initialize. */
	virtual void Initialize(const UObject* InContext);

	/* Gather New Property Edit State From Edit Condition. */
	virtual void GatherEditState(const UObject* InContext, UPropertyEditableState*& InOutEditState);

	/* Call When Property Changed. */
	virtual void Changed(const UObject* InContext, UPropertyEntity* InProperty, EPropertyChangeReason InReason);

	/* Call When Property Applied. */
	virtual void Applied(const UObject* InContext, UPropertyEntity* InProperty);

public:
	DECLARE_EVENT(FPropertyEditCondition, FOnEditConditionChanged);

	FOnEditConditionChanged OnEditConditionChanged;

	UFUNCTION(BlueprintCallable)
	void BroadcastEditConditionChanged() const { OnEditConditionChanged.Broadcast(); }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialized(const UObject* InContext);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGatherEditState(const UObject* InContext, UPropertyEditableState*& InOutEditState);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPropertyChanged(const UObject* InContext, UPropertyEntity* InProperty, EPropertyChangeReason InReason);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPropertyApplied(const UObject* InContext, UPropertyEntity* InProperty);
};
