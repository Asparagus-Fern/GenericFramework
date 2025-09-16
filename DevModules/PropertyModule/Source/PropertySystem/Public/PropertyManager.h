// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ManagerInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PropertyManager.generated.h"

class UPropertyProxy;
/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyManager : public UGameInstanceSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	PROPERTYSYSTEM_API UPropertyProxy* RegisterPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);
	PROPERTYSYSTEM_API void UnRegisterPropertyProxy(UPropertyProxy* InPropertyProxy);
	PROPERTYSYSTEM_API bool ExistPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);
	PROPERTYSYSTEM_API bool ExistPropertyProxy(const UPropertyProxy* InPropertyProxy);
	PROPERTYSYSTEM_API UPropertyProxy* GetPropertyProxy(const TSubclassOf<UPropertyProxy>& InPropertyProxyClass);

private:
	UPROPERTY()
	TArray<TObjectPtr<UPropertyProxy>> PropertyProxies;
};
