// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonBuilder.h"

#include "GenericButtonContainer.h"
#include "GenericButtonGroup.h"
#include "GenericWidgetManager.h"
#include "Manager/ManagerStatics.h"

UGenericButtonBuilder::UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ButtonGroupClass = UGenericButtonContainer::StaticClass();
	ButtonClass = UGenericButtonWidget::StaticClass();
}

