// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/Loading/LoadingPanel.h"

#include "UMG/Loading/LoadingProgressBar.h"

void ULoadingPanel::NativeOnLoadingBegin(int32 Num)
{
	ILoadingInterface::NativeOnLoadingBegin(Num);
	ILoadingInterface::Execute_OnLoadingBegin(this);

	if (LoadingProgressBar)
	{
		LoadingProgressBar->NativeOnLoadingBegin(Num);
	}
}

void ULoadingPanel::NativeOnLoadingOnceFinish()
{
	ILoadingInterface::NativeOnLoadingOnceFinish();
	ILoadingInterface::Execute_OnLoadingOnceFinish(this);

	if (LoadingProgressBar)
	{
		LoadingProgressBar->NativeOnLoadingOnceFinish();
	}
}

void ULoadingPanel::NativeOnLoadingEnd()
{
	ILoadingInterface::NativeOnLoadingEnd();
	ILoadingInterface::Execute_OnLoadingEnd(this);

	if (LoadingProgressBar)
	{
		LoadingProgressBar->NativeOnLoadingEnd();
	}
}
