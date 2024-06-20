#include "StaticFunctions/StaticFunctions_Test.h"

void FStaticFunctions_Test::OpenTestPanelWindow(TSharedRef<SWidget> InWidget)
{
	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.SizingRule(ESizingRule::UserSized)
		.ClientSize(FVector2D(1920.f, 360.f))
		.ScreenPosition(FVector2D(-2000.f, 700.f))
		.IsTopmostWindow(false)
		.FocusWhenFirstShown(true)
		.AutoCenter(EAutoCenter::None);

	NewWindow->SetContent
	(
		SNew(SBorder)
		.Padding(2.f)
		[
			InWidget
		]
	);

	FSlateApplication::Get().AddWindow(NewWindow);
}
