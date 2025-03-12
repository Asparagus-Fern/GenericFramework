// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Widgets/SWidget.h"

/**
 * 列表样式
 */
class FListViewItem
{
public:
	FListViewItem() { return; }
	virtual ~FListViewItem() { return; }
	virtual TSharedRef<SWidget> MakeWidget() =0;
};


/**
 * 列表信息
 */
class FListViewInfo
{
public:
	FListViewInfo() { return; }
	virtual ~FListViewInfo() { return; }
};


/**
 * 
 * @tparam ListViewInfoType 列表信息
 * @tparam ListViewItemType 列表样式
 */
template <typename ListViewInfoType, typename ListViewItemType>
class FListViewBase
{
public:
	FListViewBase() { return; }
	virtual ~FListViewBase() { return; }

	static FListViewBase<ListViewInfoType, ListViewItemType>* New()
	{
		FListViewBase<ListViewInfoType, ListViewItemType>* NewListView = new FListViewBase<ListViewInfoType, ListViewItemType>;
		return NewListView;
	}

	TSharedPtr<ListViewItemType> GetItem(TSharedRef<ListViewInfoType> InInfo)
	{
		return ListViewMap.FindRef(InInfo);
	}

	TArray<TSharedPtr<ListViewItemType>> GetItems()
	{
		TArray<TSharedPtr<ListViewItemType>> Values;

		for (auto& ListView : ListViewMap)
		{
			Values.Add(ListView.Value);
		}

		return Values;
	}

	TSharedPtr<ListViewInfoType> GetInfo(TSharedRef<ListViewItemType> InItem)
	{
		return *ListViewMap.FindKey(InItem);
	}

	TArray<TSharedPtr<ListViewInfoType>> GetInfos()
	{
		TArray<TSharedPtr<ListViewInfoType>> Keys;
		ListViewMap.GetKeys(Keys);

		return Keys;
	}

public:
	TMap<TSharedPtr<ListViewInfoType>, TSharedPtr<ListViewItemType>> ListViewMap;
};
