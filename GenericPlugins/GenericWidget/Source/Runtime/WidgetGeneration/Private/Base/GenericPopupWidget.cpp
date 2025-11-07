// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Base/GenericPopupWidget.h"

#include "GenericWidgetSubsystem.h"
#include "WidgetType.h"
#include "Type/DebugType.h"
#include "Type/GenericType.h"

FGameplayTag UGenericPopupWidget::GetPopupResult() const
{
	return PopupResult;
}

void UGenericPopupWidget::SubmitPopupResult(FGameplayTag InPopupResult)
{
	if (!InPopupResult.IsValid())
	{
		OnErrorPopupResultSubmitted(InPopupResult);
		GenericLOG(GenericLogUI, Error, TEXT("PopupResult Is Invalid"))
		return;
	}

	if (!InPopupResult.MatchesAny(TAG_Result.GetTag().GetSingleTagContainer()))
	{
		OnErrorPopupResultSubmitted(InPopupResult);
		GenericLOG(GenericLogUI, Error, TEXT("'PopupResult' Is Not Under The 'Result' GameplayTag"))
		return;
	}

	PopupResult = InPopupResult;
	OnPopupResultSubmitted(PopupResult);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnPopupResultSubmitted, BPDelegate_OnPopupResultSubmitted, PopupResult);

	/* On Result Submitted,It Will Auto Close To Enable Input In Game Slot */
	if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
	{
		GenericWidgetSubsystem->CloseGenericWidget(this);
	}
}

void UGenericPopupWidget::OnErrorPopupResultSubmitted_Implementation(FGameplayTag InPopupResult)
{
}

void UGenericPopupWidget::OnPopupResultSubmitted_Implementation(FGameplayTag InPopupResult)
{
}
