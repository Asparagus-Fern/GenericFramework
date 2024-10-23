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

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_SlateBrushToImageBrush(const FSlateBrush& InSlateBrush)
{
	return FImageBrush(InSlateBrush);
}

FSlateBrush UBPFunctions_Slate::Conv_ImageBrush_ToSlateBrush(const FImageBrush& InImageBrush)
{
	return InImageBrush.SlateBrush;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_SlateBrushAssetToImageBrush(USlateBrushAsset* InSlateBrushAsset)
{
	return FImageBrush(InSlateBrushAsset);
}

USlateBrushAsset* UBPFunctions_Slate::Conv_ImageBrush_ToSlateBrushAsset(const FImageBrush& InImageBrush)
{
	return InImageBrush.SlateBrushAsset;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_SlateTextureAtlasInterfaceToImageBrush(TScriptInterface<ISlateTextureAtlasInterface> InSlateTextureAtlasInterface)
{
	return FImageBrush(InSlateTextureAtlasInterface);
}

TScriptInterface<ISlateTextureAtlasInterface> UBPFunctions_Slate::Conv_ImageBrush_ToSlateTextureAtlasInterface(const FImageBrush& InImageBrush)
{
	return InImageBrush.SlateTextureAtlasInterface;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_MaterialInterfaceToImageBrush(UMaterialInterface* InMaterialInterface)
{
	return FImageBrush(InMaterialInterface);
}

UMaterialInterface* UBPFunctions_Slate::Conv_ImageBrush_ToMaterialInterface(const FImageBrush& InImageBrush)
{
	return InImageBrush.MaterialInterface;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_SoftMaterialInterfaceToImageBrush(const TSoftObjectPtr<UMaterialInterface>& InSoftMaterialInterface)
{
	return FImageBrush(InSoftMaterialInterface);
}

TSoftObjectPtr<UMaterialInterface> UBPFunctions_Slate::Conv_ImageBrush_ToSoftMaterialInterface(const FImageBrush& InImageBrush)
{
	return InImageBrush.SoftMaterialInterface;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_Texture2DToImageBrush(UTexture2D* InTexture2D)
{
	return FImageBrush(InTexture2D);
}

UTexture2D* UBPFunctions_Slate::Conv_ImageBrush_ToTexture2D(const FImageBrush& InImageBrush)
{
	return InImageBrush.Texture2D;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_SoftTexture2DToImageBrush(const TSoftObjectPtr<UTexture2D>& InSoftTexture2D)
{
	return FImageBrush(InSoftTexture2D);
}

TSoftObjectPtr<UTexture2D> UBPFunctions_Slate::Conv_ImageBrush_ToSoftTexture2D(const FImageBrush& InImageBrush)
{
	return InImageBrush.SoftTexture2D;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_Texture2DDynamicToImageBrush(UTexture2DDynamic* InTexture2DDynamic)
{
	return FImageBrush(InTexture2DDynamic);
}

UTexture2DDynamic* UBPFunctions_Slate::Conv_ImageBrush_ToTexture2DDynamic(const FImageBrush& InImageBrush)
{
	return InImageBrush.Texture2DDynamic;
}

FImageBrush UBPFunctions_Slate::Conv_ImageBrush_ResourceObjectToImageBrush(UObject* InResourceObject)
{
	return FImageBrush(InResourceObject);
}

UObject* UBPFunctions_Slate::Conv_ImageBrush_ToResourceObject(const FImageBrush& InImageBrush)
{
	return InImageBrush.ResourceObject;
}

FBorderBrush UBPFunctions_Slate::Conv_BorderBrush_SlateBrushToBorderBrush(const FSlateBrush& InSlateBrush)
{
	return FBorderBrush(InSlateBrush);
}

FSlateBrush UBPFunctions_Slate::Conv_BorderBrush_ToSlateBrush(const FBorderBrush& InBorderBrush)
{
	return InBorderBrush.SlateBrush;
}

FBorderBrush UBPFunctions_Slate::Conv_BorderBrush_SlateBrushAssetToBorderBrush(USlateBrushAsset* InSlateBrushAsset)
{
	return FBorderBrush(InSlateBrushAsset);
}

USlateBrushAsset* UBPFunctions_Slate::Conv_BorderBrush_ToSlateBrushAsset(const FBorderBrush& InBorderBrush)
{
	return InBorderBrush.SlateBrushAsset;
}

FBorderBrush UBPFunctions_Slate::Conv_BorderBrush_MaterialInterfaceToBorderBrush(UMaterialInterface* InMaterialInterface)
{
	return FBorderBrush(InMaterialInterface);
}

UMaterialInterface* UBPFunctions_Slate::Conv_BorderBrush_ToMaterialInterface(const FBorderBrush& InBorderBrush)
{
	return InBorderBrush.MaterialInterface;
}

FBorderBrush UBPFunctions_Slate::Conv_BorderBrush_Texture2DToBorderBrush(UTexture2D* InTexture2D)
{
	return FBorderBrush(InTexture2D);
}

UTexture2D* UBPFunctions_Slate::Conv_BorderBrush_ToTexture2D(const FBorderBrush& InBorderBrush)
{
	return InBorderBrush.Texture2D;
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
