using UnrealBuildTool;

public class ScreenWidgetGeneration : ModuleRules
{
	public ScreenWidgetGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",

				"UMG",
				"CommonUI",
				"GameplayTags",
				"SlateWidgetGeneration"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"ActiveNodeSystem"
			}
		);
	}
}