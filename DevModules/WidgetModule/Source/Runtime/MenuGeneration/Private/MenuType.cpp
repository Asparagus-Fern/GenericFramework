// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuType.h"

FMenuTagTableRow::FMenuTagTableRow()
	: MenuTag()
{
}

FMenuTagTableRow::FMenuTagTableRow(FName InTag)
	: MenuTag(InTag)
{
}

FMenuTagTableRow::FMenuTagTableRow(FGameplayTagTableRow const& Other)
	: MenuTag(Other.Tag),
	  MenuMainName(FText::FromString(Other.DevComment))
{
}

FMenuTagTableRow::FMenuTagTableRow(FMenuTagTableRow const& Other)
{
	*this = Other;
}

FMenuTagTableRow& FMenuTagTableRow::operator=(FMenuTagTableRow const& Other)
{
	if (this == &Other)
	{
		return *this;
	}

	MenuTag = Other.MenuTag;
	MenuMainName = Other.MenuMainName;
	MenuSubName = Other.MenuSubName;
	MenuToolTip = Other.MenuToolTip;
	MenuIcon = Other.MenuIcon;

	return *this;
}

bool FMenuTagTableRow::operator==(FMenuTagTableRow const& Other) const
{
	return (MenuTag == Other.MenuTag);
}

bool FMenuTagTableRow::operator!=(FMenuTagTableRow const& Other) const
{
	return (MenuTag != Other.MenuTag);
}

bool FMenuTagTableRow::operator<(FMenuTagTableRow const& Other) const
{
	return UE::ComparisonUtility::CompareWithNumericSuffix(MenuTag, Other.MenuTag) < 0;
}
