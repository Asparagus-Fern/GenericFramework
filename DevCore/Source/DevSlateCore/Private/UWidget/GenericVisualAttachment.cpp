// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UWidget/GenericVisualAttachment.h"

#include "SVisualAttachmentBox.h"
#include "Components/SizeBoxSlot.h"

UGenericVisualAttachment::UGenericVisualAttachment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UGenericVisualAttachment::RebuildWidget()
{
	MyAttachmentBox = SNew(SVisualAttachmentBox);
	MySizeBox = MyAttachmentBox;

	if (GetChildrenCount() > 0)
	{
		Cast<USizeBoxSlot>(GetContentSlot())->BuildSlot(MySizeBox.ToSharedRef());
	}

	return MySizeBox.ToSharedRef();
}

void UGenericVisualAttachment::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyAttachmentBox->SetContentAnchor(ContentAnchor);
}

void UGenericVisualAttachment::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyAttachmentBox.Reset();
}

FVector2D UGenericVisualAttachment::GetContentAnchor() const
{
	return ContentAnchor;
}

void UGenericVisualAttachment::SetContentAnchor(FVector2D InContentAnchor)
{
	ContentAnchor = InContentAnchor;

	if (MyAttachmentBox.IsValid())
	{
		MyAttachmentBox->SetContentAnchor(ContentAnchor);
	}
}
