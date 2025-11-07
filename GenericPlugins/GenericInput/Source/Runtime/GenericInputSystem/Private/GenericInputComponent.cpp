// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericInputComponent.h"

#include "GameFramework/InputSettings.h"

UGenericInputComponent::UGenericInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

#if WITH_EDITOR
	UInputSettings::GetInputSettings()->SetDefaultInputComponentClass(UGenericInputComponent::StaticClass());
#endif
}

void UGenericInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGenericInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
