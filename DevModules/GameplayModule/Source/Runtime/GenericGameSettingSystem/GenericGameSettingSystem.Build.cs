using UnrealBuildTool;

public class GenericGameSettingSystem : ModuleRules
{
	public GenericGameSettingSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"ModelViewViewModel",
				"WidgetGeneration",
				"WidgetGroupGeneration",
				"WidgetApplication",
				"PropertySystem",
			}
		);
	}
}