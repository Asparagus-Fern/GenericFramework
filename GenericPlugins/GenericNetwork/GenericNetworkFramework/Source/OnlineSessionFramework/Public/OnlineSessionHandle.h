// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "Interface/StateInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionHandle.generated.h"

class USessionSettingViewModel;
class FOnlineSessionSettings;

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class ONLINESESSIONFRAMEWORK_API UOnlineSessionHandle : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

public:
	UFUNCTION(BlueprintCallable)
	void CreateSessionByPlayerIndex(int32 InPlayerIndex);

	UFUNCTION(BlueprintCallable)
	void CreateSessionByPlayerUniqueNetID(const FUniqueNetIdRepl& InPlayerNetID);

protected:
	UPROPERTY()
	TObjectPtr<USessionSettingViewModel> SessionSettingViewModel = nullptr;
};
