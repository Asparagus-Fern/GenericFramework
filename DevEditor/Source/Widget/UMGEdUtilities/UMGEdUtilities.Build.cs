using UnrealBuildTool;

public class UMGEdUtilities : ModuleRules
{
	public UMGEdUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"DevEdCore",
				"DevSlateCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"InputCore",
				"BlueprintGraph",
				"KismetCompiler",
				"GraphEditor",
				"UnrealEd",
				"Kismet",
				"ToolMenus",
				"EditorStyle",
				"DeveloperSettings",

				"UMGUtilities",
			}
		);
	}
}