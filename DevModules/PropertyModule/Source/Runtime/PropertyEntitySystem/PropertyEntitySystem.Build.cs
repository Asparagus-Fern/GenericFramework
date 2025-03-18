using UnrealBuildTool;

public class PropertyEntitySystem : ModuleRules
{
	public PropertyEntitySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore"
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
				"PropertyPath",
				"GameplayTags",
			}
		);
	}
}