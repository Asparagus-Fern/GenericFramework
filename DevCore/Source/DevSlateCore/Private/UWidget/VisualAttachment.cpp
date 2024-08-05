// Fill out your copyright notice in the Description page of Project Settings.

#include "UWidget/VisualAttachment.h"

#include "SVisualAttachmentBox.h"
#include "Components/SizeBoxSlot.h"

UVisualAttachment::UVisualAttachment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UVisualAttachment::RebuildWidget()
{
	MyAttachmentBox = SNew(SVisualAttachmentBox);
	MySizeBox = MyAttachmentBox;

	if (GetChildrenCount() > 0)
	{
		Cast<USizeBoxSlot>(GetContentSlot())->BuildSlot(MySizeBox.ToSharedRef());
	}

	return MySizeBox.ToSharedRef();
}

void UVisualAttachment::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyAttachmentBox->SetContentAnchor(ContentAnchor);
}

void UVisualAttachment::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyAttachmentBox.Reset();
}

FVector2D UVisualAttachment::GetContentAnchor() const
{
	return ContentAnchor;
}

void UVisualAttachment::SetContentAnchor(FVector2D InContentAnchor)
{
	ContentAnchor = InContentAnchor;

	if (MyAttachmentBox.IsValid())
	{
		MyAttachmentBox->SetContentAnchor(ContentAnchor);
	}
}
