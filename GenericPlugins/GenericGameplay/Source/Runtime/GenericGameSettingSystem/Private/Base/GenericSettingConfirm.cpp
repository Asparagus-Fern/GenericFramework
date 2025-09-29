// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "Base/GenericSettingConfirm.h"

void UGenericSettingConfirm::ConfirmButtonSelection(bool bInSelected)
{
	GetConfirmSelectionChangedEvent().ExecuteIfBound(bInSelected);
}
