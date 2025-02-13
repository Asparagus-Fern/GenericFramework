// Fill out your copyright notice in the Description page of Project Settings.


#include "DWidgetComponent.h"


UDWidgetComponent::UDWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bReceiveHardwareInput = true;
}
