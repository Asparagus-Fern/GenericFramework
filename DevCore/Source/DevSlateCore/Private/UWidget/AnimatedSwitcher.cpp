// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UWidget/AnimatedSwitcher.h"


void UAnimatedSwitcher::HandleSlateActiveIndexChanged(int32 ActiveIndex)
{
	Super::HandleSlateActiveIndexChanged(ActiveIndex);
	OnActiveIndexChangedFinish.Broadcast(GetWidgetAtIndex(ActiveIndex), ActiveIndex);
}
