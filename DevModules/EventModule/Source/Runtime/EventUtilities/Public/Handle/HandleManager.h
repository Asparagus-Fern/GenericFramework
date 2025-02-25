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
class EVENTUTILITIES_API UHandleManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FHandleInterface */
public:
	virtual void RegisterHandle(UHandleBase* InHandle);
	virtual UHandleBase* RegisterHandle(TSubclassOf<UHandleBase> InHandleClass, FName InHandleName = NAME_None);
	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FName InHandleName = NAME_None);

	virtual void UnRegisterHandle(UHandleBase* InHandle);
	virtual void UnRegisterHandle(FGuid InHandleID);
	virtual void UnRegisterHandle(FName InHandleName);

	virtual bool IsHandleRegister(const UHandleBase* InHandle);
	virtual bool IsHandleRegister(FGuid InHandleID);
	virtual bool IsHandleRegister(FName InHandleName);

	virtual TArray<UHandleBase*> GetAllHandles() { return Handles; }

	virtual UHandleBase* GetHandle(FGuid InHandleID);
	virtual UHandleBase* GetHandle(FName InHandleName);

	/* UHandleManager */
public:
	template <typename T>
	T* RegisterHandle(FName InHandleName = NAME_None)
	{
		return Cast<T>(RegisterHandle(T::StaticClass(), InHandleName));
	}

	template <typename T>
	T* RegisterHandle(UObject* Outer, FName InHandleName = NAME_None)
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
	UPROPERTY(Transient)
	TArray<UHandleBase*> Handles;
};
