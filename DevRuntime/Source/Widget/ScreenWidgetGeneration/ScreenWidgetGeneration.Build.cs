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
				"DevSlateCore",
				"CommonUI",
				"DBTween",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"DeveloperSettings",
				"UMG",
				"GameplayTags"
			}
		);
	}
}