// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ApplicationTestActor.generated.h"

UCLASS()
class APPLICATIONRUNTIME_API AApplicationTestActor : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	void TimerTest();

	UFUNCTION(BlueprintCallable)
	void TestMessageDialog(FText Message);
	
private:
	FTimerHandle TimerHandle;
};
