// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Interface/StateInterface.h"

#include "CoreType.h"

void IStateInterface::NativeOnCreate()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_HandleOnCreate(Object);
		GenericLOG(GenericLogState, Log, TEXT("On Created : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnActived()
{
}

void IStateInterface::NativeOnActivedFinish()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		OnActivedFinishEvent.Broadcast(Object);
		IStateInterface::Execute_HandleOnActivedFinish(Object);
		GenericLOG(GenericLogState, Log, TEXT("On Actived Finish : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnRefresh()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_HandleOnRefresh(Object);
	}
}

void IStateInterface::NativeOnInactived()
{
}

void IStateInterface::NativeOnInactivedFinish()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_HandleOnInactivedFinish(Object);
		GenericLOG(GenericLogState, Log, TEXT("On Inactived Finish : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnDestroy()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_HandleOnDestroy(Object);
		GenericLOG(GenericLogState, Log, TEXT("On Destroy : %s"), *Object->GetName());
	}
}

bool IStateInterface::GetIsActived() const
{
	return bIsActived;
}

void IStateInterface::SetIsActived(const bool InActived)
{
	if (bIsActived != InActived)
	{
		bIsActived = InActived;
		OnActiveStateChanged();

		if (UObject* Object = Cast<UObject>(this))
		{
			if (bIsActived)
			{
				NativeOnActived();
				IStateInterface::Execute_HandleOnActived(Object);
				GenericLOG(GenericLogState, Log, TEXT("On Actived : %s"), *Object->GetName());
			}
			else
			{
				NativeOnInactived();
				OnInactivedFinishEvent.Broadcast(Object);
				IStateInterface::Execute_HandleOnInactived(Object);
				GenericLOG(GenericLogState, Log, TEXT("On Inactived : %s"), *Object->GetName());
			}
		}
	}
}

void IStateInterface::OnActiveStateChanged()
{
}
