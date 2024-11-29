// Fill out your copyright notice in the Description page of Project Settings.


#include "Shortcut/ShortcutWidgetHandle.h"

#include "EnhancedInputComponent.h"
#include "ScreenWidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "UserWidget/Base/UserWidgetBase.h"

void UShortcutWidgetHandle::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();

	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(this, ShortcutWidgetTableRow.PlayerIndex))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			const FEnhancedInputActionEventBinding& StartedBinding = EnhancedInputComponent->BindAction(ShortcutWidgetTableRow.InputAction, ETriggerEvent::Started, this, &UShortcutWidgetHandle::OnStarted);
			const FEnhancedInputActionEventBinding& OngoingBinding = EnhancedInputComponent->BindAction(ShortcutWidgetTableRow.InputAction, ETriggerEvent::Ongoing, this, &UShortcutWidgetHandle::OnOngoing);
			const FEnhancedInputActionEventBinding& TriggeredBinding = EnhancedInputComponent->BindAction(ShortcutWidgetTableRow.InputAction, ETriggerEvent::Triggered, this, &UShortcutWidgetHandle::OnTriggered);
			const FEnhancedInputActionEventBinding& CanceledBinding = EnhancedInputComponent->BindAction(ShortcutWidgetTableRow.InputAction, ETriggerEvent::Canceled, this, &UShortcutWidgetHandle::OnCanceled);
			const FEnhancedInputActionEventBinding& CompletedBinding = EnhancedInputComponent->BindAction(ShortcutWidgetTableRow.InputAction, ETriggerEvent::Completed, this, &UShortcutWidgetHandle::OnCompleted);

			BindingIndexArray.Add(StartedBinding.GetHandle());
			BindingIndexArray.Add(OngoingBinding.GetHandle());
			BindingIndexArray.Add(TriggeredBinding.GetHandle());
			BindingIndexArray.Add(CanceledBinding.GetHandle());
			BindingIndexArray.Add(CompletedBinding.GetHandle());
		}
	}
}

void UShortcutWidgetHandle::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();

	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(this, ShortcutWidgetTableRow.PlayerIndex))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			for (const auto& BindingIndex : BindingIndexArray)
			{
				EnhancedInputComponent->RemoveActionEventBinding(BindingIndex);
			}
		}
	}
}

bool UShortcutWidgetHandle::Equal(const TSubclassOf<UUserWidgetBase> InWidgetClass) const
{
	return ShortcutWidgetTableRow.WidgetClass == InWidgetClass;
}

bool UShortcutWidgetHandle::Equal(const UUserWidgetBase* InWidget) const
{
	return ShortcutWidgetTableRow.WidgetClass == InWidget->GetClass();
}

void UShortcutWidgetHandle::Link(UUserWidgetBase* InWidget)
{
	if (IsValid(InWidget) && !IsValid(Widget))
	{
		Widget = InWidget;
	}
}

void UShortcutWidgetHandle::UnLink()
{
	if (IsValid(Widget))
	{
		Widget = nullptr;
	}
}

void UShortcutWidgetHandle::OnStarted(const FInputActionInstance& Instance)
{
}

void UShortcutWidgetHandle::OnOngoing(const FInputActionInstance& Instance)
{
}

void UShortcutWidgetHandle::OnTriggered(const FInputActionInstance& Instance)
{
}

void UShortcutWidgetHandle::OnCanceled(const FInputActionInstance& Instance)
{
}

void UShortcutWidgetHandle::OnCompleted(const FInputActionInstance& Instance)
{
}
