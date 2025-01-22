// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlow/Load/ProcedureFlow_Load.h"

#include "ProcedureFlowManager.h"
#include "Loading/LoadingPanel.h"


AProcedureFlow_Load::AProcedureFlow_Load()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlow_Load::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();
	CreateLoadingPanel();
}

void AProcedureFlow_Load::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();

	// UScreenWidgetManager::PostHUDCreated.RemoveAll(this);

	// if (IsValid(LoadingUI))
	// {
	// 	LoadingUI->NativeOnLoadingEnd();
	// 	GetManager<UScreenWidgetManager>()->CloseUserWidget(LoadingUI);
	// }
}

void AProcedureFlow_Load::SwitchToNextProcedureFlow() const
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		ProcedureFlowManager->EnterProcedureFlow(NextProcedureFlowTag);
	}
}

void AProcedureFlow_Load::CreateLoadingPanel_Implementation()
{
	// UScreenWidgetManager::PostHUDCreated.RemoveAll(this);
	//
	// if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	// {
	// 	if (LoadingClass)
	// 	{
	// 		LoadingUI = ScreenWidgetManager->OpenUserWidget<ULoadingPanel>(LoadingClass);
	// 		if (IsValid(LoadingUI))
	// 		{
	// 			LoadingUI->NativeOnLoadingBegin(GetLoadingNum());
	// 		}
	// 	}
	// }
}

int32 AProcedureFlow_Load::GetLoadingNum_Implementation()
{
	return 0;
}

void AProcedureFlow_Load::OnLoadingOnceFinish_Implementation()
{
	if (IsValid(LoadingUI))
	{
		LoadingUI->NativeOnLoadingOnceFinish();
	}
}
