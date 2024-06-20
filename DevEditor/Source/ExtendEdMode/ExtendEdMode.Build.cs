using UnrealBuildTool;

public class ExtendEdMode : ModuleRules
{
	public ExtendEdMode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevEdCore",
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
				"EditorFramework",
				"InteractiveToolsFramework",
				"EditorInteractiveToolsFramework",
				"ToolWidgets",
				"ZoneGraph",
			}
		);
	}
}