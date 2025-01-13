using UnrealBuildTool;

public class WidgetApplicationModule : ModuleRules
{
	public WidgetApplicationModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"DevCore",
				"DevSlateCore",
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
				"InputCore",
				"CommonUI",

				"GameHUDModule",
				"WidgetGeneration",
				"InteractableWidgetGeneration",
				"WorldWidgetGeneration",
				"MenuGeneration"
			}
		);
	}
}