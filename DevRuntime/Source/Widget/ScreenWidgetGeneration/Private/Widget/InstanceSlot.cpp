// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/InstanceSlot.h"

void UInstanceSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
}

TSharedRef<SWidget> UInstanceSlot::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UInstanceSlot::SetInstanceContent(const FInstanceObject InInstanceObject)
{
	if (IsValid(InInstanceObject.InstanceObject))
	{
		UUserWidget* UserWidget = Cast<UUserWidget>(InInstanceObject.InstanceObject);
		if (IsValid(UserWidget))
		{
			SetContent(UserWidget);
		}
	}
}
