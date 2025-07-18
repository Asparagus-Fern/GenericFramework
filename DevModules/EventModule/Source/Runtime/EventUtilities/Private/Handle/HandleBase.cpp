// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Handle/HandleBase.h"

#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

void UHandleBase::UnRegister()
{
	if (UHandleManager* HandleManager = GetManagerOwner<UHandleManager>())
	{
		HandleManager->UnRegisterHandle(this);
	}
}

FName UHandleBase::GetHandleName()
{
	return HandleName;
}

void UHandleBase::SetHandleName(FName InHandleName)
{
	HandleName = InHandleName;
}

FText UHandleBase::GetHandleDisplayName()
{
	return HandleDisplayName;
}

void UHandleBase::SetHandleDisplayName(FText InHandleDisplayName)
{
	HandleDisplayName = InHandleDisplayName;
}

bool UHandleBase::EqualID_Implementation(const UHandleBase* Other)
{
	return GetHandleID() == Other->GetHandleID();
}

bool UHandleBase::EqualName_Implementation(FName Other)
{
	return GetHandleName() == Other;
}

bool UHandleBase::NotEqualID_Implementation(const UHandleBase* Other)
{
	return !EqualID(Other);
}

bool UHandleBase::NotEqualName_Implementation(FName Other)
{
	return !EqualName(Other);
}

bool UHandleBase::IsHandleValid_Implementation()
{
	return HandleID.IsValid();
}

bool UHandleBase::IsHandleInValid_Implementation()
{
	return !IsHandleValid();
}
