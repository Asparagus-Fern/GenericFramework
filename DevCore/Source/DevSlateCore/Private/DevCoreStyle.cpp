#include "DevCoreStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

using namespace CoreStyleConstants;

FName FDevCoreStyle::StyleSetName = TEXT("DevEdCoreStyle");
TSharedPtr<ISlateStyle> FDevCoreStyle::Instance = nullptr;


void FDevCoreStyle::Initialize()
{
	FSlateApplication::InitializeCoreStyle();

	if (!Instance)
	{
		Instance = Create();
	}
	FSlateStyleRegistry::RegisterSlateStyle(*Instance.Get());
}


void FDevCoreStyle::ShoutDown()
{
	if (Instance)
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*Instance.Get());
		Instance.Reset();
	}
}


FDevCoreStyle::FStyle::FStyle()
	: FSlateStyleSet(FDevCoreStyle::StyleSetName)
{
}


FDevCoreStyle::FStyle::~FStyle()
{
}


void FDevCoreStyle::FStyle::Initialize()
{
	const TSharedPtr<IPlugin> DevCorePlugin = IPluginManager::Get().FindPlugin("DevCore");
	if (DevCorePlugin.IsValid())
	{
		SetContentRoot(DevCorePlugin->GetBaseDir() + "/Resources");
	}

	SetParentStyleName("CoreStyle");

	Set("Manager.ToolbarButton", new IMAGE_BRUSH_SVG("Icons/Manager", Icon20x20));
	Set("Manager.ToolbarButton.Small", new IMAGE_BRUSH_SVG("Icons/Manager", Icon16x16));
}


TSharedRef<FDevCoreStyle::FStyle> FDevCoreStyle::Create()
{
	TSharedRef<class FDevCoreStyle::FStyle> NewStyle = MakeShareable(new FDevCoreStyle::FStyle());
	NewStyle->Initialize();
	return NewStyle;
}
