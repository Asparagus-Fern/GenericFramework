// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericLoadingViewModel.h"

float UGenericLoadingViewModel::GetLoadingValue()
{
	return (float)CurrentLoadingNum / (float)TotalLoadingNum;
}

float UGenericLoadingViewModel::GetLoadingPercentage()
{
	return (GetLoadingValue() * 100);
}
