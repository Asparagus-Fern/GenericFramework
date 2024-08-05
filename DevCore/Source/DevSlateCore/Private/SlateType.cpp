// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateType.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_HUD, "HUD");

FLineSegmentPoint::FLineSegmentPoint()
{
}

FLineSegmentPoint::FLineSegmentPoint(const float InAngle, const float InLength)
	: Angle(InAngle),
	  Length(InLength)
{
}

FImageBrush::FImageBrush()
{
}

FImageBrush::FImageBrush(const FSlateBrush& InSlateBrush)
	: ImageBrushResource(EImageBrushResource::SlateBrush),
	  SlateBrush(InSlateBrush)
{
}

FImageBrush::FImageBrush(USlateBrushAsset* InSlateBrushAsset)
	: ImageBrushResource(EImageBrushResource::SlateBrushAsset),
	  SlateBrushAsset(InSlateBrushAsset)
{
}

FImageBrush::FImageBrush(const TScriptInterface<ISlateTextureAtlasInterface> InSlateTextureAtlasInterface, const bool InMatchSize, const FVector2D InSize)
	: ImageBrushResource(EImageBrushResource::SlateTextureAtlasInterface),
	  SlateTextureAtlasInterface(InSlateTextureAtlasInterface),
	  MatchSize(InMatchSize),
	  Size(InSize)
{
}

FImageBrush::FImageBrush(UMaterialInterface* InMaterialInterface, const FVector2D InSize)
	: ImageBrushResource(EImageBrushResource::MaterialInterface),
	  MaterialInterface(InMaterialInterface),
	  Size(InSize)
{
}

FImageBrush::FImageBrush(const TSoftObjectPtr<UMaterialInterface>& InSoftMaterialInterface, const FVector2D InSize)
	: ImageBrushResource(EImageBrushResource::SoftMaterialInterface),
	  SoftMaterialInterface(InSoftMaterialInterface),
	  Size(InSize)
{
}

FImageBrush::FImageBrush(UTexture2D* InTexture2D, const bool InMatchSize, const FVector2D InSize)
	: ImageBrushResource(EImageBrushResource::Texture2D),
	  Texture2D(InTexture2D),
	  MatchSize(InMatchSize),
	  Size(InSize)
{
}

FImageBrush::FImageBrush(const TSoftObjectPtr<UTexture2D>& InSoftTexture2D, const bool InMatchSize, const FVector2D InSize)
	: ImageBrushResource(EImageBrushResource::SoftTexture2D),
	  SoftTexture2D(InSoftTexture2D),
	  MatchSize(InMatchSize),
	  Size(InSize)
{
}

FImageBrush::FImageBrush(UTexture2DDynamic* InTexture2DDynamic, const bool InMatchSize, const FVector2D InSize)
	: ImageBrushResource(EImageBrushResource::Texture2DDynamic),
	  Texture2DDynamic(InTexture2DDynamic),
	  MatchSize(InMatchSize),
	  Size(InSize)
{
}

FImageBrush::FImageBrush(UObject* InResourceObject)
	: ImageBrushResource(EImageBrushResource::ResourceObject),
	  ResourceObject(InResourceObject)
{
}

FBorderBrush::FBorderBrush()
{
}

FBorderBrush::FBorderBrush(const FSlateBrush& InSlateBrush)
	: BoderBrushResource(EBorderBrushResource::SlateBrush),
	  SlateBrush(InSlateBrush)
{
}

FBorderBrush::FBorderBrush(USlateBrushAsset* InSlateBrushAsset)
	: BoderBrushResource(EBorderBrushResource::SlateBrushAsset),
	  SlateBrushAsset(InSlateBrushAsset)
{
}

FBorderBrush::FBorderBrush(UMaterialInterface* InMaterialInterface)
	: BoderBrushResource(EBorderBrushResource::MaterialInterface),
	  MaterialInterface(InMaterialInterface)
{
}

FBorderBrush::FBorderBrush(UTexture2D* InTexture2D)
	: BoderBrushResource(EBorderBrushResource::Texture2D),
	  Texture2D(InTexture2D)
{
}
