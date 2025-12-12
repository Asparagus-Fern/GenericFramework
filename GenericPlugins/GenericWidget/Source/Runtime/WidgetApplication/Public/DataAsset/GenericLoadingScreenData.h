

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GenericLoadingScreenData.generated.h"

class UGenericLoadingScreenViewModel;

/**
 * 
 */
UCLASS()
class WIDGETAPPLICATION_API UGenericLoadingScreenData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UGenericLoadingScreenViewModel> LoadingScreenViewModel = nullptr;
};
