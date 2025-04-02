// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GeneraicVisualAttachment.h"

#include "SVisualAttachmentBox.h"
#include "Components/SizeBoxSlot.h"

UGeneraicVisualAttachment::UGeneraicVisualAttachment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UGeneraicVisualAttachment::RebuildWidget()
{
	MyAttachmentBox = SNew(SVisualAttachmentBox);
	MySizeBox = MyAttachmentBox;

	if (GetChildrenCount() > 0)
	{
		Cast<USizeBoxSlot>(GetContentSlot())->BuildSlot(MySizeBox.ToSharedRef());
	}

	return MySizeBox.ToSharedRef();
}

void UGeneraicVisualAttachment::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyAttachmentBox->SetContentAnchor(ContentAnchor);
}

void UGeneraicVisualAttachment::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyAttachmentBox.Reset();
}

FVector2D UGeneraicVisualAttachment::GetContentAnchor() const
{
	return ContentAnchor;
}

void UGeneraicVisualAttachment::SetContentAnchor(FVector2D InContentAnchor)
{
	ContentAnchor = InContentAnchor;

	if (MyAttachmentBox.IsValid())
	{
		MyAttachmentBox->SetContentAnchor(ContentAnchor);
	}
}
