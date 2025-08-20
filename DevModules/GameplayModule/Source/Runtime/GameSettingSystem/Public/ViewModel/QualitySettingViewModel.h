// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "QualitySettingViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UQualitySettingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	FText GetOverallScalabilityLevel() const;

	UFUNCTION(BlueprintCallable)
	void SetOverallScalabilityLevel(int32 InQuality);

	UFUNCTION(FieldNotify, BlueprintPure)
	FText GetViewDistanceQuality() const;

	UFUNCTION(BlueprintCallable)
	void SetViewDistanceQuality(int32 InQuality);

protected:
	FText ConvertToQualityText(int32 InQuality) const;

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText QualitySettingName = FText::FromString("Quality Settings");

	/* Changes all scalability settings at once based on a single overall quality level */
	UPROPERTY(FieldNotify, EditAnywhere, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 OverallScalabilityLevel = 3;

	/* Sets the view distance quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 ViewDistanceQuality = 3;

	/* Sets the shadow quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 ShadowQuality = 3;

	/* Sets the global illumination quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 GlobalIlluminationQuality = 3;

	/* Sets the reflection quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 ReflectionQuality = 3;

	/* Sets the anti-aliasing quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 AntiAliasingQuality = 3;

	/* Sets the texture quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 TextureQuality = 3;

	/* Sets the visual effects quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 VisualEffectQuality = 3;

	/* Sets the post-processing quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 PostProcessingQuality = 3;

	/* Sets the foliage quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 FoliageQuality = 3;

	/* Sets the shading quality (0..4, higher is better) */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 ShadingQuality = 3;
};
