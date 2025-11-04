// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "GenericLocalPlayerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGenericLocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;

public:
	template <typename PlayerType = APlayerController>
	PlayerType* GetPlayerController() const
	{
		return Cast<PlayerType>(Player);
	}

	template <typename PlayerType = APlayerController>
	PlayerType* GetPlayerControllerChecked() const
	{
		return CastChecked<PlayerType>(Player);
	}

private:
	UPROPERTY()
	TObjectPtr<APlayerController> Player = nullptr;
};
