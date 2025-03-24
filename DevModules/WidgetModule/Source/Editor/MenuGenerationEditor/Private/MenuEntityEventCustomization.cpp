// Copyright ChenTaiye 2025. All Rights Reserved.


#include "MenuEntityEventCustomization.h"

#include "BlueprintEditor.h"
#include "BlueprintEventNodeSpawner.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IPropertyUtilities.h"
#include "K2Node_CustomEvent.h"
#include "BPFunctions/BPFunctions_BlueprintEditor.h"
#include "Entity/MenuEntityBase.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Manager/BlueprintEditorNodeSpawnerManager.h"
#include "Manager/ManagerStatics.h"

FMenuEntityEventSpawnerInfo::FMenuEntityEventSpawnerInfo()
{
}

FMenuEntityEventSpawnerInfo::FMenuEntityEventSpawnerInfo(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects, const TArray<TWeakObjectPtr<UObject>>& InOuterObjects)
{
	if (InSelectedObjects.Num() == 1)
	{
		SelectedObject = InSelectedObjects[0];
	}
	if (InOuterObjects.Num() == 1)
	{
		OuterObject = InOuterObjects[0];
	}
}

FMenuEntityEventSpawnerInfo::FMenuEntityEventSpawnerInfo(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects, const TArray<UObject*>& InOuterObjects)
{
	if (InSelectedObjects.Num() == 1)
	{
		SelectedObject = InSelectedObjects[0];
	}
	if (InOuterObjects.Num() == 1)
	{
		OuterObject = InOuterObjects[0];
	}
}

bool FMenuEntityEventSpawnerInfo::IsValid() const
{
	return SelectedObject.IsValid() && OuterObject.IsValid();
}

TSharedRef<IPropertyTypeCustomization> FMenuEntityEventCustomization::MakeInstance()
{
	return MakeShareable(new FMenuEntityEventCustomization);
}

void FMenuEntityEventCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}

void FMenuEntityEventCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	TArray<UObject*> OuterObjects;
	PropertyHandle->GetOuterObjects(OuterObjects);
	MenuEntityEventSpawnerInfo = FMenuEntityEventSpawnerInfo(CustomizationUtils.GetPropertyUtilities()->GetSelectedObjects(), OuterObjects);

	if (!MenuEntityEventSpawnerInfo.IsValid())
	{
		return;
	}

	/* Skip The Root Menu */
	if (const UMenuEntityBase* MenuEntityBase = Cast<UMenuEntityBase>(MenuEntityEventSpawnerInfo.OuterObject))
	{
		if (MenuEntityBase->IsRootMenu())
		{
			return;
		}
	}

	/* Only Customize CDO Detail */
	if (!MenuEntityEventSpawnerInfo.SelectedObject->HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	ChildBuilder.AddCustomRow(FText::GetEmpty())
		.WholeRowContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString("Selected"))
				.OnClicked(this, &FMenuEntityEventCustomization::SpawnSelectedEvent)
			]
		];
}

FName FMenuEntityEventCustomization::GetEventFullName(const FString& InEventName, const FString& InBaseName)
{
	return FName(InEventName + InBaseName);
}

FReply FMenuEntityEventCustomization::SpawnSelectedEvent()
{
	if (UBlueprint* Blueprint = GetManager<UBlueprintEditorNodeSpawnerManager>()->FindOpenedBlueprintByCDO(MenuEntityEventSpawnerInfo.SelectedObject.Get()))
	{
		if (UMenuEntityBase* MenuEntityBase = Cast<UMenuEntityBase>(MenuEntityEventSpawnerInfo.OuterObject))
		{
			UEdGraph* EventGraph = FBlueprintEditorUtils::FindEventGraph(Blueprint);
			const FName EventName = MenuEntityBase->GetSelectedEventName();

			/* Find If The Event Node Already Created */
			if (const UK2Node_Event* EventNode = FBlueprintEditorUtils::FindCustomEventNode(Blueprint, EventName))
			{
				TSharedPtr<FBlueprintEditor> BlueprintEditor = UBPFunctions_BlueprintEditor::GetBlueprintEditor(Blueprint);
				if (BlueprintEditor.IsValid())
				{
					BlueprintEditor->JumpToNode(EventNode);
				}
			}
			else
			{
				Blueprint->Modify();

				const UBlueprintEventNodeSpawner* BlueprintEventNodeSpawner = UBlueprintEventNodeSpawner::Create(UK2Node_CustomEvent::StaticClass(), EventName);
				UEdGraphNode* Node = BlueprintEventNodeSpawner->Invoke(EventGraph, IBlueprintNodeBinder::FBindingSet(), EventGraph->GetGoodPlaceForNewNode());

				/* Create Custom Event Node And Add Default Pin */
				if (UK2Node_CustomEvent* CustomEventNode = Cast<UK2Node_CustomEvent>(Node))
				{
					FEdGraphPinType PinType = FEdGraphPinType();
					PinType.PinCategory = UEdGraphSchema_K2::PC_Boolean;

					CustomEventNode->CreateUserDefinedPin(FName("Selection"), PinType, EGPD_Output);
				}
			}
		}
	}


	return FReply::Handled();
}
