// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowPlay.h"

#include "GenericButtonSubsystem.h"
#include "GenericCameraSubsystem.h"
#include "GenericWidgetSubsystem.h"
#include "BPFunctions/BPFunctions_Gameplay.h"

void UProcedureFlowPlay::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();


	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* Player = Cast<APlayerController>(Iterator->Get());

		if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(this))
		{
			GenericCameraSubsystem->SwitchToCamera(Player, DefaultCameraTag, CameraHandle);
		}

		if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
		{
			for (auto& DefaultWidgetClass : DefaultWidgetList)
			{
				UGenericWidget* NewWidget = CreateWidget<UGenericWidget>(Player, DefaultWidgetClass);
				GenericWidgetSubsystem->OpenGenericWidget(NewWidget);
			}
		}

		if (UGenericButtonSubsystem* GenericButtonSubsystem = UGenericButtonSubsystem::Get(this))
		{
			for (auto& DefaultButtonClass : DefaultButtonList)
			{
				GenericButtonSubsystem->RegisterButtonCollection(Player, DefaultButtonClass);
			}
		}
	}
}

void UProcedureFlowPlay::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();
}
