// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/MenuCollectionBlueprint.h"

#include "Blueprint/MenuCollectionBlueprintGeneratedClass.h"
#include "Entity/MenuCollection.h"

UMenuCollectionBlueprint::UMenuCollectionBlueprint()
{
	BlueprintType = BPTYPE_Normal;
}

#if WITH_EDITOR

UClass* UMenuCollectionBlueprint::GetBlueprintClass() const
{
	return UMenuCollectionBlueprintGeneratedClass::StaticClass();
}

void UMenuCollectionBlueprint::GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const
{
	AllowedChildrenOfClasses.Add(UMenuCollection::StaticClass());
}

#endif

UMenuCollectionBlueprintGeneratedClass* UMenuCollectionBlueprint::GetGeneratedClass() const
{
	return Cast<UMenuCollectionBlueprintGeneratedClass>(*GeneratedClass);
}
