// Copyright ChenTaiye 2025. All Rights Reserved.

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
UCLASS(MinimalAPI)
class UHandleManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FHandleInterface */
public:
	EVENTUTILITIES_API virtual void RegisterHandle(UHandleBase* InHandle);
	EVENTUTILITIES_API virtual UHandleBase* RegisterHandle(TSubclassOf<UHandleBase> InHandleClass, FName InHandleName = NAME_None);
	EVENTUTILITIES_API virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FName InHandleName = NAME_None);

	EVENTUTILITIES_API virtual void UnRegisterHandle(UHandleBase* InHandle);
	EVENTUTILITIES_API virtual void UnRegisterHandle(FGuid InHandleID);
	EVENTUTILITIES_API virtual void UnRegisterHandle(FName InHandleName);

	EVENTUTILITIES_API virtual bool IsHandleRegister(const UHandleBase* InHandle);
	EVENTUTILITIES_API virtual bool IsHandleRegister(FGuid InHandleID);
	EVENTUTILITIES_API virtual bool IsHandleRegister(FName InHandleName);

	EVENTUTILITIES_API virtual TArray<UHandleBase*> GetAllHandles() { return Handles; }

	EVENTUTILITIES_API virtual UHandleBase* GetHandle(FGuid InHandleID);
	EVENTUTILITIES_API virtual UHandleBase* GetHandle(FName InHandleName);

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
