// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BlueprintEventNodeSpawner.h"
#include "GenericButtonCollectionCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "K2Node_CustomEvent.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Manager/BlueprintEditorManager.h"
#include "Manager/ManagerStatics.h"
#include "Runtime/WidgetGroupGeneration/Public/GenericButtonCollection.h"

#define LOCTEXT_NAMESPACE "FMenuCollectionCustomization"

TSharedRef<IDetailCustomization> FGenericButtonCollectionCustomization::MakeInstance()
{
	return MakeShareable(new FGenericButtonCollectionCustomization());
}

void FGenericButtonCollectionCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	ObjectsBeingCustomized.Empty();
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	IDetailCategoryBuilder& CollectionCategory = DetailBuilder.EditCategory("Collection");

	CollectionCategory
		.AddCustomRow(FText::GetEmpty())
		.WholeRowContent()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(160.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Pressed"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnPressedEvent)
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(160.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Released"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnReleasedEvent)
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(160.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Hovered"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnHoveredEvent)
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(160.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Unhovered"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnUnhoveredEvent)
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(160.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Clicked"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnClickedEvent)
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(160.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Double Clicked"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnDoubleClickedEvent)
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SBox)
					.MinDesiredWidth(320.f)
					.MinDesiredHeight(32.f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.Text(FText::FromString("On Selection Changed"))
						.OnClicked(this, &FGenericButtonCollectionCustomization::GenerateOnSelectionChangedEvent)
					]
				]
			]
		];
}

UGenericButtonCollection* FGenericButtonCollectionCustomization::GetButtonCollection() const
{
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);

	for (const auto& StrongObject : StrongObjects)
	{
		if (UGenericButtonCollection* Collection = Cast<UGenericButtonCollection>(StrongObject))
		{
			return Collection;
		}
	}

	return nullptr;
}

FReply FGenericButtonCollectionCustomization::GenerateOnPressedEvent()
{
	GenerateEvent(FButtonCollectionEvent::OnPressedEventName);
	return FReply::Handled();
}

FReply FGenericButtonCollectionCustomization::GenerateOnReleasedEvent()
{
	GenerateEvent(FButtonCollectionEvent::OnReleasedEventName);
	return FReply::Handled();
}

FReply FGenericButtonCollectionCustomization::GenerateOnHoveredEvent()
{
	GenerateEvent(FButtonCollectionEvent::OnHoveredEventName);
	return FReply::Handled();
}

FReply FGenericButtonCollectionCustomization::GenerateOnUnhoveredEvent()
{
	GenerateEvent(FButtonCollectionEvent::OnUnhoveredEventName);
	return FReply::Handled();
}

FReply FGenericButtonCollectionCustomization::GenerateOnClickedEvent()
{
	GenerateEvent(FButtonCollectionEvent::OnClickedEventName);
	return FReply::Handled();
}

FReply FGenericButtonCollectionCustomization::GenerateOnDoubleClickedEvent()
{
	GenerateEvent(FButtonCollectionEvent::OnDoubleClickedEventName);
	return FReply::Handled();
}

FReply FGenericButtonCollectionCustomization::GenerateOnSelectionChangedEvent()
{
	TArray<UK2Node_CustomEvent*> Events = GenerateEvent(FButtonCollectionEvent::OnSelectionChangedEventName);
	for (auto Event : Events)
	{
		if (!Event->FindPin(FName(TEXT("Selection"))))
		{
			FEdGraphPinType PinType = FEdGraphPinType();
			PinType.PinCategory = UEdGraphSchema_K2::PC_Boolean;

			Event->CreateUserDefinedPin(FName(TEXT("Selection")), PinType, EGPD_Output);
		}
	}

	return FReply::Handled();
}

TArray<UK2Node_CustomEvent*> FGenericButtonCollectionCustomization::GenerateEvent(FName EventName)
{
	TArray<UK2Node_CustomEvent*> Events;

	UGenericButtonCollection* Collection = GetButtonCollection();
	if (!IsValid(Collection))
	{
		return Events;
	}

	/* Get Collection Blueprint */
	UBlueprint* Blueprint = nullptr;
	if (UBlueprintEditorManager* BlueprintEditorManager = GetManager<UBlueprintEditorManager>())
	{
		Blueprint = BlueprintEditorManager->FindOpenedBlueprintByCDO(Collection);
	}

	if (!IsValid(Blueprint))
	{
		return Events;
	}

	/* Get Blueprint Graph */
	UEdGraph* EdGraph = nullptr;

	TSet<FName> GraphNames;
	FBlueprintEditorUtils::GetAllGraphNames(Blueprint, GraphNames);

	if (GraphNames.Contains(EventName))
	{
		TArray<UEdGraph*> Graphs;
		Blueprint->GetAllGraphs(Graphs);

		/* Find The Graph */
		for (auto& Graph : Graphs)
		{
			if (Graph->GetName().Equals(EventName.ToString(), ESearchCase::CaseSensitive))
			{
				EdGraph = Graph;
				break;
			}
		}
	}
	else
	{
		/* Create The Graph */
		EdGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, EventName, UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());
		FBlueprintEditorUtils::AddUbergraphPage(Blueprint, EdGraph);
	}

	if (!IsValid(EdGraph))
	{
		return Events;
	}

	Blueprint->Modify();

	for (auto& ButtonTag : Collection->GetAllButtonTags())
	{
		FName NodeName = FButtonCollectionEvent::GetEventNodeName(EventName, ButtonTag);
		if (UK2Node_Event* EventNode = FBlueprintEditorUtils::FindCustomEventNode(Blueprint, NodeName))
		{
			if (UK2Node_CustomEvent* CustomEventNode = Cast<UK2Node_CustomEvent>(EventNode))
			{
				Events.Add(CustomEventNode);
			}
		}
		else
		{
			const UBlueprintEventNodeSpawner* BlueprintEventNodeSpawner = UBlueprintEventNodeSpawner::Create(UK2Node_CustomEvent::StaticClass(), NodeName);
			UEdGraphNode* Node = BlueprintEventNodeSpawner->Invoke(EdGraph, IBlueprintNodeBinder::FBindingSet(), EdGraph->GetGoodPlaceForNewNode());

			if (UK2Node_CustomEvent* CustomEventNode = Cast<UK2Node_CustomEvent>(Node))
			{
				Events.Add(CustomEventNode);
			}
		}
	}

	return Events;

	// TSharedPtr<FBlueprintEditor> BlueprintEditor = UBPFunctions_BlueprintEditor::GetBlueprintEditor(Blueprint);
	// if (BlueprintEditor.IsValid())
	// {
	// 	BlueprintEditor->JumpToNode(EventNode);
	// }
}

#undef LOCTEXT_NAMESPACE
