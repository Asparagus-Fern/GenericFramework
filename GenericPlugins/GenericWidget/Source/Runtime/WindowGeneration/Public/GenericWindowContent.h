// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "GenericWindowContent.generated.h"

class UGenericWindowWrapper;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericWindowContent : public UGenericWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	WINDOWGENERATION_API UGenericWindowWrapper* GetWindowWrapper() const;
	WINDOWGENERATION_API void SetWindowWrapper(UGenericWindowWrapper* InWindowWrapper);

protected:
	WINDOWGENERATION_API virtual void OnChildAdded_Implementation(UUserWidget* InWidget, int32 InIndex) override;
	WINDOWGENERATION_API virtual void OnChildRemoved_Implementation(UUserWidget* InWidget, int32 InIndex) override;

private:
	UPROPERTY()
	TWeakObjectPtr<UGenericWindowWrapper> WindowWrapper = nullptr;
};
