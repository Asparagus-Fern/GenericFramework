using UnrealBuildTool;

public class MediaSystem : ModuleRules
{
	public MediaSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"MediaAssets",
				"ElectraPlayerPlugin",
				
				"EventUtilities",
				"MovieSceneUtilities"
			}
		);
	}
}