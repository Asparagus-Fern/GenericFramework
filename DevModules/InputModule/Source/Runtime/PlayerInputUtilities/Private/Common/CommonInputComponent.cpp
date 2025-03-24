// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Common/CommonInputComponent.h"

#include "GameFramework/InputSettings.h"

UCommonInputComponent::UCommonInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

#if WITH_EDITOR
	UInputSettings::GetInputSettings()->SetDefaultInputComponentClass(UCommonInputComponent::StaticClass());
#endif
}

void UCommonInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCommonInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
