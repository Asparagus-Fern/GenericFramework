// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "ShortcutWidgetManager.generated.h"

class UUserWidgetBase;
class UShortcutWidgetHandle;

/**
 * 管理UI的快捷键绑定
 */
UCLASS()
class SCREENWIDGETGENERATION_API UShortcutWidgetManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FCoreInternalManager */
public:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* Delegates Bind From UScreenWidgetManager */
protected:
	virtual void OnWidgetOpen(UUserWidgetBase* InWidget);
	virtual void OnWidgetClose(UUserWidgetBase* InWidget);

	/* UShortcutWidgetManager */
public:
	void RegisterShortcutWidgetHandles(UDataTable* InShortcutTable);
	void UnRegisterShortcutWidgetHandles(UDataTable* InShortcutTable);

protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UDataTable>> ShortcutWidgetTables;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UShortcutWidgetHandle>> ShortcutWidgetHandles;

protected:
	UShortcutWidgetHandle* GetShortcutWidgetHandle(const UUserWidgetBase* InWidget);
	UShortcutWidgetHandle* GetShortcutWidgetHandle(TSubclassOf<UUserWidgetBase> InWidgetClass);
};
