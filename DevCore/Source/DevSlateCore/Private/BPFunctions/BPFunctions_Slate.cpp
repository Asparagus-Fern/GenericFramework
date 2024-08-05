// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Slate.h"

#include "Components/BackgroundBlurSlot.h"
#include "Components/Border.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/StackBoxSlot.h"
#include "Engine/Texture2DDynamic.h"
#include "Slate/SlateBrushAsset.h"

UStackBoxSlot* UBPFunctions_Slate::SlotAsStackBoxSlot(const UWidget* Widget)
{
	if (Widget)
	{
		return Cast<UStackBoxSlot>(Widget->Slot);
	}

	return nullptr;
}

UButtonSlot* UBPFunctions_Slate::SlotAsButtonSlot(const UWidget* Widget)
{
	if (Widget)
	{
		return Cast<UButtonSlot>(Widget->Slot);
	}

	return nullptr;
}

UBackgroundBlurSlot* UBPFunctions_Slate::SlotAsBackgroundBlurSlot(const UWidget* Widget)
{
	if (Widget)
	{
		return Cast<UBackgroundBlurSlot>(Widget->Slot);
	}

	return nullptr;
}

bool UBPFunctions_Slate::IsValid_ImageBrush(const FImageBrush& InImageBrush)
{
	switch (InImageBrush.ImageBrushResource)
	{
	case EImageBrushResource::SlateBrush:
		break;
	case EImageBrushResource::SlateBrushAsset:
		return IsValid(InImageBrush.SlateBrushAsset);
	case EImageBrushResource::SlateTextureAtlasInterface:
		break;
	case EImageBrushResource::MaterialInterface:
		return IsValid(InImageBrush.MaterialInterface);
	case EImageBrushResource::SoftMaterialInterface:
		return !InImageBrush.SoftMaterialInterface.IsNull();
	case EImageBrushResource::Texture2D:
		return IsValid(InImageBrush.Texture2D);
	case EImageBrushResource::SoftTexture2D:
		return !InImageBrush.SoftTexture2D.IsNull();
	case EImageBrushResource::Texture2DDynamic:
		return IsValid(InImageBrush.Texture2DDynamic);
	case EImageBrushResource::ResourceObject:
		return IsValid(InImageBrush.ResourceObject);
	}

	return true;
}

void UBPFunctions_Slate::SetImageBrush(UImage* InImage, const FImageBrush InImageBrush)
{
	if (!IsValid(InImage) || !IsValid_ImageBrush(InImageBrush))
	{
		return;
	}

	auto SetDesiredSizeOverride = [](UImage* Image, const FImageBrush& ImageBrush)
	{
		if (!ImageBrush.MatchSize)
		{
			Image->SetDesiredSizeOverride(ImageBrush.Size);
		}
	};

	switch (InImageBrush.ImageBrushResource)
	{
	case EImageBrushResource::SlateBrush:
		InImage->SetBrush(InImageBrush.SlateBrush);
		break;
	case EImageBrushResource::SlateBrushAsset:
		InImage->SetBrushFromAsset(InImageBrush.SlateBrushAsset);
		break;
	case EImageBrushResource::SlateTextureAtlasInterface:
		InImage->SetBrushFromAtlasInterface(InImageBrush.SlateTextureAtlasInterface, InImageBrush.MatchSize);
		break;
	case EImageBrushResource::MaterialInterface:
		InImage->SetBrushFromMaterial(InImageBrush.MaterialInterface);
		break;
	case EImageBrushResource::SoftMaterialInterface:
		InImage->SetBrushFromSoftMaterial(InImageBrush.SoftMaterialInterface);
		break;
	case EImageBrushResource::Texture2D:
		InImage->SetBrushFromTexture(InImageBrush.Texture2D, InImageBrush.MatchSize);
		break;
	case EImageBrushResource::SoftTexture2D:
		InImage->SetBrushFromSoftTexture(InImageBrush.SoftTexture2D, InImageBrush.MatchSize);
		break;
	case EImageBrushResource::Texture2DDynamic:
		InImage->SetBrushFromTextureDynamic(InImageBrush.Texture2DDynamic, InImageBrush.MatchSize);
		break;
	case EImageBrushResource::ResourceObject:
		InImage->SetBrushResourceObject(InImageBrush.ResourceObject);
		break;
	}

	SetDesiredSizeOverride(InImage, InImageBrush);
}

bool UBPFunctions_Slate::IsValid_BorderBrush(const FBorderBrush& InBorderBrush)
{
	switch (InBorderBrush.BoderBrushResource)
	{
	case EBorderBrushResource::SlateBrush:
		break;
	case EBorderBrushResource::SlateBrushAsset:
		return IsValid(InBorderBrush.SlateBrushAsset);
	case EBorderBrushResource::MaterialInterface:
		return IsValid(InBorderBrush.MaterialInterface);
	case EBorderBrushResource::Texture2D:
		return IsValid(InBorderBrush.Texture2D);
	}

	return true;
}

void UBPFunctions_Slate::SetBorderBrush(UBorder* InBorder, FBorderBrush InBorderBrush)
{
	if (!IsValid(InBorder) || !IsValid_BorderBrush(InBorderBrush))
	{
		return;
	}

	switch (InBorderBrush.BoderBrushResource)
	{
	case EBorderBrushResource::SlateBrush:
		InBorder->SetBrush(InBorderBrush.SlateBrush);
		break;
	case EBorderBrushResource::SlateBrushAsset:
		InBorder->SetBrushFromAsset(InBorderBrush.SlateBrushAsset);
		break;
	case EBorderBrushResource::MaterialInterface:
		InBorder->SetBrushFromMaterial(InBorderBrush.MaterialInterface);
		break;
	case EBorderBrushResource::Texture2D:
		InBorder->SetBrushFromTexture(InBorderBrush.Texture2D);
		break;
	}
}
