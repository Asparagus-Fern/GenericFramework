// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interface/ManagerInterface.h"
#include "Manager/ManagerStatics.h"
#include "Subsystems/EngineSubsystem.h"
#include "GenericWindowManager.generated.h"

class UGenericMessageDialog;
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

	WINDOWGENERATION_API FGameplayTag OpenMessageDialog(APlayerController* InPlayer, const TSubclassOf<UGenericMessageDialog>& MessageDialogClass, bool& Result);
	WINDOWGENERATION_API FGameplayTag OpenMessageDialog(APlayerController* InPlayer, UGenericMessageDialog* MessageDialog, bool& Result);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UGenericWindowWrapper>> WindowWrappers;
};

class WINDOWGENERATION_API FWindowHelper
{
public:
	static UGenericWindowWrapper* RegisterWindowWrapper(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result)
	{
		if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
		{
			return GenericWindowManager->RegisterWindowWrapper(InPlayer, WindowViewModelClass, Result);
		}
		return nullptr;
	}

	static UGenericWindowWrapper* RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result)
	{
		if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
		{
			return GenericWindowManager->RegisterWindowWrapper(InPlayer, WindowViewModel, Result);
		}
		return nullptr;
	}

	static bool UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper)
	{
		if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
		{
			return GenericWindowManager->UnRegisterWindowWrapper(InWrapper);
		}
		return false;
	}

	static void UnRegisterAllWindowWrapper()
	{
		if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
		{
			return GenericWindowManager->UnRegisterAllWindowWrapper();
		}
	}

	static FGameplayTag OpenMessageDialog(APlayerController* InPlayer, const TSubclassOf<UGenericMessageDialog>& MessageDialogClass, bool& Result)
	{
		if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
		{
			return GenericWindowManager->OpenMessageDialog(InPlayer, MessageDialogClass, Result);
		}
		return FGameplayTag::EmptyTag;
	}

	static FGameplayTag OpenMessageDialog(APlayerController* InPlayer, UGenericMessageDialog* MessageDialog, bool& Result)
	{
		if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
		{
			return GenericWindowManager->OpenMessageDialog(InPlayer, MessageDialog, Result);
		}
		return FGameplayTag::EmptyTag;
	}
};
