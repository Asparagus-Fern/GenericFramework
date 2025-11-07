// Copyright ChenTaiye 2025,. All Rights Reserved.

using UnrealBuildTool;

public class ExternalData : ModuleRules
{
	public ExternalData(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"GenericJson",
				// ... add other public dependencies that you statically link with here ...
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
				// ... add private dependencies that you statically link with here ...	
			});

		RuntimeDependencies.Add("$(ProjectDir)/Config/ExternalData/...*json", StagedFileType.NonUFS);
	}
}