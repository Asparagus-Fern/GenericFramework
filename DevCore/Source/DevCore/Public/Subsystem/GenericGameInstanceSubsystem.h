// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GenericGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGenericGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
#if WITH_EDITOR
	//Before Subsystem Initialize, Delegate Broadcast From FWorldDelegates::OnPIEStarted
	//Before Subsystem Initialize, Delegate Broadcast From FWorldDelegates::OnPIEMapCreated
#endif
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
#if WITH_EDITOR
	//After Subsystem Initialize, Delegate Broadcast From FWorldDelegates::OnPIEMapReady
#endif
	virtual void Deinitialize() override;

public:
	template <typename T>
	T* GetGameInstance()
	{
		return Cast<T>(GetOuter());
	}
};
