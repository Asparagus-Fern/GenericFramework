// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWidget.h"

UWorldWidget::UWorldWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bEnableInteraction = false;
}

void UWorldWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

FVector2D UWorldWidget::GetAnchorOffset() const
{
	const FVector2D WidgetSize = GetDesiredSize();
	return FVector2D(-(WidgetSize.X * Anchor.X), -(WidgetSize.Y * Anchor.Y));
}
