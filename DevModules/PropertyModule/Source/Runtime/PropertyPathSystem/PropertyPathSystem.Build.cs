using UnrealBuildTool;

public class PropertyPathSystem : ModuleRules
{
	public PropertyPathSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"DevCore",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"UMG",
				"PropertyPath",
				"CommonUI",
				"InputCore",
				"GameplayTags",

				"WidgetGeneration",
			}
		);
	}
}