using UnrealBuildTool;

public class PropertyViewModelSystem : ModuleRules
{
	public PropertyViewModelSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"FieldNotification",
				"ModelViewViewModel",

				"PropertyUtilities",
				"WidgetGeneration"
			}
		);
	}
}