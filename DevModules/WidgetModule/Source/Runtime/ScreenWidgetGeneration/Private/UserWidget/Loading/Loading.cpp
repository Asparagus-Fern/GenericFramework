// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Loading/Loading.h"

void ULoading::NativeOnLoadingBegin(int32 Num)
{
	ILoadingInterface::NativeOnLoadingBegin(Num);
	LoadingNum = Num;
	ILoadingInterface::Execute_OnLoadingBegin(this);
}

void ULoading::NativeOnLoadingOnceFinish()
{
	ILoadingInterface::NativeOnLoadingOnceFinish();
	CurrentLoadingNum++;
	LoadingPercentage = CurrentLoadingNum / LoadingNum;
	ILoadingInterface::Execute_OnLoadingOnceFinish(this);
}

void ULoading::NativeOnLoadingEnd()
{
	ILoadingInterface::NativeOnLoadingEnd();
	ILoadingInterface::Execute_OnLoadingOnceFinish(this);
}
