// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyProxy.h"

#include "PropertyListItemAsset.h"
#include "MVVM/PropertyValueViewModel.h"
#include "UMG/PropertyListItem.h"

void UPropertyProxy::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	/* todo:刪除PropertyListItemAsset，运行时初始化PropertyListItemObjects, 添加一个Asset用来Mapping所需生成的 PropertyValueClass */

	if (PropertyListItemAsset)
	{
		for (auto& ItemObject : PropertyListItemAsset->PropertyListItemObjects)
		{
			if (ItemObject->PropertyValueViewModel)
			{
				ItemObject->PropertyValueViewModel->Initialize();
			}
		}
	}
}

void UPropertyProxy::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();

	if (PropertyListItemAsset)
	{
		for (auto& ItemObject : PropertyListItemAsset->PropertyListItemObjects)
		{
			if (ItemObject->PropertyValueViewModel)
			{
				ItemObject->PropertyValueViewModel->Deinitialize();
			}
		}
	}
}

TArray<UPropertyListItemObject*> UPropertyProxy::GetPropertyListItemObjects() const
{
	return IsValid(PropertyListItemAsset) ? PropertyListItemAsset->PropertyListItemObjects : TArray<UPropertyListItemObject*>();
}

bool UPropertyProxy::ExistPropertyListItemObject(const FName PropertyName) const
{
	if (IsValid(PropertyListItemAsset))
	{
		for (auto& ItemObject : PropertyListItemAsset->PropertyListItemObjects)
		{
			if (ItemObject->PropertyName == PropertyName)
			{
				return true;
			}
		}
	}

	return false;
}

UPropertyListItemObject* UPropertyProxy::GetPropertyListItemObject(const FName PropertyName) const
{
	if (IsValid(PropertyListItemAsset))
	{
		for (auto& ItemObject : PropertyListItemAsset->PropertyListItemObjects)
		{
			if (ItemObject->PropertyName == PropertyName)
			{
				return ItemObject;
			}
		}
	}

	return nullptr;
}

void UPropertyProxy::ApplyPropertyChanged()
{
	if (PropertyListItemAsset)
	{
		for (auto& ItemObject : PropertyListItemAsset->PropertyListItemObjects)
		{
			if (IsValid(ItemObject->PropertyValueViewModel) && ItemObject->PropertyValueViewModel->GetIsPropertyDirty())
			{
				ItemObject->PropertyValueViewModel->Apply();
			}
		}

		OnPropertyApplied();
	}
}

void UPropertyProxy::ReversePropertyChanged()
{
	if (PropertyListItemAsset)
	{
		for (auto& ItemObject : PropertyListItemAsset->PropertyListItemObjects)
		{
			if (IsValid(ItemObject->PropertyValueViewModel) && ItemObject->PropertyValueViewModel->GetIsPropertyDirty())
			{
				ItemObject->PropertyValueViewModel->Reverse();
			}
		}

		OnPropertyReversed();
	}
}

void UPropertyProxy::OnPropertyApplied_Implementation()
{
}

void UPropertyProxy::OnPropertyReversed_Implementation()
{
}
