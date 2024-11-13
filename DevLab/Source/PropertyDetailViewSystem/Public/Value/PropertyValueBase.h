// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/PropertyEntity.h"
#include "PropertyValueBase.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyValueBase : public UPropertyEntity
{
	GENERATED_BODY()

public:
	/* 应用属性的修改，用当前值设置初始值，在下次读取时将以初始值作为当前值 */
	virtual void StoreInitial() PURE_VIRTUAL(,);

	/* 重置属性的修改，用默认值设置当前值 */
	virtual void ResetToDefault() PURE_VIRTUAL(,);

	/* 回滚当前修改，用修改前的当前值设置当前值 */
	virtual void RestoreToInitial() PURE_VIRTUAL(,);
};
