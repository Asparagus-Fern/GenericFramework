// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GenericAnimatedSwitcher.h"

void UGenericAnimatedSwitcher::HandleSlateActiveIndexChanged(int32 ActiveIndex)
{
	Super::HandleSlateActiveIndexChanged(ActiveIndex);
	OnActiveIndexChangedFinish.Broadcast(GetWidgetAtIndex(ActiveIndex), ActiveIndex);
}
