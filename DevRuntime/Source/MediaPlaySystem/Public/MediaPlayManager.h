// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "MediaPlayManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDIAPLAYSYSTEM_API UMediaPlayManager : public UCoreManager
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
};
