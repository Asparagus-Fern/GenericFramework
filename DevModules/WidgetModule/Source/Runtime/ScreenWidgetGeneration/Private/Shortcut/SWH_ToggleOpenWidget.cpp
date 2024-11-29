// Fill out your copyright notice in the Description page of Project Settings.


#include "Shortcut/SWH_ToggleOpenWidget.h"

#include "UserWidget/Base/UserWidgetBase.h"
#include "ScreenWidgetManager.h"
#include "Manager/ManagerProxy.h"

void USWH_ToggleOpenWidget::OnCompleted(const FInputActionInstance& Instance)
{
	Super::OnCompleted(Instance);

	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		if (IsValid(Widget) && Widget->GetIsActived())
		{
			ScreenWidgetManager->CloseUserWidget(Widget);
		}
		else if (!IsValid(Widget))
		{
			ScreenWidgetManager->OpenUserWidget(ShortcutWidgetTableRow.WidgetClass);
		}
	}
}
