// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"
#include "Generic/GenericObject.h"
#include "PropertyDataSource.generated.h"


/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyDataSource : public UGenericObject
{
	GENERATED_BODY()

public:
	static PROPERTYSYSTEM_API UPropertyDataSource* Create(UObject* InContainer, const FString& InGetterPath, const FString& InSetterPath);
	static PROPERTYSYSTEM_API UPropertyDataSource* Create(UObject* InContainer, const TArray<FString>& InGetterPath, const TArray<FString>& InSetterPath);
	static PROPERTYSYSTEM_API UPropertyDataSource* Create(UObject* InContainer, const FCachedPropertyPath& InGetterPath, const FCachedPropertyPath& InSetterPath);

	PROPERTYSYSTEM_API UObject* GetContainer() const;
	PROPERTYSYSTEM_API bool Resolve() const;
	PROPERTYSYSTEM_API FString GetValueAsString() const;
	PROPERTYSYSTEM_API void SetValueFromString(const FString& InValue) const;

	void SetPropertyGetterPath(const FCachedPropertyPath& InGetterPath);
	void SetPropertySetterPath(const FCachedPropertyPath& InSetterPath);

	template <typename SourceType>
	bool GetValue(SourceType& OutValue)
	{
		return PropertyPathHelpers::GetPropertyValue(GetContainer(), PropertyGetterPath, OutValue);
	}

	template <typename SourceType>
	bool SetValue(SourceType InValue)
	{
		return PropertyPathHelpers::SetPropertyValue(GetContainer(), PropertySetterPath, InValue);
	}

private:
	FCachedPropertyPath PropertyGetterPath;
	FCachedPropertyPath PropertySetterPath;
};
