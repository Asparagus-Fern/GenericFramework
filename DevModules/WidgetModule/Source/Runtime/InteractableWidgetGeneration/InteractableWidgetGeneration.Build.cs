using UnrealBuildTool;

public class InteractableWidgetGeneration : ModuleRules
{
	public InteractableWidgetGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"UMG",
				"CommonInput",
				"EnhancedInput",
				"InputCore",
				"CommonUI",
				"GameplayTags",

				"DevCore",
				"DevSlateCore",
				"WidgetGeneration",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);
	}
}