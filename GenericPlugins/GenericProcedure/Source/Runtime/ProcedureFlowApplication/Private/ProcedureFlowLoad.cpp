// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowLoad.h"

#include "GenericWidgetSubsystem.h"
#include "GenericWidgetSubsystem.h"
#include "ProcedureFlowSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "DataAsset/GenericLoadingScreenData.h"
#include "UMG/GenericLoadingScreen.h"

void UProcedureFlowLoad::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	if (bEnableLoadingScreen && LoadingScreenClass)
	{
		LoadingScreen = CreateWidget<UGenericLoadingScreen>(GetWorld(), LoadingScreenClass);
		LoadingScreen->SetLoadCount(GetLoadCount());

		if (LoadingScreenData)
		{
			LoadingScreen->SetLoadingScreenViewModel(LoadingScreenData->LoadingScreenViewModel);
		}

		if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
		{
			GenericWidgetSubsystem->OpenGenericWidget(LoadingScreen);
		}
	}


	StartLoading();
}

void UProcedureFlowLoad::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();
}

int32 UProcedureFlowLoad::GetLoadCount()
{
	return 0;
}

void UProcedureFlowLoad::StartLoading()
{
}

void UProcedureFlowLoad::OnLoadOnceFinish()
{
	if (LoadingScreen)
	{
		LoadingScreen->NotifyLoadOnceFinish();
	}
}

void UProcedureFlowLoad::OnLoadFinish()
{
	if (LoadingScreen)
	{
		if (LoadingScreen->GetIsFinished())
		{
			if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
			{
				GenericWidgetSubsystem->CloseGenericWidget(LoadingScreen);
			}

			SwitchToNextProcedureFlow();
		}
		else
		{
			LoadingScreen->OnLoadFinishedEvent.AddUObject(this, &UProcedureFlowLoad::OnPerformanceLoadFinish);
		}
	}
	else
	{
		SwitchToNextProcedureFlow();
	}
}

void UProcedureFlowLoad::OnPerformanceLoadFinish()
{
	if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
	{
		GenericWidgetSubsystem->CloseGenericWidget(LoadingScreen);
	}

	SwitchToNextProcedureFlow();
}
