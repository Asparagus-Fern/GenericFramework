// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/Override/DVisualAttachment.h"

#include "SVisualAttachmentBox.h"
#include "Components/SizeBoxSlot.h"

UDVisualAttachment::UDVisualAttachment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UDVisualAttachment::RebuildWidget()
{
	MyAttachmentBox = SNew(SVisualAttachmentBox);
	MySizeBox = MyAttachmentBox;

	if (GetChildrenCount() > 0)
	{
		Cast<USizeBoxSlot>(GetContentSlot())->BuildSlot(MySizeBox.ToSharedRef());
	}

	return MySizeBox.ToSharedRef();
}

void UDVisualAttachment::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyAttachmentBox->SetContentAnchor(ContentAnchor);
}

void UDVisualAttachment::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyAttachmentBox.Reset();
}

FVector2D UDVisualAttachment::GetContentAnchor() const
{
	return ContentAnchor;
}

void UDVisualAttachment::SetContentAnchor(FVector2D InContentAnchor)
{
	ContentAnchor = InContentAnchor;

	if (MyAttachmentBox.IsValid())
	{
		MyAttachmentBox->SetContentAnchor(ContentAnchor);
	}
}
