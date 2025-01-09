// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuCollectionFactory.h"

#include "Entity/MenuCollection.h"

#define LOCTEXT_NAMESPACE "UMenuCollectionFactory"

// UMenuCollectionFactory::UMenuCollectionFactory()
// {
// 	SupportedClass = UMenuCollection::StaticClass();
// }
//
// FText UMenuCollectionFactory::GetDisplayName() const
// {
// 	return LOCTEXT("DisplayName", "Menu Collection");
// }
//
// FText UMenuCollectionFactory::GetToolTip() const
// {
// 	return LOCTEXT("Tooltip", "Manager A Group Of Game Menu");
// }
//
// FString UMenuCollectionFactory::GetDefaultNewAssetName() const
// {
// 	return FString(TEXT("MenuCollection_New"));
// }
//
// UObject* UMenuCollectionFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
// {
// 	// check(InClass->IsChildOf(UMenuCollection::StaticClass()));
// 	// return NewObject<UMenuCollection>(InParent, InClass, InName, Flags | RF_Transactional, Context);
//
// 	return Super::FactoryCreateNew(InClass, InParent, InName, Flags, Context, Warn);
// }

#undef LOCTEXT_NAMESPACE
