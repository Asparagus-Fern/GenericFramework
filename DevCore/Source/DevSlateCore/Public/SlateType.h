// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Components/RadialBoxSettings.h"
#include "SlateType.generated.h"


class ISlateTextureAtlasInterface;
class USlateBrushAsset;

/**
 * Types of easing functions for Slate animation curves.  These are used to smooth out animations.
 */
UENUM(BlueprintType)
enum class ESequenceTransitionCurve : uint8
{
	/** Linear interpolation, with no easing */
	Linear,
	/** Quadratic ease in */
	QuadIn,
	/** Quadratic ease out */
	QuadOut,
	/** Quadratic ease in, quadratic ease out */
	QuadInOut,
	/** Cubic ease in */
	CubicIn,
	/** Cubic ease out */
	CubicOut,
	/** Cubic ease in, cubic ease out */
	CubicInOut,
};

static ECurveEaseFunction ConvertToCurveEaseFunction(ESequenceTransitionCurve CurveType)
{
	switch (CurveType)
	{
	default:
	case ESequenceTransitionCurve::Linear: return ECurveEaseFunction::Linear;
	case ESequenceTransitionCurve::QuadIn: return ECurveEaseFunction::QuadIn;
	case ESequenceTransitionCurve::QuadOut: return ECurveEaseFunction::QuadOut;
	case ESequenceTransitionCurve::QuadInOut: return ECurveEaseFunction::QuadInOut;
	case ESequenceTransitionCurve::CubicIn: return ECurveEaseFunction::CubicIn;
	case ESequenceTransitionCurve::CubicOut: return ECurveEaseFunction::CubicOut;
	case ESequenceTransitionCurve::CubicInOut: return ECurveEaseFunction::CubicInOut;
	}
}

/**
 * 
 */
UENUM(BlueprintType)
enum class ELineType : uint8
{
	Line,
	Spline,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FLineSegmentPoint
{
	GENERATED_BODY()

public:
	FLineSegmentPoint();
	FLineSegmentPoint(float InAngle, float InLength);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = -180.f, ClampMax = 180.f))
	float Angle = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length = 100.f;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCommonRadialBoxSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 360))
	float StartingAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDistributeItemsEvenly;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))
	float AngleBetweenItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bDistributeItemsEvenly", ClampMin = 0, ClampMax = 360))
	float SectorCentralAngle;

	FCommonRadialBoxSettings()
		: StartingAngle(0.f)
		  , bDistributeItemsEvenly(true)
		  , AngleBetweenItems(0.f)
		  , SectorCentralAngle(360.f)
	{
	}

	FCommonRadialBoxSettings(const float InStartingAngle, const bool InDistributeItemsEvenly, const float InAngleBetweenItems, const float InSectorCentralAngle)
		: StartingAngle(InStartingAngle)
		  , bDistributeItemsEvenly(InDistributeItemsEvenly)
		  , AngleBetweenItems(InAngleBetweenItems)
		  , SectorCentralAngle(InSectorCentralAngle)
	{
	}
};

static FRadialBoxSettings ConvertToRadialBoxSettings(FCommonRadialBoxSettings InCommonRadialBoxSettings)
{
	FRadialBoxSettings RadialBoxSettings;
	RadialBoxSettings.StartingAngle = InCommonRadialBoxSettings.StartingAngle;
	RadialBoxSettings.AngleBetweenItems = InCommonRadialBoxSettings.AngleBetweenItems;
	RadialBoxSettings.bDistributeItemsEvenly = InCommonRadialBoxSettings.bDistributeItemsEvenly;
	RadialBoxSettings.SectorCentralAngle = InCommonRadialBoxSettings.SectorCentralAngle;

	return RadialBoxSettings;
}

static FCommonRadialBoxSettings ConvertToCommonRadialBoxSettings(FRadialBoxSettings InRadialBoxSettings)
{
	FCommonRadialBoxSettings CommonRadialBoxSettings;
	CommonRadialBoxSettings.StartingAngle = InRadialBoxSettings.StartingAngle;
	CommonRadialBoxSettings.AngleBetweenItems = InRadialBoxSettings.AngleBetweenItems;
	CommonRadialBoxSettings.bDistributeItemsEvenly = InRadialBoxSettings.bDistributeItemsEvenly;
	CommonRadialBoxSettings.SectorCentralAngle = InRadialBoxSettings.SectorCentralAngle;

	return CommonRadialBoxSettings;
}

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
	FImageBrush(TScriptInterface<ISlateTextureAtlasInterface> InSlateTextureAtlasInterface, bool InMatchSize, FVector2D InSize);
	FImageBrush(UMaterialInterface* InMaterialInterface, FVector2D InSize);
	FImageBrush(const TSoftObjectPtr<UMaterialInterface>& InSoftMaterialInterface, FVector2D InSize);
	FImageBrush(UTexture2D* InTexture2D, bool InMatchSize, FVector2D InSize);
	FImageBrush(const TSoftObjectPtr<UTexture2D>& InSoftTexture2D, bool InMatchSize, FVector2D InSize);
	FImageBrush(UTexture2DDynamic* InTexture2DDynamic, bool InMatchSize, FVector2D InSize);
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

/**
 * 
 */
UENUM(BlueprintType)
enum class ESimpleTextBoxType:uint8
{
	Horizontal,
	Vertical,
	HorizontalReversal,
	VerticalReversal
};

/**
 * 列表样式
 */
class FListViewItem
{
public:
	FListViewItem() { return; }
	virtual ~FListViewItem() { return; }
	virtual TSharedRef<SWidget> MakeWidget() =0;
};


/**
 * 列表信息
 */
class FListViewInfo
{
public:
	FListViewInfo() { return; }
	virtual ~FListViewInfo() { return; }
};


/**
 * 
 * @tparam ListViewInfoType 列表信息
 * @tparam ListViewItemType 列表样式
 */
template <typename ListViewInfoType, typename ListViewItemType>
class FListViewBase
{
public:
	FListViewBase() { return; }
	virtual ~FListViewBase() { return; }

	static FListViewBase<ListViewInfoType, ListViewItemType>* New()
	{
		FListViewBase<ListViewInfoType, ListViewItemType>* NewListView = new FListViewBase<ListViewInfoType, ListViewItemType>;
		return NewListView;
	}

	TSharedPtr<ListViewItemType> GetItem(TSharedRef<ListViewInfoType> InInfo)
	{
		return ListViewMap.FindRef(InInfo);
	}

	TArray<TSharedPtr<ListViewItemType>> GetItems()
	{
		TArray<TSharedPtr<ListViewItemType>> Values;

		for (auto& ListView : ListViewMap)
		{
			Values.Add(ListView.Value);
		}

		return Values;
	}

	TSharedPtr<ListViewInfoType> GetInfo(TSharedRef<ListViewItemType> InItem)
	{
		return *ListViewMap.FindKey(InItem);
	}

	TArray<TSharedPtr<ListViewInfoType>> GetInfos()
	{
		TArray<TSharedPtr<ListViewInfoType>> Keys;
		ListViewMap.GetKeys(Keys);

		return Keys;
	}

public:
	TMap<TSharedPtr<ListViewInfoType>, TSharedPtr<ListViewItemType>> ListViewMap;
};
