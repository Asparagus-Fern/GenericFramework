// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Components/RadialBoxSettings.h"
#include "SlateType.generated.h"


class ISlateTextureAtlasInterface;
class USlateBrushAsset;

/**
 * 
 */
UENUM(BlueprintType)
enum class EImageBrushResource :uint8
{
	SlateBrush,
	SlateBrushAsset,
	SlateTextureAtlasInterface,
	MaterialInterface,
	SoftMaterialInterface,
	Texture2D,
	SoftTexture2D,
	Texture2DDynamic,
	ResourceObject
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FImageBrush
{
	GENERATED_BODY()

public:
	FImageBrush();
	FImageBrush(const FSlateBrush& InSlateBrush);
	FImageBrush(USlateBrushAsset* InSlateBrushAsset);
	FImageBrush(TScriptInterface<ISlateTextureAtlasInterface> InSlateTextureAtlasInterface, bool InMatchSize = false, FVector2D InSize = FVector2D(32.f, 32.f));
	FImageBrush(UMaterialInterface* InMaterialInterface, FVector2D InSize = FVector2D(32.f, 32.f));
	FImageBrush(const TSoftObjectPtr<UMaterialInterface>& InSoftMaterialInterface, FVector2D InSize = FVector2D(32.f, 32.f));
	FImageBrush(UTexture2D* InTexture2D, bool InMatchSize = false, FVector2D InSize = FVector2D(32.f, 32.f));
	FImageBrush(const TSoftObjectPtr<UTexture2D>& InSoftTexture2D, bool InMatchSize = false, FVector2D InSize = FVector2D(32.f, 32.f));
	FImageBrush(UTexture2DDynamic* InTexture2DDynamic, bool InMatchSize = false, FVector2D InSize = FVector2D(32.f, 32.f));
	FImageBrush(UObject* InResourceObject);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EImageBrushResource ImageBrushResource = EImageBrushResource::SlateBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::SlateBrush"))
	FSlateBrush SlateBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::SlateBrushAsset"))
	USlateBrushAsset* SlateBrushAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::SlateTextureAtlasInterface"))
	TScriptInterface<ISlateTextureAtlasInterface> SlateTextureAtlasInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::MaterialInterface"))
	UMaterialInterface* MaterialInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::SoftMaterialInterface"))
	TSoftObjectPtr<UMaterialInterface> SoftMaterialInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::Texture2D"))
	UTexture2D* Texture2D = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::SoftTexture2D"))
	TSoftObjectPtr<UTexture2D> SoftTexture2D = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::Texture2DDynamic"))
	UTexture2DDynamic* Texture2DDynamic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::ResourceObject"))
	UObject* ResourceObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "ImageBrushResource == EImageBrushResource::SlateTextureAtlasInterface || ImageBrushResource == EImageBrushResource::Texture2D || ImageBrushResource == EImageBrushResource::SoftTexture2D|| ImageBrushResource == EImageBrushResource::Texture2DDynamic"))
	bool MatchSize = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = FVector2D(32.f);
};

/**
 * 
 */
UENUM(BlueprintType)
enum class EBorderBrushResource
{
	SlateBrush,
	SlateBrushAsset,
	MaterialInterface,
	Texture2D
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FBorderBrush
{
	GENERATED_BODY()

public:
	FBorderBrush();
	FBorderBrush(const FSlateBrush& InSlateBrush);
	FBorderBrush(USlateBrushAsset* InSlateBrushAsset);
	FBorderBrush(UMaterialInterface* InMaterialInterface);
	FBorderBrush(UTexture2D* InTexture2D);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBorderBrushResource BoderBrushResource = EBorderBrushResource::SlateBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "BoderBrushResource == EBorderBrushResource::SlateBrush"))
	FSlateBrush SlateBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "BoderBrushResource == EBorderBrushResource::SlateBrushAsset"))
	USlateBrushAsset* SlateBrushAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "BoderBrushResource == EBorderBrushResource::MaterialInterface"))
	UMaterialInterface* MaterialInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "BoderBrushResource == EBorderBrushResource::Texture2D"))
	UTexture2D* Texture2D = nullptr;
};
