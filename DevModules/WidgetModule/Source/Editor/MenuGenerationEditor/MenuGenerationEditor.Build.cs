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

				"AssetDefinition",
				"EngineAssetDefinitions",

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
				"Kismet"
			}
		);
	}
}