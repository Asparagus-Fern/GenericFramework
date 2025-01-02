// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProcedureFlowManager.generated.h"

class AProcedureFlowActor;
class UProcedureFlowComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnProcedureFlowRegister, UProcedureFlowComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnProcedureFlowRegister, UProcedureFlowComponent*, InComponent);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnProcedureFlowEnter, UProcedureFlowComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnProcedureFlowEnter, UProcedureFlowComponent*, InComponent);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnProcedureFlowExit, UProcedureFlowComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnProcedureFlowExit, UProcedureFlowComponent*, InComponent);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnProcedureFlowUnRegister, UProcedureFlowComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnProcedureFlowUnRegister, UProcedureFlowComponent*, InComponent);

/**
 * 
 */
UCLASS()
class PROCEDUREFLOWSYSTEM_API UProcedureFlowManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* IManagerInterface */
protected:
	virtual FName GetManagerName() override { return FName("ProcedureFlowManager"); }
	virtual int32 GetManagerOrder() override { return 1; }
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* UProcedureFlowManager */
public:
	void RegisterProcedureFlow(const AProcedureFlowActor* InActor);
	void RegisterProcedureFlow(UProcedureFlowComponent* InComponent);

	void UnRegisterProcedureFlow(const AProcedureFlowActor* InActor);
	void UnRegisterProcedureFlow(UProcedureFlowComponent* InComponent);

	void EnterProcedureFlow(const AProcedureFlowActor* InActor);
	void EnterProcedureFlow(const UProcedureFlowComponent* InComponent);
	void EnterProcedureFlow(FGameplayTag InProcedureFlowTag);

	void RefreshCurrentProcedureFlow();
	void ReEnterCurrentProcedureFlow();

	void ExitProcedureFlow(const AProcedureFlowActor* InActor);
	void ExitProcedureFlow(const UProcedureFlowComponent* InComponent);
	void ExitProcedureFlow(FGameplayTag InProcedureFlowTag);

	bool IsProcedureFlowActived(const AProcedureFlowActor* InActor) const;
	bool IsProcedureFlowActived(const UProcedureFlowComponent* InComponent) const;
	bool IsProcedureFlowActived(FGameplayTag InProcedureFlowTag) const;

	FGameplayTag GetCurrentProcedureFlowTag() const;
	UProcedureFlowComponent* GetCurrentProcedureFlowComponent();

	template <typename T>
	T* GetCurrentProcedureFlowComponent()
	{
		return Cast<T>(GetCurrentProcedureFlowComponent());
	}

	TArray<UProcedureFlowComponent*> GetProcedureFlowComponents();
	UProcedureFlowComponent* GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag);

	template <typename T>
	T* GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag)
	{
		return Cast<T>(GetProcedureFlowComponent(InProcedureFlowTag));
	}

private:
	void SortProcedureFlowComponentsAsInitialize();
	void SortProcedureFlowComponentsAsDeinitialize();
	void Execute(const TFunctionRef<void(UProcedureFlowComponent* InComponent)>& Func);

public:
	inline static FDelegate_OnProcedureFlowRegister Delegate_OnProcedureFlowRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowRegister BPDelegate_OnProcedureFlowRegister;

	inline static FDelegate_OnProcedureFlowEnter Delegate_OnProcedureFlowEnter;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowEnter BPDelegate_OnProcedureFlowEnter;

	inline static FDelegate_OnProcedureFlowExit Delegate_OnProcedureFlowExit;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowExit BPDelegate_OnProcedureFlowExit;

	inline static FDelegate_OnProcedureFlowUnRegister Delegate_OnProcedureFlowUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowUnRegister BPDelegate_OnProcedureFlowUnRegister;

private:
	UPROPERTY(Transient)
	FGameplayTag CurrentProcedureFlowTag = FGameplayTag::EmptyTag;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProcedureFlowComponent>> ProcedureFlowComponents;
};
