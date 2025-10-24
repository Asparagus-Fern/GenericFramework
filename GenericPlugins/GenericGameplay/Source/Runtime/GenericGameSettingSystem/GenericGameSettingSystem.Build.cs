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
				"UnrealMisc",
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

				"PropertySystem",
				"GenericGameplaySystem",
				"WidgetGeneration",
				"WidgetGroupGeneration",
				"WidgetApplication",
				"WindowGeneration",
			}
		);
		
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}