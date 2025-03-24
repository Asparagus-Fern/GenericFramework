#include "DevCoreStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyle.h"
#include "Styling/CoreStyle.h"
#include "Framework/Application/SlateApplication.h"

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

	Set("Developer.DeveloperSetting", new IMAGE_BRUSH_SVG("Icons/DeveloperSetting", Icon20x20));
	Set("Developer.DeveloperSetting.Small", new IMAGE_BRUSH_SVG("Icons/DeveloperSetting", Icon16x16));

	Set("Developer.FastSwitchLanguage", new IMAGE_BRUSH_SVG("Icons/FastSwitchLanguage", Icon20x20));
	Set("Developer.FastSwitchLanguage.Small", new IMAGE_BRUSH_SVG("Icons/FastSwitchLanguage", Icon16x16));

	Set("Developer.ReadMe", new IMAGE_BRUSH_SVG("Icons/ReadMe", Icon20x20));
	Set("Developer.ReadMe.Small", new IMAGE_BRUSH_SVG("Icons/ReadMe", Icon16x16));
}


TSharedRef<FDevCoreStyle::FStyle> FDevCoreStyle::Create()
{
	TSharedRef<class FDevCoreStyle::FStyle> NewStyle = MakeShareable(new FDevCoreStyle::FStyle());
	NewStyle->Initialize();
	return NewStyle;
}
