// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_MakeContainer.h"
#include "K2Node_GetPropertyPath.generated.h"

class FKCHandler_GetPropertyPath : public FNodeHandlingFunctor
{
public:
	FKCHandler_GetPropertyPath(FKismetCompilerContext& InCompilerContext);

	virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;
	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;

protected:
	EKismetCompiledStatementType CompiledStatementType;
};

/**
 * 
 */
UCLASS()
class PROPERTYNODE_API UK2Node_GetPropertyPath : public UK2Node, public IK2Node_AddPinInterface
{
	GENERATED_BODY()

public:
	UK2Node_GetPropertyPath(const FObjectInitializer& ObjectInitializer);

	/* UEdGraphNode */
public:
	virtual void AllocateDefaultPins() override;
	virtual void PostReconstructNode() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

	/* UK2Node */
public:
	virtual bool IsNodePure() const override { return true; }
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual int32 GetNodeRefreshPriority() const override { return EBaseNodeRefreshPriority::Low_UsesDependentWildcard; }
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;

	/* IK2Node_AddPinInterface */
public:
	virtual void AddInputPin() override;
	virtual void RemoveInputPin(UEdGraphPin* Pin) override;

	/* UK2Node_GetPropertyPath */
protected:
	virtual FName GetPinName(int32 PinIndex) const;
	virtual void GetKeyAndValuePins(TArray<UEdGraphPin*>& KeyPins, TArray<UEdGraphPin*>& ValuePins) const;
	void SyncPinNames();
	
protected:
	UPROPERTY()
	int32 NumInputs = 1;
};
