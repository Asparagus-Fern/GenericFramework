// Fill out your copyright notice in the Description page of Project Settings.

#include "Loading/LoadingPanel.h"

#include "Loading/LoadingProgressBar.h"


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
