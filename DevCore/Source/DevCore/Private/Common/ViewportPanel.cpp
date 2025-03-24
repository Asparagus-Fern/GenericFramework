// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Common/ViewportPanel.h"

#include "Components/CanvasPanel.h"

void UViewportPanel::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();

	/* 创建新的Panel存放WorldWidget */
	CanvasPanel = NewObject<UCanvasPanel>(GetOuter());

#if WITH_EDITOR
	ConstraintCanvas = SNew(SConstraintCanvas);
#endif

	HandleAddToViewport();
}

void UViewportPanel::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
}

void UViewportPanel::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	
	CanvasPanel->ClearChildren();

#if WITH_EDITOR
	ConstraintCanvas->ClearChildren();
#endif

	HandleRemoveFromViewport();
}
