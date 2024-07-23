// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldWidgetType.h"
#include "Manager/CoreManager.h"
#include "WorldWidgetManager.generated.h"

class UWorldWidgetManager;
class UCanvasPanel;
class AWorldWidgetPoint;

/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetPanel : public UObject, public IProcedureInterface
{
	GENERATED_UCLASS_BODY()
	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* FWorldWidgetPanel */
protected:
	UPROPERTY()
	UCanvasPanel* Panel;

	UPROPERTY()
	TMap<AWorldWidgetPoint*, UWorldWidget*> WorldWidgets;

public:
	virtual void AddWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RemoveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void ClearWorldWidget();

	virtual void ActiveWorldWidget(const AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void InactiveWorldWidget(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void ActiveWorldWidgets(TArray<AWorldWidgetPoint*> InWorldWidgetPoints);
	virtual void InactiveWorldWidgets(TArray<AWorldWidgetPoint*> InWorldWidgetPoints);

	virtual UCanvasPanel* GetPanel() { return Panel; }
	TMap<AWorldWidgetPoint*, UWorldWidget*>& GetWorldWidgets() { return WorldWidgets; }

protected:
	virtual TArray<UWorldWidget*> GetWorldWidgetsByPoints(TArray<AWorldWidgetPoint*> InPoints);
};


/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UWorldWidgetManager();

	/* FTickableGameObject */
public:
	virtual bool IsTickable() const override { return true; }
	virtual void Tick(float DeltaTime) override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;
	virtual void NativeOnBeginPlay() override;
	virtual void NativeOnEndPlay() override;

	/* UWorldWidgetManager */
public:
	UPROPERTY(Transient, VisibleAnywhere)
	TArray<AWorldWidgetPoint*> WorldWidgetPoints;

public:
	void ActiveWorldWidgetPoint(AWorldWidgetPoint* InPoint);
	void ActiveWorldWidgetPoint(FGameplayTag InPointTag);
	void InactiveWorldWidgetPoint(AWorldWidgetPoint* InPoint);
	void InactiveWorldWidgetPoint(FGameplayTag InPointTag);
	TArray<AWorldWidgetPoint*> GetWorldWidgetPoints() const;
	TArray<AWorldWidgetPoint*> GetWorldWidgetPoints(FGameplayTag InPointTag) const;

protected:
	virtual void GenerateWorldWidgetPanel();

public:
	virtual void AddWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RemoveWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RefreshWolrdWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RefreshAllWorldWidgetPoint();

	virtual void AddPanelWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RemovePanelWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RefreshPanelWorldWidgetPoint(AWorldWidgetPoint* InWorldWidgetPoint);
	virtual void RefreshAllPanelWorldWidgetPoint();

protected:
	UPROPERTY()
	TArray<UWorldWidgetPanel*> WorldWidgetPanels;

	virtual UWorldWidgetPanel* CreateWorldWidgetPanel();
	virtual void ClearupWorldWidgetPanel();
};
