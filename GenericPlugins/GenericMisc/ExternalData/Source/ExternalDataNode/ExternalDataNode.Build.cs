// Copyright ChenTaiye 2025,. All Rights Reserved.

using UnrealBuildTool;

public class ExternalDataNode : ModuleRules
{
	public ExternalDataNode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"ExternalData",
				"BlueprintGraph",
			}
		);
	}
}