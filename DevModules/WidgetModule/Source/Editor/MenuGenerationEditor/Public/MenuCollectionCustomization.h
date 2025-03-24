// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
// #include "MenuCollectionCustomization.generated.h"

/**
 * 
 */
class FMenuCollectionCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	TSharedPtr<IPropertyHandle> MenuEntitiesHandle;
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;

	FReply GenerateMenuEntities() const;
};
