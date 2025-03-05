// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValue.h"

#include "Base/PropertyDataSource.h"

void UPropertyDiscreteValue::Startup()
{
	Getter->Startup(Source, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
}

void UPropertyDiscreteValue::OnInitialized()
{
#if !UE_BUILD_SHIPPING
	ensureAlways(Getter);
	ensureAlwaysMsgf(Getter->Resolve(Source), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
	ensureAlways(Setter);
	ensureAlwaysMsgf(Setter->Resolve(Source), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
#endif

	Super::OnInitialized();
}

void UPropertyDiscreteValue::ResetToDefault()
{
	SetDiscreteValue(DefaultValue, EPropertyChangeReason::ResetToDefault);
}

void UPropertyDiscreteValue::StoreToInitial()
{
	InitialValue = GetValue();
}

void UPropertyDiscreteValue::ResetToInitial()
{
	SetDiscreteValue(InitialValue, EPropertyChangeReason::ResetToDefault);
}

void UPropertyDiscreteValue::OnDataSourcesReady()
{
	FinishStartup();
}

void UPropertyDiscreteValue::SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter)
{
	Getter = InGetter;
}

void UPropertyDiscreteValue::SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter)
{
	Setter = InSetter;
}

FString UPropertyDiscreteValue::GetDefaultValue() const
{
	return DefaultValue;
}

void UPropertyDiscreteValue::SetDefaultValue(FString InValue)
{
	DefaultValue = InValue;
}

FString UPropertyDiscreteValue::GetValue() const
{
	return Getter->GetValue(Source);
}

void UPropertyDiscreteValue::SetValue(FString InValue)
{
	SetDiscreteValue(InValue, EPropertyChangeReason::Change);
}

void UPropertyDiscreteValue::SetDiscreteValue(FString InValue, EPropertyChangeReason Reason)
{
	Setter->SetValue(Source, InValue);
	NotifyPropertyChanged(Reason);
}
