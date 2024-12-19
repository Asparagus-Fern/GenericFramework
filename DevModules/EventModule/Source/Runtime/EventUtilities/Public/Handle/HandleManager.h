// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandleInterface.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "HandleManager.generated.h"

class ULevelSequenceHandle;

/**
 * 
 */
UCLASS()
class EVENTUTILITIES_API UHandleManager : public UEngineSubsystem, public FCoreInternalManager, public FHandleInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* FHandleInterface */
public:
	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass) override;
	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FGuid InHandleID) override;
	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FName InHandleName) override;

	virtual void UnRegisterHandle(UHandleBase* InHandle) override;
	virtual void UnRegisterHandle(FGuid InHandleID) override;
	virtual void UnRegisterHandle(FName InHandleName) override;

	virtual bool IsHandleRegister(const UHandleBase* InHandle) override;
	virtual bool IsHandleRegister(FGuid InHandleID) override;
	virtual bool IsHandleRegister(FName InHandleName) override;

	virtual TArray<UHandleBase*> GetAllHandles() override { return Handles; }

	virtual UHandleBase* GetHandle(FGuid InHandleID) override;
	virtual UHandleBase* GetHandle(FName InHandleName) override;

	/* UHandleManager */
public:
	template <typename T>
	T* RegisterHandle(UObject* Outer)
	{
		return Cast<T>(RegisterHandle(Outer, T::StaticClass()));
	}

	template <typename T>
	T* RegisterHandle(UObject* Outer, FGuid InHandleID)
	{
		return Cast<T>(RegisterHandle(Outer, T::StaticClass(), InHandleID));
	}

	template <typename T>
	T* RegisterHandle(UObject* Outer, FName InHandleName)
	{
		return Cast<T>(RegisterHandle(Outer, T::StaticClass(), InHandleName));
	}

	template <typename T>
	TArray<T*> GetHandles()
	{
		TArray<T*> Results;

		for (auto& Handle : Handles)
		{
			if (Handle->GetClass() == T::StaticClass())
			{
				Results.Add(Cast<T>(Handle));
			}
		}

		return Results;
	}

	template <typename T>
	T* GetHandle(FGuid InHandleID)
	{
		return Cast<T>(GetHandle(InHandleID));
	}

	template <typename T>
	T* GetHandle(FName InHandleName)
	{
		return Cast<T>(GetHandle(InHandleName));
	}

protected:
	UPROPERTY()
	TArray<UHandleBase*> Handles;
};
