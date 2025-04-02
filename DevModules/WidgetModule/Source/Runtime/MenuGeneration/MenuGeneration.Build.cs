using UnrealBuildTool;

public class MenuGeneration : ModuleRules
{
	public MenuGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"GameplayTags",
				"UMG",
				"CommonUI",
				"CommonInput",
				"EnhancedInput",
				"InputCore",

				"DevSlateCore",
				"DevCore",
				"WidgetGeneration",
				"GameHUDModule",
				"InteractableWidgetGeneration",
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