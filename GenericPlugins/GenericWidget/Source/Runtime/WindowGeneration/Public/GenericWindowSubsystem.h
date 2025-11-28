// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/GenericGameInstanceSubsystem.h"
#include "GenericWindowSubsystem.generated.h"

class UGenericWindowWrapper;
class UGenericWindowViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericWindowSubsystem : public UGenericGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static WINDOWGENERATION_API UGenericWindowSubsystem* Get(const UObject* WorldContextObject);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	WINDOWGENERATION_API UGenericWindowWrapper* RegisterWindowWrapper(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result);
	WINDOWGENERATION_API UGenericWindowWrapper* RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result);
	WINDOWGENERATION_API bool UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper);
	WINDOWGENERATION_API void UnRegisterAllWindowWrapper();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UGenericWindowWrapper>> WindowWrappers;
};
