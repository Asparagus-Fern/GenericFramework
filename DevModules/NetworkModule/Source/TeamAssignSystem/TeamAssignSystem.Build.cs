using UnrealBuildTool;

public class TeamAssignSystem : ModuleRules
{
	public TeamAssignSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"CommonUI",
				"ModelViewViewModel",

				"UnrealMisc",
				"GenericGameplaySystem",
				"WidgetGeneration"
			}
		);
	}
}