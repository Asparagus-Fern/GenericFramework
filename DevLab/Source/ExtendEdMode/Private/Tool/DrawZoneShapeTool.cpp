#include "Tool/DrawZoneShapeTool.h"

#include "InteractiveToolManager.h"
#include "ZoneGraphDelegates.h"
#include "ZoneGraphSettings.h"
#include "ZoneShapeActor.h"
#include "ZoneShapeComponent.h"
#include "BaseBehaviors/SingleClickOrDragBehavior.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tool/ZoneShapeContainer.h"

#define LOCTEXT_NAMESPACE "FExtendEdModeModule"

struct FZoneShapePoint;

namespace DrawZoneShapeToolLocals
{
	class FPointInsertionChange : public FToolCommandChange
	{
	public:
		FPointInsertionChange(const FVector& InHitLocation)
			: HitLocation(InHitLocation)
		{
		}

		virtual void Apply(UObject* Object) override
		{
			UDrawZoneShapeTool* Tool = Cast<UDrawZoneShapeTool>(Object);
			if (!ensure(Tool))
			{
				return;
			}

			Tool->AddPoint(HitLocation);
		}

		virtual void Revert(UObject* Object) override
		{
			UDrawZoneShapeTool* Tool = Cast<UDrawZoneShapeTool>(Object);
			if (!ensure(Tool))
			{
				return;
			}

			Tool->RemoveLastPoint();
		}

	protected:
		FVector HitLocation;
	};
}

bool UDrawZoneShapeToolBuilder::CanBuildTool(const FToolBuilderState& SceneState) const
{
	return true;
}

UInteractiveTool* UDrawZoneShapeToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	return NewObject<UDrawZoneShapeTool>(SceneState.ToolManager);
}

void UDrawZoneShapeTool::Setup()
{
	Super::Setup();

	Settings = NewObject<UDrawZoneShapeToolProperties>(this);
	Settings->RestoreProperties(this);
	AddToolPropertySource(Settings);

	SetToolDisplayName(LOCTEXT("DisplayName", "Draw Zone Shape"));

	ClickOrDragBehavior = NewObject<USingleClickOrDragInputBehavior>();
	ClickOrDragBehavior->Initialize(this, this);
	AddInputBehavior(ClickOrDragBehavior);

	/* Spawn Actor And Zone Shape Component */
	{
		ZoneShapeContainer = GetWorld()->SpawnActor<AZoneShapeContainer>(FVector::ZeroVector, FRotator::ZeroRotator);
		ZoneShapeComponent = ZoneShapeContainer->GetZoneShapeComponent();

		// ZoneShapeComponent = NewObject<UZoneShapeComponent>(ZoneShapeContainer.Get());
		// ZoneShapeComponent->RegisterComponent();
		// ZoneShapeContainer->AddOwnedComponent(ZoneShapeComponent.Get());
		// ZoneShapeContainer->SetRootComponent(ZoneShapeComponent.Get());

		/* !!! Crash While Zone Shape Component Without Two Point */
		for (auto& Point : ZoneShapeComponent->GetMutablePoints())
		{
			Point.Position = FVector::ZeroVector;
		}
	}

	auto UpdateZoneShapeComponent = [this]()
	{
		if (ZoneShapeComponent.IsValid())
		{
			ZoneShapeComponent->SetCommonLaneProfile(Settings->LaneProfile);
			ZoneShapeComponent->SetReverseLaneProfile(Settings->bReverseLaneProfile);
			ZoneShapeComponent->SetShapeType(Settings->ShapeType);
			ZoneShapeComponent->SetPolygonRoutingType(Settings->PolygonRoutingType);
			ZoneShapeComponent->SetTags(Settings->Tags);

			ZoneShapeComponent->UpdateShape();
		}
	};

	Settings->GetOnModified().AddLambda([UpdateZoneShapeComponent](UObject*, FProperty*)
		{
			UpdateZoneShapeComponent();
		}
	);

	UpdateZoneShapeComponent();
}

void UDrawZoneShapeTool::Shutdown(EToolShutdownType ShutdownType)
{
	Settings->SaveProperties(this);

	if (ShutdownType == EToolShutdownType::Accept)
	{
		ZoneShapeComponent->UpdateShape();
		UE::ZoneGraphDelegates::OnZoneGraphRequestRebuild.Broadcast();
	}
	else
	{
		if (ZoneShapeContainer.IsValid())
		{
			ZoneShapeContainer->Destroy();
		}
	}

	Super::Shutdown(ShutdownType);
}

bool UDrawZoneShapeTool::CanAccept() const
{
	return Settings->ShapeType == FZoneShapeType::Spline ? CurPointNum > 1 : CurPointNum > 2;
}

void UDrawZoneShapeTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	Super::Render(RenderAPI);
}

FInputRayHit UDrawZoneShapeTool::IsHitByClick(const FInputDeviceRay& ClickPos)
{
	FVector3d HitLocation, HitNormal;
	double Distance;
	if (RayCast(ClickPos.WorldRay, HitLocation, HitNormal, Distance))
	{
		return FInputRayHit(Distance, HitNormal);
	}
	return FInputRayHit();
}

void UDrawZoneShapeTool::OnClicked(const FInputDeviceRay& ClickPos)
{
	using namespace DrawZoneShapeToolLocals;

	FVector3d HitLocation, HitNormal;
	double HitDistance;
	if (RayCast(ClickPos.WorldRay, HitLocation, HitNormal, HitDistance))
	{
		/* User For undo/redo */
		GetToolManager()->EmitObjectChange
		(
			this,
			MakeUnique<FPointInsertionChange>(HitLocation),
			LOCTEXT("AddPointTransactionName", "Add Point")
		);

		AddPoint(HitLocation);
	}
}

FInputRayHit UDrawZoneShapeTool::CanBeginClickDragSequence(const FInputDeviceRay& PressPos)
{
	FVector3d HitLocation, HitNormal;
	double Distance;
	if (RayCast(PressPos.WorldRay, HitLocation, HitNormal, Distance))
	{
		return FInputRayHit(Distance, HitNormal);
	}
	return FInputRayHit();
}

void UDrawZoneShapeTool::OnClickPress(const FInputDeviceRay& PressPos)
{
}

void UDrawZoneShapeTool::OnClickDrag(const FInputDeviceRay& DragPos)
{
}

void UDrawZoneShapeTool::OnClickRelease(const FInputDeviceRay& ReleasePos)
{
}

void UDrawZoneShapeTool::OnTerminateDragSequence()
{
}

bool UDrawZoneShapeTool::RayCast(const FRay& WorldRay, FVector3d& HitLocation, FVector3d& HitNormal, double& HitDistance)
{
	double BestHitT = TNumericLimits<double>::Max();

	const FVector3d LineTraceStart = WorldRay.Origin;
	const FVector3d LineTraceEnd = WorldRay.Origin + WorldRay.Direction * WORLD_MAX;
	FHitResult HitResult;

	if (const bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStart, LineTraceEnd, ECC_Visibility))
	{
		HitLocation = HitResult.ImpactPoint;
		HitNormal = HitResult.ImpactNormal;
		BestHitT = HitDistance = HitResult.Distance;
	}

	return BestHitT < TNumericLimits<double>::Max();
}

void UDrawZoneShapeTool::AddPoint(FVector HitLocation)
{
	CurPointNum++;

	/* Add Point */
	if (CurPointNum > 2)
	{
		ZoneShapeComponent->GetMutablePoints().Add(FZoneShapePoint(HitLocation - ZoneShapeContainer->GetActorLocation()));
	}
	else
	{
		/* First Point Location As Actor Location */
		if (CurPointNum == 1)
		{
			ZoneShapeContainer->SetActorLocation(HitLocation);
		}
		/* Set Point Position */
		else if (CurPointNum == 2)
		{
			ZoneShapeComponent->GetMutablePoints()[CurPointNum - 1].Position = HitLocation - ZoneShapeContainer->GetActorLocation();
		}
	}

	FZoneShapePoint& CurPoint = ZoneShapeComponent->GetMutablePoints()[CurPointNum - 1];
	OriginPoints.Add(CurPoint);

	/* Set Zone Shape Point Type */
	if (Settings->ShapeType == FZoneShapeType::Spline)
	{
		CurPoint.Type = FZoneShapePointType::AutoBezier;
	}
	else if (Settings->ShapeType == FZoneShapeType::Polygon)
	{
		CurPoint.Type = FZoneShapePointType::LaneProfile;
		CurPoint.LaneProfile = ZoneShapeComponent->AddUniquePerPointLaneProfile(Settings->LaneProfile);
	}

	/* Update All Points */
	SortPoints();
	RefreshPoints();
}

void UDrawZoneShapeTool::RemovePoint(FZoneShapePoint& InPoint)
{
	/* Make Sure Zone Shape Component Has At Least Two Zone Shape Point */
	if (CurPointNum == 0)
	{
		return;
	}
	/* Reset Actor Location */
	else if (CurPointNum == 1)
	{
		ZoneShapeContainer->SetActorLocation(FVector::ZeroVector);
	}
	/* Reset The Second Point Location */
	else if (CurPointNum == 2)
	{
		ZoneShapeComponent->GetMutablePoints()[CurPointNum - 1].Position = FVector::ZeroVector;
	}
	else
	{
		/* Remove Point Lane Profile */
		if (Settings->ShapeType == FZoneShapeType::Polygon)
		{
			InPoint.LaneProfile = FZoneShapePoint::InheritLaneProfile;
			ZoneShapeComponent->CompactPerPointLaneProfiles();
		}

		/* Remove Point(FZoneShapePoint Has No Operator==(),So Remove The OriginPoints And ReSort) */
		TArray<FZoneShapePoint>& Points = ZoneShapeComponent->GetMutablePoints();
		Points = OriginPoints;
		Points.RemoveAt(CurPointNum - 1);
	}

	OriginPoints.RemoveAt(CurPointNum - 1);
	CurPointNum--;

	/* Update All Points */
	SortPoints();
	RefreshPoints();
}

void UDrawZoneShapeTool::RemoveLastPoint()
{
	RemovePoint(OriginPoints.Last());
}

void UDrawZoneShapeTool::SortPoints()
{
	if (Settings->ShapeType == FZoneShapeType::Spline)
	{
	}
	else if (Settings->ShapeType == FZoneShapeType::Polygon)
	{
		TArray<FZoneShapePoint> ResultPoints;

		/* Get Degree */
		const FVector CenterLocation = GetPointsCenterLocation();
		auto GetDegree = [CenterLocation](const FZoneShapePoint& Point)
		{
			const FVector Direction = Point.Position - CenterLocation;
			const float Length = Direction.Length();
			const float Radian = FMath::Acos(Direction.Y / Length);
			float Degree = 180.f / PI * Radian;

			if (Direction.X > 0)
			{
				Degree = 360.f - Degree;
			}

			return Degree;
		};

		/* Sort In Clockwise */
		ZoneShapeComponent->GetMutablePoints().Sort([GetDegree](const FZoneShapePoint& A, const FZoneShapePoint& B)
			{
				const float DegreeA = GetDegree(A);
				const float DegreeB = GetDegree(B);

				return DegreeA < DegreeB;
			}
		);

		// 	UE_LOG(LogTemp, Warning, TEXT("Direction : %s"), *Direction.ToString());
		// 	UE_LOG(LogTemp, Warning, TEXT("Length : %f ===== Radian : %f ===== Degree : %f"), Length, Radian, Degree);
	}
}

void UDrawZoneShapeTool::RefreshPoints()
{
	if (Settings->ShapeType == FZoneShapeType::Spline)
	{
	}
	/* Update All Polygon Points In Control Point */
	else if (Settings->ShapeType == FZoneShapeType::Polygon)
	{
		/* Polygon Center Point */
		const FVector CenterLocation = GetPointsCenterLocation();
		// UE_LOG(LogTemp, Warning, TEXT("CenterLocation : %s"), *CenterLocation.ToString())

		const UZoneGraphSettings* ZoneGraphSettings = GetDefault<UZoneGraphSettings>();
		const FZoneLaneProfile* LaneProfile = ZoneGraphSettings->GetLaneProfileByRef(Settings->LaneProfile);

		/* Average Of Lanes Total Width */
		const float Distance = LaneProfile->GetLanesTotalWidth() / LaneProfile->Lanes.Num();

		for (auto& Point : ZoneShapeComponent->GetMutablePoints())
		{
			Point.Type = FZoneShapePointType::LaneProfile;

			/* Get Direction And Normalize */
			FVector Direction = Point.Position - CenterLocation;
			UKismetMathLibrary::Vector_Normalize(Direction, .001f);

			/* InControlPoint Location Z Depend On Point Location Z*/
			const float InControlPointZ = Point.Position.Z;

			/* Direction From Center Point To CurPoint * Average Lanes Width */
			FVector InControlPoint = FVector(Direction.X * Distance + Point.Position.X, Direction.Y * Distance + Point.Position.Y, InControlPointZ);
			Point.SetInControlPoint(InControlPoint);

			// UE_LOG(LogTemp, Warning, TEXT("Direction : %s ===== Position : %s ===== InControlPoint : %s"), *Direction.ToString(), *Point.Position.ToString(), *(Direction * Distance + Point.Position).ToString())
		}
		// UE_LOG(LogTemp, Warning, TEXT("===================="))
	}

	ZoneShapeComponent->UpdateShape();
}

FVector UDrawZoneShapeTool::GetPointsCenterLocation()
{
	FVector CenterLocation;
	for (int32 It = 0; It < CurPointNum; It++)
	{
		CenterLocation += ZoneShapeComponent->GetMutablePoints()[It].Position;
		// UE_LOG(LogTemp, Warning, TEXT("Point Location : %s"), *ZoneShapeComponent->GetMutablePoints()[It].Position.ToString())
	}
	return (CenterLocation /= CurPointNum);
}

UDrawZoneShapeToolProperties::UDrawZoneShapeToolProperties(const FObjectInitializer& ObjectInitializer)
	: ShapeType(FZoneShapeType::Spline)
{
	if (const UZoneGraphSettings* ZoneGraphSettings = GetDefault<UZoneGraphSettings>())
	{
		if (const FZoneLaneProfile* NewLaneProfile = ZoneGraphSettings->GetDefaultLaneProfile())
		{
			LaneProfile = *NewLaneProfile;
		}
	}
}

#undef LOCTEXT_NAMESPACE
