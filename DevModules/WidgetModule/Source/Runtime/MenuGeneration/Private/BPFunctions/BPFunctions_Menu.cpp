// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Menu.h"

#include "MenuGenerationManager.h"
#include "Collection/MenuCollection.h"
#include "Manager/ManagerStatics.h"

UMenuCollection* UBPFunctions_Menu::RegisterMenuCollectionByClass(TSubclassOf<UMenuCollection> InCollectionClass, bool InActived)
{
	ensure(InCollectionClass);

	if (UMenuGenerationManager* MenuGenerationManager = GetManager<UMenuGenerationManager>())
	{
		return Cast<UMenuCollection>(MenuGenerationManager->RegisterMenuCollection(InCollectionClass, InActived));
	}

	return nullptr;
}

bool UBPFunctions_Menu::RegisterMenuCollection(UMenuCollection* InCollection, bool InActived)
{
	if (UMenuGenerationManager* MenuGenerationManager = GetManager<UMenuGenerationManager>())
	{
		return MenuGenerationManager->RegisterMenuCollection(InCollection, InActived);
	}
	return false;
}

bool UBPFunctions_Menu::UnRegisterMenuCollection(UMenuCollection* InCollection)
{
	if (UMenuGenerationManager* MenuGenerationManager = GetManager<UMenuGenerationManager>())
	{
		return MenuGenerationManager->UnRegisterMenuCollection(InCollection);
	}
	return false;
}
