#pragma once

#include "CoreMinimal.h"

#include "Styling/SlateStyle.h"

class DEVSLATECORE_API FDevCoreStyle
{
public:
	static void Initialize();
	static void ShoutDown();
	static const ISlateStyle& Get() { return *Instance.Get(); }
	static FName GetStyleSetName() { return StyleSetName; }

public:
	class FStyle : public FSlateStyleSet
	{
	public:
		FStyle();
		virtual ~FStyle() override;
		void Initialize();
	};

	static TSharedRef<class FDevCoreStyle::FStyle> Create();

private:
	static TSharedPtr<class ISlateStyle> Instance;
	static FName StyleSetName;
};
