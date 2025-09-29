using UnrealBuildTool;

public class WidgetApplication : ModuleRules
{
	public WidgetApplication(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"DevSlateCore",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"GameplayTags",
				"CommonUI",
				"InputCore",
				"DeveloperSettings",
				"ModelViewViewModel",

				"WidgetGeneration",
				"WidgetGroupGeneration",
				"WorldWidgetGeneration",
			}
		);
	}
}