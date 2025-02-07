using UnrealBuildTool;

public class MenuGenerationEditor : ModuleRules
{
	public MenuGenerationEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"DevCore",
				"DevEdCore",
				"MenuGeneration",
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
				"BlueprintGraph",
				"Kismet",
				"InputCore",
				"AssetDefinition",
				"GameplayTags",
				"PropertyEditor",
				"StructUtilsEditor",
			}
		);
	}
}