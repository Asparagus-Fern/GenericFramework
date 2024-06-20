#pragma once

#include "CoreMinimal.h"
#include "UserWidgetType.generated.h"

class ISlateTextureAtlasInterface;
class USlateBrushAsset;

UENUM(BlueprintType)
enum class EImageBrushResource
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

USTRUCT(BlueprintType)
struct FImageBrush
{
	GENERATED_BODY()

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditConditionHides, EditCondition = "(ImageBrushResource == EImageBrushResource::SlateTextureAtlasInterface || ImageBrushResource == EImageBrushResource::Texture2D || ImageBrushResource == EImageBrushResource::SoftTexture2D|| ImageBrushResource == EImageBrushResource::Texture2DDynamic) && !MatchSize"))
	FVector2D Size = FVector2D(32.f);
};

UENUM(BlueprintType)
enum class EBorderBrushResource
{
	SlateBrush,
	SlateBrushAsset,
	MaterialInterface,
	Texture2D
};

USTRUCT(BlueprintType)
struct FBorderBrush
{
	GENERATED_BODY()

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
