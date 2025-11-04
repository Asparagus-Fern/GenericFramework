// Copyright ChenTaiye 2025. All Rights Reserved.

using UnrealBuildTool;

public class DevCore : ModuleRules
{
	public DevCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseSharedPCHs;
		SharedPCHHeaderFile = "Public/SharedPCHHeader.h";	
		PrivatePCHHeaderFile = "Public/PrivatePCHHeader.h";
		
		PrecompileForTargets = PrecompileTargetsType.Any;
		bUsePrecompiled = false;

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc", 
				// ... add other public dependencies that you statically link with here ...
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
				"DeveloperSettings",
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd"
				}
			);
		}

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add("pdh.lib");
			PublicAdditionalLibraries.Add("kernel32.lib");
		}
	}
}