// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GameplayTagSlot.h"

#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif

UE_DEFINE_GAMEPLAY_TAG(TAG_HUD, "UI.HUD");

FGameplayTagSlotDelegate UGameplayTagSlot::OnBuildGameplayTagSlot;
FGameplayTagSlotDelegate UGameplayTagSlot::OnRemoveGameplayTagSlot;

#if WITH_EDITOR
void UGameplayTagSlot::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!SlotTag.IsValid())
	{
		CompileLog.Error(FText::FromString(TEXT("Slot Tag Is InValid")));
	}
}
#endif

TSharedRef<SWidget> UGameplayTagSlot::RebuildWidget()
{
	if (IsDesignTime())
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(SlotTag.GetTagName().ToString()))
			];
	}
	else
	{
		if (SlotTag.IsValid() && !bManualRegistration)
		{
			OnBuildGameplayTagSlot.Broadcast(this);
		}

		return Super::RebuildWidget();
	}
}

void UGameplayTagSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	if (!IsDesignTime())
	{
		if (SlotTag.IsValid())
		{
			OnRemoveGameplayTagSlot.Broadcast(this);
		}
	}
}

void UGameplayTagSlot::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);
	OnSlotContentAdded.Broadcast(GetChildAt(0));
}

void UGameplayTagSlot::OnSlotRemoved(UPanelSlot* InSlot)
{
	OnSlotContentRemoved.Broadcast(GetChildAt(0));
	Super::OnSlotRemoved(InSlot);
}
