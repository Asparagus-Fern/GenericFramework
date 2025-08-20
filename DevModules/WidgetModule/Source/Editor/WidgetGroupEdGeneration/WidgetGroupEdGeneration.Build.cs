using UnrealBuildTool;

public class WidgetGroupEdGeneration : ModuleRules
{
	public WidgetGroupEdGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",
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
				"BlueprintGraph",
				"Kismet",
				"InputCore",
				"AssetDefinition",
				"GameplayTags",
				"PropertyEditor",
				"StructUtilsEditor",

				"WidgetGroupGeneration"
			}
		);
	}
}