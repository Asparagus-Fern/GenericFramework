// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/AnimatedSwitcher.h"


void UAnimatedSwitcher::HandleSlateActiveIndexChanged(int32 ActiveIndex)
{
	Super::HandleSlateActiveIndexChanged(ActiveIndex);
	OnActiveIndexChangedFinish.Broadcast(GetWidgetAtIndex(ActiveIndex), ActiveIndex);
}
