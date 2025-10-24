// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericWindowContent.h"

#include "GenericWindowManager.h"

UGenericWindowWrapper* UGenericWindowContent::GetWindowWrapper() const
{
	return WindowWrapper.IsValid() ? WindowWrapper.Get() : nullptr;
}

void UGenericWindowContent::SetWindowWrapper(UGenericWindowWrapper* InWindowWrapper)
{
	WindowWrapper = InWindowWrapper;
}

void UGenericWindowContent::OnChildAdded_Implementation(UUserWidget* InWidget, int32 InIndex)
{
	Super::OnChildAdded_Implementation(InWidget, InIndex);
}

void UGenericWindowContent::OnChildRemoved_Implementation(UUserWidget* InWidget, int32 InIndex)
{
	Super::OnChildRemoved_Implementation(InWidget, InIndex);
}
