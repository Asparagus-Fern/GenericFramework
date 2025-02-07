// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Common/CommonObject.h"
#include "Entity/WidgetEntity.h"
#include "Interface/StateInterface.h"
#include "MenuCollection.generated.h"

class UMenuGroupEntity;
class UMenuEntity;
class UMenuEntityBase;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuCollection : public UCommonObject, public IStateInterface
{
	GENERATED_BODY()

public:
	UMenuCollection(const FObjectInitializer& ObjectInitializer);

	/* IStateInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
	virtual void NativeOnDestroy() override;

	UFUNCTION(BlueprintPure)
	virtual bool GetIsActived() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetIsActived(const bool InActived) override;

	/* Delegate From GameHUDManager */
protected:
	void PostHUDCreated();

	/* UMenuCollection */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> MenuTagTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMenuEntity> MenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMenuGroupEntity> MenuGroupClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag OwnerTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta = (TitleProperty = "MenuMainName"))
	TArray<TObjectPtr<UMenuEntityBase>> MenuEntities;
	
#if WITH_EDITOR

public:
	void ReGenerateMenu();
	void ReGenerateMenu(UDataTable* InMenuTagTable);

	void GenerateMenu();
	void GenerateMenu(UDataTable* InMenuTagTable);

	void ClearupMenu();

#endif

public:
	UFUNCTION(BlueprintPure)
	bool IsContainMenuTag(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure)
	bool IsContainMenu(const UMenuEntityBase* InMenuEntity);

	UFUNCTION(BlueprintPure)
	UMenuEntityBase* GetRootMenuEntity();

	UFUNCTION(BlueprintPure)
	UMenuEntityBase* GetMenuEntity(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure)
	TArray<UMenuEntityBase*> GetMenuEntities(const TArray<FGameplayTag>& InMenuTags);

	UFUNCTION(BlueprintPure)
	UMenuEntityBase* GetParentMenuEntity(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure)
	TArray<UMenuEntityBase*> GetChildMenuEntities(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure)
	TArray<UMenuEntityBase*> GetDirectChildMenuEntities(FGameplayTag InMenuTag);

public:
	UFUNCTION(BlueprintCallable)
	void ActiveMenu(UMenuEntityBase* InEntity);

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer GameplayTagContainer;
};
