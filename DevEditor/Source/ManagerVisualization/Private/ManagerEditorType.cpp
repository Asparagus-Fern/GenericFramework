#include "ManagerEditorType.h"

#include "ManagerEditor.h"


FManagerListViewItem::FManagerListViewItem()
{
}

TSharedRef<SWidget> FManagerListViewItem::MakeWidget()
{
	FManagerListViewInfoPtr ManagerListViewInfo = GetManager<UManagerEditor>()->GetManagerListView()->GetInfo(SharedThis(this));
	FString ManagerName = ManagerListViewInfo->CoreManager->GetClass()->GetName();

	return SNew(SBox)
		.HeightOverride(30.f)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(10.f, 0.f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(ManagerName))
			]
		];
}

FManagerListViewInfo::FManagerListViewInfo(UCoreManager* InCoreManager)
	: CoreManager(InCoreManager)
{
}
