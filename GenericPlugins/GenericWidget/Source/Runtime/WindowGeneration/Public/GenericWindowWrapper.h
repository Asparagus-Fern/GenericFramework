// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Obect/GenericObject.h"
#include "GenericWindowWrapper.generated.h"

class UGenericWindowContent;
class UGenericWindowStyle;
class UGenericWindowViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericWindowOpened);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericWindowClosed);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericWindowWrapper : public UGenericObject
{
	GENERATED_BODY()

public:
	WINDOWGENERATION_API UGenericWindowWrapper(const FObjectInitializer& ObjectInitializer);
	WINDOWGENERATION_API virtual bool Initialize(UGenericWindowViewModel* InViewModel);
	WINDOWGENERATION_API virtual void Deinitialize();

public:
	UFUNCTION(BlueprintPure)
	WINDOWGENERATION_API APlayerController* GetOwnerPlayer() const;

	UFUNCTION(BlueprintCallable)
	WINDOWGENERATION_API void OpenWindow();

	UFUNCTION(BlueprintCallable)
	WINDOWGENERATION_API void CloseWindow();

	UFUNCTION(BlueprintPure)
	WINDOWGENERATION_API UGenericWindowViewModel* GetWindowViewModel() const;

	UFUNCTION(BlueprintCallable)
	WINDOWGENERATION_API void SetWindowViewModel(UGenericWindowViewModel* InWindowViewModel);

	UFUNCTION(BlueprintPure)
	WINDOWGENERATION_API UGenericWindowContent* GetWindowContentObject();

	UFUNCTION(BlueprintCallable)
	WINDOWGENERATION_API void SetWindowContentObjectByClass(TSubclassOf<UUserWidget> InWidgetClass);

	UFUNCTION(BlueprintCallable)
	WINDOWGENERATION_API void SetWindowContentObject(UUserWidget* InWidget);

	template <typename T>
	T* GetWindowContentObject()
	{
		return Cast<T>(GetWindowContentObject());
	}

	TSharedPtr<SWidget> GetWindowContent();
	void SetWindowContent(TSharedPtr<SWidget> InWindowContent);

	UPROPERTY(BlueprintAssignable)
	FOnGenericWindowOpened OnWindowOpened;

	UPROPERTY(BlueprintAssignable)
	FOnGenericWindowClosed OnWindowClosed;

protected:
	WINDOWGENERATION_API virtual void HandleOnWindowClosed(const TSharedRef<SWindow>& InWindow);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UGenericWindowViewModel> WindowViewModel = nullptr;

private:
	TSharedPtr<SWindow> Window = nullptr;
	TSharedPtr<SWidget> WindowContent = nullptr;

	UPROPERTY()
	TSubclassOf<UGenericWindowContent> WindowContentClass = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericWindowContent> WindowContentObject = nullptr;
};
