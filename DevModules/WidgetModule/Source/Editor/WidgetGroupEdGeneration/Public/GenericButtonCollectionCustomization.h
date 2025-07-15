// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
// #include "MenuCollectionCustomization.generated.h"

class UK2Node_CustomEvent;
class UGenericButtonCollection;

/**
 * 
 */
class FGenericButtonCollectionCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	UGenericButtonCollection* GetButtonCollection() const;
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	
	FReply GenerateOnPressedEvent();
	FReply GenerateOnReleasedEvent();
	FReply GenerateOnHoveredEvent();
	FReply GenerateOnUnhoveredEvent();
	FReply GenerateOnClickedEvent();
	FReply GenerateOnDoubleClickedEvent();
	FReply GenerateOnSelectionChangedEvent();

	TArray<UK2Node_CustomEvent*> GenerateEvent(FName EventName);
};
