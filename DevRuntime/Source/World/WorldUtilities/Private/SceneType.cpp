#include "SceneType.h"

FFindActorHandle::FFindActorHandle()
	: ID(FGuid::NewGuid())
{
}

bool FFindActorHandle::GetIsValid() const
{
	return (FindActorMethod == EFindActorMethod::Class && IsValid(ActorClass))
		|| (FindActorMethod == EFindActorMethod::Tag && !ActorTag.IsNone())
		|| (FindActorMethod == EFindActorMethod::ClassAndTag && IsValid(ActorClass) && !ActorTag.IsNone())
		|| (FindActorMethod == EFindActorMethod::Interface && IsValid(ActorInterface));
}

bool FHandleActor::GetIsValid() const
{
	TSet<EHandleActorMethod> ValidHandleActorMethods;
	for (auto& HandleActorMethod : HandleActorMethods)
	{
		if (HandleActorMethod != EHandleActorMethod::None)
		{
			ValidHandleActorMethods.Add(HandleActorMethod);
		}
	}

	return !ValidHandleActorMethods.IsEmpty();
}
