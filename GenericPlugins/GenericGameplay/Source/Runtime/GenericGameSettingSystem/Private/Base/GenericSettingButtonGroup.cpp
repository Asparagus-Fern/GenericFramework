// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Base/GenericSettingButtonGroup.h"

#include "GameSettingType.h"
#include "GenericWidgetSubsystem.h"
#include "PropertyProxy.h"
#include "PropertySubsystem.h"
#include "Application/GameSettingDataSourceCollection.h"
#include "Base/GenericPopupWidget.h"
#include "Type/GenericType.h"

void UGenericSettingButtonGroup::NativeOnCreate()
{
	Super::NativeOnCreate();

	UPropertySubsystem::Delegate_OnPropertyProxyRegister.AddUObject(this, &UGenericSettingButtonGroup::OnPropertyProxyRegister);
	UPropertySubsystem::Delegate_OnPropertyProxyUnRegister.AddUObject(this, &UGenericSettingButtonGroup::OnPropertyProxyUnRegister);
}

void UGenericSettingButtonGroup::NativeOnDestroy()
{
	Super::NativeOnDestroy();

	UPropertySubsystem::Delegate_OnPropertyProxyRegister.RemoveAll(this);
	UPropertySubsystem::Delegate_OnPropertyProxyUnRegister.RemoveAll(this);
}

void UGenericSettingButtonGroup::OnPropertyProxyRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy)
{
	if (IsValid(InProxy->GetPropertyDataSourceCollection<UGameSettingDataSourceCollection>()))
	{
		GameSettingProxies.Add(InProxy);
	}
}

void UGenericSettingButtonGroup::OnPropertyProxyUnRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy)
{
	if (IsValid(InProxy->GetPropertyDataSourceCollection<UGameSettingDataSourceCollection>()))
	{
		GameSettingProxies.Remove(InProxy);
	}
}

bool UGenericSettingButtonGroup::HandleOnButtonSelectionConfirmed(UGenericButtonWidget* InButton, bool InSelection)
{
	bool NeedConfirm = false;

	/* Check Is Any Game Settings Dirty */
	for (auto& GameSettingProxy : GameSettingProxies)
	{
		if (GameSettingProxy->IsAnyPropertyValueDirty())
		{
			NeedConfirm = true;
		}
	}

	/* If Dirty, Try To Make Popup Widget To Remind The Player */
	if (NeedConfirm && PopupWidgetClass)
	{
		if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
		{
			UGenericPopupWidget* PopupWidget = GenericWidgetSubsystem->OpenGenericWidget<UGenericPopupWidget>(GetWorld(), PopupWidgetClass);
			if (IsValid(PopupWidget))
			{
				PopupWidget->Delegate_OnPopupResultSubmitted.AddLambda([this, InButton](FGameplayTag InPopupResult)
					{
						bool bShouldUpdateSelection = false;

						for (auto& GameSettingProxy : GameSettingProxies)
						{
							/* If Result == Yes/No, Save/UnSave Game Settings,And ReSelect The Button Once Against */
							if (InPopupResult == TAG_Result_Yes)
							{
								GameSettingProxy->ApplyProperty();
								bShouldUpdateSelection = true;
							}
							else if (InPopupResult == TAG_Result_No)
							{
								GameSettingProxy->ResetProperty();
								bShouldUpdateSelection = true;
							}
							/* If Result == Cancel/Other */
							else
							{
								/* Just Do Nothing, The Popup Widget Will Close Self, And The Player Input Will Recover */
							}
						}

						if (bShouldUpdateSelection)
						{
							SetSelectedButton(InButton);
						}
					}
				);

				return false;
			}
		}
	}

	return Super::HandleOnButtonSelectionConfirmed(InButton, InSelection);
}
