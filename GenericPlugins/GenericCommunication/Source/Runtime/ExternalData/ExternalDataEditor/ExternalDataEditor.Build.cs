using UnrealBuildTool;

public class ExternalDataEditor : ModuleRules
{
	public ExternalDataEditor(ReadOnlyTargetRules Target) : base(Target)
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

				"UnrealEd",
				"AssetTools",
				"ExternalData"
			}
		);
	}
}