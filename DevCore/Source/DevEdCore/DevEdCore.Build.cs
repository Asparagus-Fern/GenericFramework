using UnrealBuildTool;

public class DevEdCore : ModuleRules
{
	public DevEdCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;
		bUsePrecompiled = false;

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

				"EditorSubsystem",
				"UnrealEd",
				"ToolMenus",
				"Blutility",
				"LevelEditor",
				"AssetTools",
				"ClassViewer",
				"Settings",
				"SettingsEditor",
				"GraphEditor",
				"BlueprintGraph",
				"SubobjectEditor",
				"AssetDefinition",
				"InputCore",
				"DeveloperSettings",
				"GameplayTags"
			}
		);
	}
}