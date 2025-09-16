using UnrealBuildTool;

public class DocumentReader : ModuleRules
{
	public DocumentReader(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"DevSlateCore",
				"DevEdCore"
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
				"ToolMenus"
			}
		);
	}
}