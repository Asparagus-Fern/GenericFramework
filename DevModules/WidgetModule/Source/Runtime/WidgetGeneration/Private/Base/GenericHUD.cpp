#include "Base/GenericHUD.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif

#if WITH_EDITOR
void UGenericHUD::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!HUDTag.IsValid())
	{
		CompileLog.Error(FText::FromString(TEXT("HUD Tag Is InValid")));
	}
}

#endif
