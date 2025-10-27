// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interface/ManagerInterface.h"
#include "Manager/ManagerStatics.h"
#include "Subsystems/EngineSubsystem.h"
#include "GenericWindowManager.generated.h"

class UGenericWindowWrapper;
class UGenericWindowViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericWindowManager : public UGameInstanceSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
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

/**
 * 
 */
class WINDOWGENERATION_API FWindowHelper
{
public:
	static UGenericWindowWrapper* RegisterWindowWrapper(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result);
	static UGenericWindowWrapper* RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result);
	static bool UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper);
	static void UnRegisterAllWindowWrapper();
};
