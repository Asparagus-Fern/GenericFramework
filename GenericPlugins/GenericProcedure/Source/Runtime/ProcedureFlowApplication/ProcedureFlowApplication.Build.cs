using UnrealBuildTool;

public class ProcedureFlowApplication : ModuleRules
{
	public ProcedureFlowApplication(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"UnrealMisc",
				"GenericCameraSystem",
				"ProcedureFlowSystem",
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
				"LevelStreaming",
				"UMG",
			}
		);
	}
}