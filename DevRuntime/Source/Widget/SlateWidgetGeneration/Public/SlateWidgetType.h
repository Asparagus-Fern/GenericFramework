#pragma once

#include "CoreMinimal.h"
#include "SlateWidgetType.generated.h"

UENUM(BlueprintType)
enum class ELineType
{
	Line,
	Spline,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct SLATEWIDGETGENERATION_API FLinePoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = -180.f, ClampMax = 180.f))
	float Angle = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length = 100.f;
};
