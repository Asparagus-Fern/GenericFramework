using UnrealBuildTool;

public class ApplicationRuntime : ModuleRules
{
	public ApplicationRuntime(ReadOnlyTargetRules Target) : base(Target)
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

				/* Unreal Engine */
				"ModularGameplay",
				"GameplayTags",
				"UMG",
				"LevelSequence",
				"MovieScene",
				"MediaAssets",

				/* Dev Misc */
				"UnrealMisc",

				/* Dev Module */
				"CameraSystem",
				"GenericJson",
				"GenericProtocol",
				"EventUtilities",
				"DevGameplay",
				"PlayerInputUtilities",
				"ExternalData",
				"NativeAPI",
				"MovieSceneUtilities",
				"LevelSequenceSystem",
				"MediaSystem",
				"TeamAssignSystem",
				"ProcedureFlowSystem",
				"PropertyUtilities",
				"GenericThreadSystem",
				"ExtraProc",
				"WidgetGeneration",
				"InteractableWidgetGeneration",
				"GameHUDModule",
				"WorldWidgetGeneration",
				"MenuGeneration",
				"WidgetApplicationModule",
				"WorldUtilities",
				"LevelStreaming",
				"WorldPartition",

				/* Marketplace */
				"DBTween",
				"UltraDynamicSkyUtilities",
			}
		);
	}
}