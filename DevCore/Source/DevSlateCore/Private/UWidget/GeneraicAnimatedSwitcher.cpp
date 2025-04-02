// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UWidget/GeneraicAnimatedSwitcher.h"


void UGeneraicAnimatedSwitcher::HandleSlateActiveIndexChanged(int32 ActiveIndex)
{
	Super::HandleSlateActiveIndexChanged(ActiveIndex);
	OnActiveIndexChangedFinish.Broadcast(GetWidgetAtIndex(ActiveIndex), ActiveIndex);
}
