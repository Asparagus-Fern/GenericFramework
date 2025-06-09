#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "ZoneGraphTypes.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"
#include "UObject/Object.h"
#include "DrawZoneShapeTool.generated.h"


/**
 * 
 */
UCLASS(Transient)
class EXTENDEDMODE_API UDrawZoneShapeToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

	/* UInteractiveToolBuilder */
public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};


/**
 * 
 */
UCLASS()
class EXTENDEDMODE_API UDrawZoneShapeTool : public UInteractiveTool, public IClickBehaviorTarget, public IClickDragBehaviorTarget
{
	GENERATED_BODY()

	/* UInteractiveTool */
public:
	virtual void Setup() override;
	virtual void Shutdown(EToolShutdownType ShutdownType) override;
	virtual bool HasAccept() const override { return true; }
	virtual bool CanAccept() const override;
	virtual bool HasCancel() const override { return true; }
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;

	/* IClickBehaviorTarget */
public:
	virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;
	virtual void OnClicked(const FInputDeviceRay& ClickPos) override;

	/* IClickDragBehaviorTarget */
public:
	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& PressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;
	virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;
	virtual void OnTerminateDragSequence() override;

private:
	bool RayCast(const FRay& WorldRay, FVector3d& HitLocation, FVector3d& HitNormal, double& HitDistance);

protected:
	UPROPERTY()
	TObjectPtr<class UDrawZoneShapeToolProperties> Settings = nullptr;

	UPROPERTY()
	TObjectPtr<class USingleClickOrDragInputBehavior> ClickOrDragBehavior = nullptr;

	TWeakObjectPtr<class AZoneShapeContainer> ZoneShapeContainer = nullptr;

	TWeakObjectPtr<class UZoneShapeComponent> ZoneShapeComponent = nullptr;

	int32 CurPointNum = 0;

	TArray<FZoneShapePoint> OriginPoints;

public:
	void AddPoint(FVector HitLocation);
	void RemovePoint(FZoneShapePoint& InPoint);
	void RemoveLastPoint();

protected:
	void SortPoints();
	void RefreshPoints();
	FVector GetPointsCenterLocation();
};


/**
 * 
 */
UCLASS()
class EXTENDEDMODE_API UDrawZoneShapeToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_UCLASS_BODY()

public:
	/* Common lane template for whole shape */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FZoneLaneProfileRef LaneProfile;

	/* True if lane profile should be reversed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReverseLaneProfile = false;

	/* Shape type, spline or polygon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FZoneShapeType ShapeType;

	/* Polygon shape routing type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ShapeType == FZoneShapeType::Polygon", EditConditionHides))
	EZoneShapePolygonRoutingType PolygonRoutingType = EZoneShapePolygonRoutingType::Bezier;

	/* Zone tags, the lanes inherit zone tags. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FZoneGraphTagMask Tags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UZoneShapeComponent* ZoneShapeComponent;
};
