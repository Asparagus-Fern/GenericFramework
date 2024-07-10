// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidget/SLine.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SLine::Construct(const FArguments& InArgs)
{
	Thickness = InArgs._Thickness;
	Anchor = InArgs._Anchor;
	LinePoints = InArgs._LinePoint;
	Content = InArgs._Content.Widget;

	OnTransitionFinish = InArgs._OnTransitionFinish;
	SetTransition(InArgs._Duration, InArgs._CurveType);

	ChildSlot
	[
		Content.ToSharedRef()
	];
}

void SLine::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

int32 SLine::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (TransitionSequence.IsPlaying())
	{
		const TArray<FVector2D> Points = CalculatePoints(TransitionSequence.GetLerp());
		FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points, ESlateDrawEffect::None, LineColor, true, Thickness);
		// LayerId++;

		// int32 Result = LayerId;
		// if (Content.IsValid() && !Points.IsEmpty())
		// {
		// 	const FVector2D LastPoint = Points.Last();
		// 	const FVector2D ContentSize = Content->GetDesiredSize();
		// 	const FVector2D RenderTransiation = LastPoint - FVector2D(ContentSize.X * Anchor.X, ContentSize.Y * Anchor.Y);
		//
		// 	Content->SetRenderTransform(FSlateRenderTransform(RenderTransiation));
		// 	
		// }

		// return LayerId;
		return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}
	else
	{
		const TArray<FVector2D> Points = CalculatePoints();
		FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points, ESlateDrawEffect::None, LineColor, true, Thickness);
		LayerId++;

		int32 Result = LayerId;;
		if (Content.IsValid() && !Points.IsEmpty())
		{
			const FVector2D LastPoint = Points.Last();
			const FVector2D ContentSize = Content->GetDesiredSize();
			const FVector2D RenderTransiation = LastPoint - FVector2D(ContentSize.X * Anchor.X, ContentSize.Y * Anchor.Y);

			Content->SetRenderTransform(FSlateRenderTransform(RenderTransiation));
			Result = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
		}

		return Result;
	}
}

FVector2D SLine::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	/*TArray<FVector2D> Points = CalculatePoints();
	
	float MaxPositionX = 0.f;
	float MinPositionX = 0.f;
	float MaxPositionY = 0.f;
	float MinPositionY = 0.f;
	
	for (const auto& Point : Points)
	{
		if (Point.X > MaxPositionX)
		{
			MaxPositionX = Point.X;
		}
		else if (Point.X < MinPositionX)
		{
			MinPositionX = Point.X;
		}
		if (Point.Y > MaxPositionY)
		{
			MaxPositionY = Point.Y;
		}
		else if (Point.Y < MinPositionY)
		{
			MinPositionY = Point.Y;
		}
	}
	
	return FVector2D(MaxPositionX - MinPositionX, MaxPositionY - MinPositionY);

	if (Content.IsValid())
	{
		return Content->GetDesiredSize();
	}*/

	return SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);

	// return FVector2D::Zero();
}

TArray<FVector2D> SLine::CalculatePoints() const
{
	TArray<FVector2D> Points;

	FVector2D LastPointPosition = FVector2D::Zero();
	Points.Add(LastPointPosition);

	/* 计算每个点连接上一个点后的位置 */
	for (auto& LinePoint : LinePoints)
	{
		FVector2D PointPositon = CalculatePoint(LinePoint);
		FVector2D ResultPosition = PointPositon + LastPointPosition;
		LastPointPosition = PointPositon;

		Points.Add(ResultPosition);
	}

	return Points;
}

TArray<FVector2D> SLine::CalculatePoints(const float Alpha) const
{
	/* 约束到 0~1 */
	const float ClampAlpha = FMath::Clamp(Alpha, 0.f, 1.f);

	/* 最后计算完返回的点 */
	TArray<FVector2D> TargetPoints;
	TargetPoints.Add(FVector2D::Zero());

	/* 获取所有线段总长度，用Alpha计算出需要的长度 */
	const float Length = GetLength();
	const float TargetLength = FMath::Lerp(0.f, Length, ClampAlpha);

	float CurrentLength = 0.f;
	FVector2D CurrentPointPosition = FVector2D::Zero();

	for (auto& LinePoint : LinePoints)
	{
		/* 所需长度介于当前点和上一个点之间 */
		if (CurrentLength + LinePoint.Length > TargetLength)
		{
			/* 使用当前点的角度和超出上一个点的长度计算最后一个点的位置 */
			CurrentPointPosition += CalculatePoint(FLinePoint(LinePoint.Angle, TargetLength - CurrentLength));
			TargetPoints.Add(CurrentPointPosition);
			break;
		}
		/* 所需长度已经超出这个点的长度 */
		else
		{
			/* 计算这个点的位置 */
			CurrentPointPosition += CalculatePoint(LinePoint);
			CurrentLength += LinePoint.Length;
			TargetPoints.Add(CurrentPointPosition);
		}
	}

	return TargetPoints;
}

FVector2D SLine::CalculatePoint(FLinePoint InLinePoint) const
{
	return FVector2D(InLinePoint.Length * FMath::Cos(UE_DOUBLE_PI / (180.0) * InLinePoint.Angle), InLinePoint.Length * FMath::Sin(UE_DOUBLE_PI / (180.0) * InLinePoint.Angle));
}

float SLine::GetLength() const
{
	float Length = 0.f;

	for (auto& LinePoint : LinePoints)
	{
		Length += LinePoint.Length;
	}

	return Length;
}

void SLine::SetThickness(float InThickness)
{
	Thickness = InThickness;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetAnchor(FVector2D InAnchor)
{
	Anchor = InAnchor;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetLineColor(FLinearColor InLineColor)
{
	LineColor = InLineColor;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetLinePoints(const TArray<FLinePoint>& InLinePoints)
{
	LinePoints = InLinePoints;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetContent(const TSharedRef<SWidget>& InContent)
{
	Content = InContent;
	ChildSlot
	[
		Content.ToSharedRef()
	];

	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetTransition(float Duration, ETransitionCurve Curve)
{
	TransitionSequence = FCurveSequence(0.f, Duration, TransitionCurveToCurveEaseFunction(Curve));
}

void SLine::PlayTransition(bool InForward)
{
	// if (TransitionSequence.IsPlaying())
	// {
	// }
	// else
	// {
	// }

	if (InForward)
	{
		TransitionSequence.Play(AsShared());
	}
	else
	{
		TransitionSequence.PlayReverse(AsShared());
	}

	if (!bIsTransitionTimerRegistered)
	{
		bIsTransitionTimerRegistered = true;
		TimerHandle = RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &SLine::UpdateTransition));
	}
}


EActiveTimerReturnType SLine::UpdateTransition(double InCurrentTime, float InDeltaTime)
{
	if (!TransitionSequence.IsPlaying())
	{
		bIsTransitionTimerRegistered = false;
		UnRegisterActiveTimer(TimerHandle.ToSharedRef());
		OnTransitionFinish.ExecuteIfBound();

		return EActiveTimerReturnType::Stop;
	}

	return EActiveTimerReturnType::Continue;
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
