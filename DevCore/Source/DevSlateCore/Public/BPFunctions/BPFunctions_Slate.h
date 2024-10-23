// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Slate.generated.h"

class UBackgroundBlurSlot;
class UWidget;
class UButtonSlot;
class UStackBoxSlot;
class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UBPFunctions_Slate : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Layout */
public:
	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static UStackBoxSlot* SlotAsStackBoxSlot(const UWidget* Widget);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static UButtonSlot* SlotAsButtonSlot(const UWidget* Widget);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static UBackgroundBlurSlot* SlotAsBackgroundBlurSlot(const UWidget* Widget);

	/* Image */
public:
	UFUNCTION(BlueprintPure, DisplayName="IsValid(ImageBrush)", meta=(CompactNodeTitle = "IsValid"), Category="BPFunctions_Slate|Image")
	static bool IsValid_ImageBrush(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Slate|Image")
	static void SetImageBrush(UImage* InImage, FImageBrush InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Slate Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_SlateBrushToImageBrush(const FSlateBrush& InSlateBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Brush(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FSlateBrush Conv_ImageBrush_ToSlateBrush(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Slate Brush Asset)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_SlateBrushAssetToImageBrush(USlateBrushAsset* InSlateBrushAsset);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Brush Asset(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static USlateBrushAsset* Conv_ImageBrush_ToSlateBrushAsset(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Slate Texture Atlas Interface)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_SlateTextureAtlasInterfaceToImageBrush(TScriptInterface<ISlateTextureAtlasInterface> InSlateTextureAtlasInterface);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Texture Atlas Interface(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static TScriptInterface<ISlateTextureAtlasInterface> Conv_ImageBrush_ToSlateTextureAtlasInterface(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Material Interface)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_MaterialInterfaceToImageBrush(UMaterialInterface* InMaterialInterface);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Material Interface(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static UMaterialInterface* Conv_ImageBrush_ToMaterialInterface(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Soft Material Interface)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_SoftMaterialInterfaceToImageBrush(const TSoftObjectPtr<UMaterialInterface>& InSoftMaterialInterface);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Soft Material Interface(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static TSoftObjectPtr<UMaterialInterface> Conv_ImageBrush_ToSoftMaterialInterface(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Texture2D)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_Texture2DToImageBrush(UTexture2D* InTexture2D);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Texture2D(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static UTexture2D* Conv_ImageBrush_ToTexture2D(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Soft Texture2D)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_SoftTexture2DToImageBrush(const TSoftObjectPtr<UTexture2D>& InSoftTexture2D);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Soft Texture2D(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static TSoftObjectPtr<UTexture2D> Conv_ImageBrush_ToSoftTexture2D(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Texture2D Dynamic)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_Texture2DDynamicToImageBrush(UTexture2DDynamic* InTexture2DDynamic);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Texture2D Dynamic(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static UTexture2DDynamic* Conv_ImageBrush_ToTexture2DDynamic(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush(Resource Object)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush Conv_ImageBrush_ResourceObjectToImageBrush(UObject* InResourceObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Resource Object(Image Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static UObject* Conv_ImageBrush_ToResourceObject(const FImageBrush& InImageBrush);

	/* Border */
public:
	UFUNCTION(BlueprintPure, DisplayName="IsValid(BorderBrush)", meta=(CompactNodeTitle = "IsValid"), Category="BPFunctions_Slate|Border")
	static bool IsValid_BorderBrush(const FBorderBrush& InBorderBrush);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Slate|Border")
	static void SetBorderBrush(UBorder* InBorder, FBorderBrush InBorderBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Border Brush(Slate Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FBorderBrush Conv_BorderBrush_SlateBrushToBorderBrush(const FSlateBrush& InSlateBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Brush(Border Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FSlateBrush Conv_BorderBrush_ToSlateBrush(const FBorderBrush& InBorderBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Border Brush(Slate Brush Asset)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FBorderBrush Conv_BorderBrush_SlateBrushAssetToBorderBrush(USlateBrushAsset* InSlateBrushAsset);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Brush Asset(Border Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static USlateBrushAsset* Conv_BorderBrush_ToSlateBrushAsset(const FBorderBrush& InBorderBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Border Brush(Material Interface)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FBorderBrush Conv_BorderBrush_MaterialInterfaceToBorderBrush(UMaterialInterface* InMaterialInterface);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Material Interface(Border Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static UMaterialInterface* Conv_BorderBrush_ToMaterialInterface(const FBorderBrush& InBorderBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Border Brush(Texture2D)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FBorderBrush Conv_BorderBrush_Texture2DToBorderBrush(UTexture2D* InTexture2D);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Texture2D(Border Brush)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static UTexture2D* Conv_BorderBrush_ToTexture2D(const FBorderBrush& InBorderBrush);
};
