// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NiagaraUserRedirectionParameterStore.h"
#include "NiagaraVariant.h"
#include "GameFramework/Actor.h"
#include "ApplicationTestActor.generated.h"

class UNiagaraComponent;

UCLASS()
class APPLICATIONRUNTIME_API AApplicationTestActor : public AActor
{
	GENERATED_BODY()

public:
	AApplicationTestActor(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void TimerTest();

	UFUNCTION(BlueprintCallable)
	void TestMessageDialog(FText Message);

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> TestNiagaraComponent = nullptr;

	UPROPERTY(EditAnywhere, Category="Niagara")
	TMap<FNiagaraVariableBase, FNiagaraVariant> TemplateParameterOverrides;

	UPROPERTY(EditAnywhere, Category="Niagara")
	TMap<FNiagaraVariableBase, FNiagaraVariant> InstanceParameterOverrides;

private:
	FTimerHandle TimerHandle;
};
