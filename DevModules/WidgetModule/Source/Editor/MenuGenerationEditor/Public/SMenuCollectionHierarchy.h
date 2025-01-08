// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MENUGENERATIONEDITOR_API SMenuCollectionHierarchy : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMenuCollectionHierarchy)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor);
};
