// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Backpack/BackpackItemData.h"

int32 UBackpackItemData::GetItemID() const
{
	return ItemID;
}

void UBackpackItemData::SetItemID(const int32 InItemID)
{
	UE_MVVM_SET_PROPERTY_VALUE(ItemID, InItemID);
}

FName UBackpackItemData::GetDisplayName() const
{
	return DisplayName;
}

void UBackpackItemData::SetDisplayName(const FName InDisplayName)
{
	UE_MVVM_SET_PROPERTY_VALUE(DisplayName, InDisplayName);
}

FText UBackpackItemData::GetTooltipText() const
{
	return TooltipText;
}

void UBackpackItemData::SetTooltipText(const FText InTooltipText)
{
	UE_MVVM_SET_PROPERTY_VALUE(TooltipText, InTooltipText);
}

UTexture2D* UBackpackItemData::GetIcon() const
{
	return Icon;
}

void UBackpackItemData::SetIcon(UTexture2D* InIcon)
{
	UE_MVVM_SET_PROPERTY_VALUE(Icon, InIcon);
}

int32 UBackpackItemData::GetCount() const
{
	return Count;
}

void UBackpackItemData::SetCount(int32 InCount)
{
	UE_MVVM_SET_PROPERTY_VALUE(Count, InCount);
}

TArray<FName> UBackpackItemData::GetTags() const
{
	return Tags;
}

void UBackpackItemData::SetTags(TArray<FName> InTags)
{
	UE_MVVM_SET_PROPERTY_VALUE(Tags, InTags);
}
