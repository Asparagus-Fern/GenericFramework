// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/PropertyEntity.h"
#include "PropertyCollection.generated.h"

class UPropertyVisualData;

/**
 * 属性集
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyCollection : public UPropertyEntity
{
	GENERATED_BODY()

public:
	/* 获取子属性 */
	virtual TArray<UPropertyEntity*> GetChildProperties() override;

	/* 获取子属性集 */
	TArray<UPropertyCollection*> GetChildCollections() const;

	/* 添加一个属性 */
	UFUNCTION(BlueprintCallable)
	void AddProperty(UPropertyEntity* InProperty);
	
protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyEntity>> ChildProperties;
};
