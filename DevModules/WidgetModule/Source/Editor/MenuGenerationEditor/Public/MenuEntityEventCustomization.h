// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "MenuEntityBaseCustomization.generated.h"

struct FMenuEntityEventSpawnerInfo
{
public:
	FMenuEntityEventSpawnerInfo();
	FMenuEntityEventSpawnerInfo(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects, const TArray<TWeakObjectPtr<UObject>>& InOuterObjects);
	FMenuEntityEventSpawnerInfo(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects, const TArray<UObject*>& InOuterObjects);
	bool IsValid() const;

public:
	TWeakObjectPtr<UObject> SelectedObject;
	TWeakObjectPtr<UObject> OuterObject;
};

/**
 * 
 */
class FMenuEntityEventCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	FMenuEntityEventSpawnerInfo MenuEntityEventSpawnerInfo;

	FName GetEventFullName(const FString& InEventName, const FString& InBaseName);
	FReply SpawnSelectedEvent();
};
