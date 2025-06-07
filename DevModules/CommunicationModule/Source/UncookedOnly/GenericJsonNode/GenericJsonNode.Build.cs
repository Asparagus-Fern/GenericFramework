using UnrealBuildTool;

public class GenericJsonNode : ModuleRules
{
	public GenericJsonNode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"UnrealEd",
				"BlueprintGraph",
				"GraphEditor",

				"GenericJson",
			}
		);
	}
}