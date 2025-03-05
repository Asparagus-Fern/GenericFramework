using UnrealBuildTool;

public class PropertyNode : ModuleRules
{
	public PropertyNode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"Blutility",
				"UnrealEd",
				"GraphEditor",
				"BlueprintGraph",
				"KismetCompiler",
				"ToolMenus"
			}
		);
	}
}