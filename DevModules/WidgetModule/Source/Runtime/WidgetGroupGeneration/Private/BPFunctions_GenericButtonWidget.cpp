// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_GenericButtonWidget.h"

#include "GenericButtonCollection.h"
#include "GenericButtonManager.h"
#include "Manager/ManagerStatics.h"

UGenericButtonCollection* UBPFunctions_GenericButtonWidget::RegisterButtonCollectionByClass(TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived)
{
	ensure(InCollectionClass);
	return Cast<UGenericButtonCollection>(GetManagerOwner<UGenericButtonManager>()->RegisterButtonCollection(InCollectionClass, InActived));
}

bool UBPFunctions_GenericButtonWidget::RegisterButtonCollection(UGenericButtonCollection* InCollection, bool InActived)
{
	return GetManagerOwner<UGenericButtonManager>()->RegisterButtonCollection(InCollection, InActived);
}

bool UBPFunctions_GenericButtonWidget::UnRegisterButtonCollection(UGenericButtonCollection* InCollection)
{
	return GetManagerOwner<UGenericButtonManager>()->UnRegisterButtonCollection(InCollection);
}
