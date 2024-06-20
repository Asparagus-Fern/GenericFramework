#include "DevEdCoreStyle.h"

#include "StaticFunctions/StaticFunctions_Plugin.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

using namespace CoreStyleConstants;

FName FDevEdCoreStyle::StyleSetName = TEXT("DevEdCoreStyle");
TSharedPtr<ISlateStyle> FDevEdCoreStyle::Instance = nullptr;


void FDevEdCoreStyle::Initialize()
{
	FSlateApplication::InitializeCoreStyle();

	if (!Instance)
	{
		Instance = Create();
	}
	FSlateStyleRegistry::RegisterSlateStyle(*Instance.Get());
}


void FDevEdCoreStyle::ShoutDown()
{
	if (Instance)
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*Instance.Get());
		Instance.Reset();
	}
}


FDevEdCoreStyle::FStyle::FStyle()
	: FSlateStyleSet(FDevEdCoreStyle::StyleSetName)
{
}


FDevEdCoreStyle::FStyle::~FStyle()
{
}


void FDevEdCoreStyle::FStyle::Initialize()
{
	SetContentRoot(FStaticFunctions_Plugin::GetPluginResourcesDir("DevCore"));
	SetParentStyleName("CoreStyle");

	Set("Manager.ToolbarButton", new IMAGE_BRUSH_SVG("Icons/Manager", Icon20x20));
	Set("Manager.ToolbarButton.Small", new IMAGE_BRUSH_SVG("Icons/Manager", Icon16x16));
}


TSharedRef<FDevEdCoreStyle::FStyle> FDevEdCoreStyle::Create()
{
	TSharedRef<class FDevEdCoreStyle::FStyle> NewStyle = MakeShareable(new FDevEdCoreStyle::FStyle());
	NewStyle->Initialize();
	return NewStyle;
}
