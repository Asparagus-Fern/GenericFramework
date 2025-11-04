// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "ProcedureFlowSubsystem.generated.h"

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
UCLASS(MinimalAPI)
class UProcedureFlowSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static PROCEDUREFLOWSYSTEM_API UProcedureFlowSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldMatchStarting() override;
	virtual void OnWorldBeginTearDown(UWorld* InWorld) override;
	virtual void Deinitialize() override;

	/* UProcedureFlowSubsystem */
public:
	PROCEDUREFLOWSYSTEM_API void RegisterProcedureFlow(const AProcedureFlowActor* InActor);
	PROCEDUREFLOWSYSTEM_API void RegisterProcedureFlow(UProcedureFlowComponent* InComponent);

	PROCEDUREFLOWSYSTEM_API void UnRegisterProcedureFlow(const AProcedureFlowActor* InActor);
	PROCEDUREFLOWSYSTEM_API void UnRegisterProcedureFlow(UProcedureFlowComponent* InComponent);

	PROCEDUREFLOWSYSTEM_API void EnterProcedureFlow(const AProcedureFlowActor* InActor);
	PROCEDUREFLOWSYSTEM_API void EnterProcedureFlow(const UProcedureFlowComponent* InComponent);
	PROCEDUREFLOWSYSTEM_API void EnterProcedureFlow(FGameplayTag InProcedureFlowTag);

	PROCEDUREFLOWSYSTEM_API void RefreshCurrentProcedureFlow();
	PROCEDUREFLOWSYSTEM_API void ReEnterCurrentProcedureFlow();

	PROCEDUREFLOWSYSTEM_API void ExitProcedureFlow(const AProcedureFlowActor* InActor);
	PROCEDUREFLOWSYSTEM_API void ExitProcedureFlow(const UProcedureFlowComponent* InComponent);
	PROCEDUREFLOWSYSTEM_API void ExitProcedureFlow(FGameplayTag InProcedureFlowTag);

	PROCEDUREFLOWSYSTEM_API bool IsProcedureFlowActived(const AProcedureFlowActor* InActor) const;
	PROCEDUREFLOWSYSTEM_API bool IsProcedureFlowActived(const UProcedureFlowComponent* InComponent) const;
	PROCEDUREFLOWSYSTEM_API bool IsProcedureFlowActived(FGameplayTag InProcedureFlowTag) const;

	PROCEDUREFLOWSYSTEM_API FGameplayTag GetCurrentProcedureFlowTag() const;
	PROCEDUREFLOWSYSTEM_API UProcedureFlowComponent* GetCurrentProcedureFlowComponent();

	template <typename T>
	T* GetCurrentProcedureFlowComponent()
	{
		return Cast<T>(GetCurrentProcedureFlowComponent());
	}

	PROCEDUREFLOWSYSTEM_API TArray<UProcedureFlowComponent*> GetProcedureFlowComponents();
	PROCEDUREFLOWSYSTEM_API UProcedureFlowComponent* GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag);

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
	PROCEDUREFLOWSYSTEM_API inline static FDelegate_OnProcedureFlowRegister Delegate_OnProcedureFlowRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowRegister BPDelegate_OnProcedureFlowRegister;

	PROCEDUREFLOWSYSTEM_API inline static FDelegate_OnProcedureFlowEnter Delegate_OnProcedureFlowEnter;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowEnter BPDelegate_OnProcedureFlowEnter;

	PROCEDUREFLOWSYSTEM_API inline static FDelegate_OnProcedureFlowExit Delegate_OnProcedureFlowExit;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowExit BPDelegate_OnProcedureFlowExit;

	PROCEDUREFLOWSYSTEM_API inline static FDelegate_OnProcedureFlowUnRegister Delegate_OnProcedureFlowUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnProcedureFlowUnRegister BPDelegate_OnProcedureFlowUnRegister;

private:
	UPROPERTY(Transient)
	FGameplayTag CurrentProcedureFlowTag = FGameplayTag::EmptyTag;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UProcedureFlowComponent>> ProcedureFlowComponents;
};
