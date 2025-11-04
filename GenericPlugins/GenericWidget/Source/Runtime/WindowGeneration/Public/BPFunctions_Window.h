// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Window.generated.h"

class UGenericWindowViewModel;
class UGenericWindowWrapper;

/**
 * 
 */
UCLASS()
class WINDOWGENERATION_API UBPFunctions_Window : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category = "Window", DisplayName="Register Window Wrapper (Class)")
	static UGenericWindowWrapper* RegisterWindowWrapperByClass(const UObject* WorldContextObject, APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category = "Window", DisplayName="Register Window Wrapper (Object)")
	static UGenericWindowWrapper* RegisterWindowWrapper(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category = "Window", DisplayName="UnRegister Window Wrapper")
	static bool UnRegisterWindowWrapper(const UObject* WorldContextObject, UGenericWindowWrapper* InWrapper);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category = "Window", DisplayName="UnRegister All Window Wrapper")
	static void UnRegisterAllWindowWrapper(const UObject* WorldContextObject);
};
