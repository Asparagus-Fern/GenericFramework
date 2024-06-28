// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/GameplayProcedureFactory.h"

#include "Kismet2/KismetEditorUtilities.h"
#include "Procedure/GameplayProcedure.h"

#define LOCTEXT_NAMESPACE "UGameplayProcedureFactory"

UGameplayProcedureFactory::UGameplayProcedureFactory()
{
	SupportedClass = UGameplayProcedure::StaticClass();
	AssetName = LOCTEXT("AssetName", "Gameplay Procedure");
	bPickClass = true;
}

UObject* UGameplayProcedureFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	if (IsValid(PickClass))
	{
		// FKismetEditorUtilities::CreateBlueprint(PickClass, InParent, InName, EBlueprintType::BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
		return NewObject<UGameplayProcedure>(InParent, PickClass, InName, Flags);
	}
	else
	{
		ensure(InClass->IsChildOf(UGameplayProcedure::StaticClass()));
		return NewObject<UGameplayProcedure>(InParent, InClass, InName, Flags);
	}
}

void UGameplayProcedureFactory::ConfigureFilter(TSharedRef<FAssetFilter>& Filter)
{
	Super::ConfigureFilter(Filter);
	Filter->AllowedChildrenOfClasses.Add(UGameplayProcedure::StaticClass());
}

#undef LOCTEXT_NAMESPACE
