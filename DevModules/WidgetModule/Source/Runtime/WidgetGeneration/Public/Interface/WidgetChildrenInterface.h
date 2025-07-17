// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WidgetChildrenInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWidgetChildrenInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIDGETGENERATION_API IWidgetChildrenInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UGenericWidget* GetChildByIndex(int32 InIndex) = 0;
	virtual void AddChild(UGenericWidget* InWidget) = 0;
	virtual void AddChild(UGenericWidget* InWidget, int32 InIndex) = 0;
	virtual void RemoveChild(int32 InIndex) = 0;
	virtual void RemoveChild(UGenericWidget* InWidget) = 0;
	virtual void ClearChildren() = 0;

	template <typename T>
	T* GetChildByIndex(int32 InIndex)
	{
		return Cast<T>(GetChildByIndex(InIndex));
	}
};
