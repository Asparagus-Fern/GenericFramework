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
				"GenericCameraSystem",
				"ProcedureFlowSystem",
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
			}
		);
	}
}