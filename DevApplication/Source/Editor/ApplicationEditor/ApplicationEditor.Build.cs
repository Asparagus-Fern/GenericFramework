using UnrealBuildTool;

public class ApplicationEditor : ModuleRules
{
	public ApplicationEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"DevSlateCore",
				"DevEdCore",
				"DevCore",
				"ApplicationRuntime"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"UnrealEd",
				"EditorSubsystem",
				"ToolMenus",
				"Settings",
				"SettingsEditor",
				"InternationalizationSettings",
				"PropertyEditor",
			}
		);
	}
}