// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "Application/GenericNavViewModel.h"

void UGenericNavViewModel::SwitchLeft()
{
	SetNavIndex(NavIndex - 1 < 0 ? (bAllowWrap ? NavNum - 1 : NavIndex) : NavIndex - 1);
}

void UGenericNavViewModel::SwitchRight()
{
	SetNavIndex(NavIndex + 1 >= NavNum ? (bAllowWrap ? 0 : NavIndex) : NavIndex + 1);
}

int32 UGenericNavViewModel::GetNavNum() const
{
	return NavNum;
}

void UGenericNavViewModel::SetNavNum(int32 InNum)
{
	if (InNum > 0)
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(NavNum, InNum);
	}
}

int32 UGenericNavViewModel::GetNavIndex() const
{
	return NavIndex;
}

void UGenericNavViewModel::SetNavIndex(int32 InIndex)
{
	if (InIndex > 0 && InIndex < NavNum)
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(NavIndex, InIndex);
	}
}
