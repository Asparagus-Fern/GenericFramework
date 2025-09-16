using UnrealBuildTool;

public class ExtendEdMode : ModuleRules
{
	public ExtendEdMode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
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
				"UnrealEd",
				"EditorFramework",
				"InteractiveToolsFramework",
				"EditorInteractiveToolsFramework",
				"ToolWidgets",
				"ZoneGraph"
			}
		);
	}
}