// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericMessageDialog.h"

#include "GenericButtonWidget.h"
#include "GenericWindowType.h"
#include "GenericWindowWrapper.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Type/DebugType.h"

FGameplayTag UGenericMessageDialog::GetResultDialogType() const
{
	return ResultDialogType;
}

void UGenericMessageDialog::SubmitMessageDialogResult(FGameplayTag InDialogType)
{
	ResultDialogType = InDialogType;
	if (UGenericWindowWrapper* Wrapper = GetWindowWrapper())
	{
		Wrapper->CloseWindow();
	}
}
