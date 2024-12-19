// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode.h"
#include "ActiveNodeInterface.h"
#include "Components/GameFrameworkComponent.h"
#include "ActiveNodeComponent.generated.h"

UCLASS(Abstract, ClassGroup=(ActiveNode))
class ACTIVENODE_API UActiveNodeComponent : public UGameFrameworkComponent , public IActiveNodeInterface
{
	GENERATED_BODY()
	
public:
	UActiveNodeComponent() = default;
	
	// Sets default values for this component's properties
	UActiveNodeComponent(const FObjectInitializer& ObjectInitializer);
	
	template<class T>
	T* GetOwnerNode() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AActiveNode>::Value, "'T' template parameter to GetOwnerNode must be derived from AActiveNode");
		return Cast<T>(GetOwner());
	}

	// Begin IActiveNodeInterface.
	virtual bool CanUpdate_Implementation() override;
	// End IActiveNodeInterface.
};