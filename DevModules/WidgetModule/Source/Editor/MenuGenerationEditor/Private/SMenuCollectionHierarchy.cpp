// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuCollectionHierarchy.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMenuCollectionHierarchy::Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor)
{
	ChildSlot
	[
		SNew(STextBlock)
		.Text(FText::FromString("AAA"))
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
