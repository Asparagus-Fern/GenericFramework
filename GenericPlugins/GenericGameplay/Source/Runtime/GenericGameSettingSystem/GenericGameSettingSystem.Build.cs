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
				"UnrealMisc",
				"DevCore",
				"PropertySystem",
				"GenericGameplaySystem",
				"WidgetGeneration",
				"WidgetGroupGeneration",
				"WidgetApplication",
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
				"ModelViewViewModel",
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}