// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_GenericButtonWidget.h"

#include "GenericButtonCollection.h"
#include "GenericButtonManager.h"
#include "Manager/ManagerStatics.h"

UGenericButtonCollection* UBPFunctions_GenericButtonWidget::RegisterButtonCollectionByClass(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	ensureAlways(InCollectionClass);
	ensureAlways(Player);

	if (!IsValid(Player))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Player Is InValid"))
		return nullptr;
	}

	if (!InCollectionClass)
	{
		GenericLOG(GenericLogUI, Error, TEXT("CollectionClass Is InValid"))
		return nullptr;
	}

	return Cast<UGenericButtonCollection>(GetManagerOwner<UGenericButtonManager>()->RegisterButtonCollection(Player, InCollectionClass, InActived));
}

bool UBPFunctions_GenericButtonWidget::UnRegisterButtonCollection(UGenericButtonCollection* InCollection)
{
	ensureAlways(InCollection);

	if (!IsValid(InCollection))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Collection Is InValid"))
		return false;
	}

	return GetManagerOwner<UGenericButtonManager>()->UnRegisterButtonCollection(InCollection);
}

UGenericButtonCollection* UBPFunctions_GenericButtonWidget::GetButtonCollectionByTag(TSubclassOf<UGenericButtonCollection> InCollectionClass, FGameplayTag InRootButtonTag)
{
	ensureAlways(InCollectionClass);

	if (!InCollectionClass)
	{
		GenericLOG(GenericLogUI, Error, TEXT("CollectionClass Is InValid"))
		return nullptr;
	}

	return Cast<UGenericButtonCollection>(GetManagerOwner<UGenericButtonManager>()->GetButtonCollection(InRootButtonTag));
}
