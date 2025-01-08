// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Common/CommonObject.h"
#include "MenuCollection.generated.h"

class UMenuEntity;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuCollection : public UCommonObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> MenuTagTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag OwnerTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMenuEntity*> MenuEntities;

public:
	void GenerateMenu(UDataTable* InMenuTagTable);
	void ClearupMenu();

	bool ContainerMenu(FGameplayTag InMenuTag);
	bool ContainerMenu(const UMenuEntity* InMenuEntity);

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer GameplayTagContainer;
};
