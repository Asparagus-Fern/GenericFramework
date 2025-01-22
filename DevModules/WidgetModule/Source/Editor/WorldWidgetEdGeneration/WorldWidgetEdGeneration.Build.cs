using UnrealBuildTool;

public class WorldWidgetEdGeneration : ModuleRules
{
	public WorldWidgetEdGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"DevEdCore",
				"DeveloperSettings"
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
				"LevelEditor",
				"UnrealEd",
				"InputCore",

				"WidgetGeneration",
				"WorldWidgetGeneration",
			}
		);
	}
}