// Copyright ChenTaiye 2025. All Rights Reserved.

#include "DataSource/PropertyDataSourceCollection.h"

UPropertyProxy* UPropertyDataSourceCollection::GetOwnerPropertyProxy() const
{
	return OwnerPropertyProxy.IsValid() ? OwnerPropertyProxy.Get() : nullptr;
}

void UPropertyDataSourceCollection::SetOwnerPropertyProxy(UPropertyProxy* InProxy)
{
	OwnerPropertyProxy = InProxy;
}

void UPropertyDataSourceCollection::GeneratePropertyViewModels_Implementation(TArray<UPropertyViewModel*>& Result)
{
}

void UPropertyDataSourceCollection::OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel)
{
}

void UPropertyDataSourceCollection::OnPropertyReset_Implementation(UPropertyViewModel* InPropertyViewModel)
{
}

void UPropertyDataSourceCollection::OnPropertyChanged_Implementation(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason)
{
}
