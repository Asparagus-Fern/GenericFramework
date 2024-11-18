// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/GamePanel.h"

#include "Components/CanvasPanel.h"

void UGamePanel::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();

	/* 创建新的Panel存放WorldWidget */
	CanvasPanel = NewObject<UCanvasPanel>(GetOuter());

#if WITH_EDITOR
	ConstraintCanvas = SNew(SConstraintCanvas);
#endif

	HandleAddToViewport();
}

void UGamePanel::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
}

void UGamePanel::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	
	CanvasPanel->ClearChildren();

#if WITH_EDITOR
	ConstraintCanvas->ClearChildren();
#endif

	HandleRemoveFromViewport();
}
