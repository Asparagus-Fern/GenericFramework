using UnrealBuildTool;

public class TeamAllocationSystem : ModuleRules
{
	public TeamAllocationSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"GameplayTags",
				"UMG",
				"InputCore",
				"CommonUI",

				"GenericGameplaySystem",
				"WidgetGeneration",
			}
		);
	}
}