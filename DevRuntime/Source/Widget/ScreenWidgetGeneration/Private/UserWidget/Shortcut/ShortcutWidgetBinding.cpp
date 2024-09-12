// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Shortcut/ShortcutWidgetBinding.h"

#include "Input/CommonInputComponent.h"
#include "UserWidget/Base/UserWidgetBase.h"

void UShortcutWidgetBinding::SetupBinding(UCommonInputComponent* CommonInputComponent)
{
	Super::SetupBinding(CommonInputComponent);

	for (const auto& ShortcutWidget : ShortcutWidgets)
	{
		CommonInputComponent->RegisterInputHandle(ShortcutWidget.Widget, ShortcutWidget.InputHandle);
	}
}

void UShortcutWidgetBinding::ClearupBinding(UCommonInputComponent* CommonInputComponent)
{
	Super::ClearupBinding(CommonInputComponent);

	for (const auto& ShortcutWidget : ShortcutWidgets)
	{
		CommonInputComponent->UnRegisterInputHandle(ShortcutWidget.InputHandle);
	}
}
