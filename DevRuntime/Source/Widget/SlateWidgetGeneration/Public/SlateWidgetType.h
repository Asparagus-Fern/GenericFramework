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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELineType LineType = ELineType::Line;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = -180.f, ClampMax = 180.f))
	float Angle = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D StartDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D EndDir;
};
