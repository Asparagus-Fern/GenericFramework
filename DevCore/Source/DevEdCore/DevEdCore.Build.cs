using UnrealBuildTool;

public class DevEdCore : ModuleRules
{
	public DevEdCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
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
				"EditorSubsystem",
				"UnrealEd",
				"ToolMenus",
				"Blutility",
				"UnrealEd",
				"LevelEditor",
				"AssetTools",
				"ClassViewer"
			}
		);
	}
}