#pragma once
#include "SlateType.h"


class UCoreManager;


/**
 * 
 */
class FManagerListViewItem : public FListViewItem, public TSharedFromThis<FManagerListViewItem>
{
public:
	FManagerListViewItem();
	virtual TSharedRef<SWidget> MakeWidget() override;
};


/**
 * 
 */
class FManagerListViewInfo : public FListViewInfo, public TSharedFromThis<FManagerListViewInfo>
{
public:
	FManagerListViewInfo(UCoreManager* InCoreManager);

public:
	UCoreManager* CoreManager;
};


typedef TSharedPtr<FManagerListViewItem> FManagerListViewItemPtr;
typedef TSharedPtr<FManagerListViewInfo> FManagerListViewInfoPtr;
