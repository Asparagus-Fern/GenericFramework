// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_GenericButtonWidget.h"

#include "GenericButtonCollection.h"
#include "GenericButtonManager.h"
#include "Manager/ManagerStatics.h"

UGenericButtonCollection* UBPFunctions_GenericButtonWidget::RegisterButtonCollectionByClass(APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	ensure(InCollectionClass);
	check(Player)
	return Cast<UGenericButtonCollection>(GetManagerOwner<UGenericButtonManager>()->RegisterButtonCollection(Player, InCollectionClass, InActived));
}

bool UBPFunctions_GenericButtonWidget::UnRegisterButtonCollection(UGenericButtonCollection* InCollection)
{
	return GetManagerOwner<UGenericButtonManager>()->UnRegisterButtonCollection(InCollection);
}

UGenericButtonCollection* UBPFunctions_GenericButtonWidget::GetButtonCollectionByTag(TSubclassOf<UGenericButtonCollection> InCollectionClass, FGameplayTag InRootButtonTag)
{
	ensure(InCollectionClass);
	return Cast<UGenericButtonCollection>(GetManagerOwner<UGenericButtonManager>()->GetButtonCollection(InRootButtonTag));
}
