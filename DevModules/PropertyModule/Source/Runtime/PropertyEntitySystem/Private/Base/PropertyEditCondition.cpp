// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Base/PropertyEditCondition.h"

UPropertyEditCondition::UPropertyEditCondition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPropertyEditCondition::Initialize(const UObject* InContext)
{
	OnInitialized(InContext);
}

void UPropertyEditCondition::GatherEditState(const UObject* InContext, UPropertyEditableState*& InOutEditState)
{
	OnGatherEditState(InContext, InOutEditState);
}

void UPropertyEditCondition::Changed(const UObject* InContext, UPropertyEntity* InProperty, EPropertyChangeReason InReason)
{
	OnPropertyChanged(InContext, InProperty, InReason);
}

void UPropertyEditCondition::Applied(const UObject* InContext, UPropertyEntity* InProperty)
{
	OnPropertyApplied(InContext, InProperty);
}
