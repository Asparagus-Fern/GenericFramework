#pragma once


class DEVEDCORE_API FUECommandDoc : public TCommands<FUECommandDoc>
{
public:
	FUECommandDoc()
		: TCommands<FUECommandDoc>(
			"",
			FText(),
			NAME_None,
			NAME_None
		)
	{
	}

	virtual void RegisterCommands() override
	{
#pragma region Source/Runtime
		/**
		FGenericCommands：
		UI_COMMAND(Cut, "Cut", "Cut selection", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::X))
		UI_COMMAND(Copy, "Copy", "Copy selection", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::C))
		UI_COMMAND(Paste, "Paste", "Paste clipboard contents", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::V))

		UI_COMMAND(Duplicate, "Duplicate", "Duplicate selection", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Command, EKeys::D))

		UI_COMMAND(Duplicate, "Duplicate", "Duplicate selection", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::D))

		UI_COMMAND(Undo, "Undo", "Undo last action", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Z))
		UI_COMMAND(Redo, "Redo", "Redo last action", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Y))

		UI_COMMAND(Delete, "Delete", "Delete current selection", EUserInterfaceActionType::Button, FInputChord(EKeys::Delete), FInputChord(EKeys::BackSpace))

		UI_COMMAND(Rename, "Rename", "Rename current selection", EUserInterfaceActionType::Button, FInputChord(EKeys::F2))
		UI_COMMAND(SelectAll, "Select All", "Select everything in the current scope", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::A))
		*/

		/**
		FTabCommands：
		UI_COMMAND(CloseMajorTab, "Close Major Tab", "Closes the focused major tab", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::W))
		UI_COMMAND(CloseMinorTab, "Close Minor Tab", "Closes the current window's active minor tab", EUserInterfaceActionType::Button, FInputChord())
		*/

		/**
		FMacMenuCommands：
		UI_COMMAND( Preferences, "Preferences...", "Preferences", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control, EKeys::Comma ) )
		UI_COMMAND( Help, "Help", "Help", EUserInterfaceActionType::None, FInputChord( EModifierKey::None, EKeys::F1 ) )
		UI_COMMAND( Hide, "Hide", "Hide", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control, EKeys::H ) )
		UI_COMMAND( HideOthers, "Hide Others", "Hide Others", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control | EModifierKey::Alt, EKeys::H ) )
		UI_COMMAND( ShowAll, "Show All", "Show All", EUserInterfaceActionType::None, FInputChord() )
		UI_COMMAND( Minimize, "Minimize", "Minimize", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control, EKeys::M ) )
		UI_COMMAND( Close, "Close", "Close", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control, EKeys::W ) )
		UI_COMMAND( About, "About", "About", EUserInterfaceActionType::None, FInputChord( FInputChord() ) )
		UI_COMMAND( Quit, "Quit", "Quit", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control, EKeys::Q ) )		
		UI_COMMAND( Zoom, "Zoom", "Zoom", EUserInterfaceActionType::None, FInputChord() )	
		UI_COMMAND( ToggleFullScreen, "Enter Full Screen", "Enter Full Screen", EUserInterfaceActionType::None, FInputChord( EModifierKey::Control | EModifierKey::Command, EKeys::F ) )
		UI_COMMAND( BringAllToFront, "Bring All to Front", "Bring All to Front", EUserInterfaceActionType::None, FInputChord() )
		*/

		/**
		FMultiBoxTestCommandList：
		UI_COMMAND( FirstCommandInfo, "First Test", "This is the first test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SecondCommandInfo, "Second Test", "This is the second test menu item. Shows a keybinding", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Shift, EKeys::A ) );
		UI_COMMAND( ThirdCommandInfo, "Third Test", "This is the thrid test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( FourthCommandInfo, "Fourth Test", "This is the fourth test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( FifthCommandInfo, "Fifth Test", "This is the fifth test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SixthCommandInfo, "Sixth Test", "This is the sixth test menu item. Shows a keybinding", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SeventhCommandInfo, "Seventh Test", "This is the seventh test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( EighthCommandInfo, "Eighth Test", "This is the eighth test menu item", EUserInterfaceActionType::ToggleButton, FInputChord() );
		*/
#pragma endregion

#pragma region Source/Editor
		/**
		FAdvancedPreviewSceneCommands：
		UI_COMMAND(ToggleEnvironment, "Toggle Environment", "Toggles Environment visibility", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::I));
		UI_COMMAND(ToggleFloor, "Toggle Floor", "Toggles floor visibility", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::O));
		UI_COMMAND(TogglePostProcessing, "Toggle Post Processing", "Toggles whether Post Processing is enabled", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::P));
		*/

		/**
		FAnimGraphCommands：
		UI_COMMAND(TogglePoseWatch, "Toggle Pose Watch", "Toggle pose watching on this node", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(HideUnboundPropertyPins, "Hide Unbound/Unset Property Pins", "Unexpose all unbound/unset property pins from this node", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( SelectBone, "Select Bone", "Assign or change the bone for skeletal controls", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( AddBlendListPin, "Add Blend Pin", "Add blend pin to blend list", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( RemoveBlendListPin, "Remove Blend Pin", "Remove blend pin", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( ConvertToSeqEvaluator, "Convert to Single Frame Animation", "Convert to one frame animation that requires position", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ConvertToSeqPlayer, "Convert to Sequence Player", "Convert back to sequence player without manual position set up", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( ConvertToBSEvaluator, "Convert to Single Frame Blend Space Player", "Convert to one frame blend space player that requires position", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ConvertToBSPlayer, "Convert to Blend Space Player", "Convert back to blend space player without manual position set up", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ConvertToBSGraph, "Convert to Blend Space Graph", "Convert to blend space graph", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( ConvertToAimOffsetLookAt, "Convert to LookAt AimOffset", "Convert to one AimOffset that automatically tracks a Target", EUserInterfaceActionType::Button, FInputChord())
		UI_COMMAND( ConvertToAimOffsetSimple, "Convert to simple AimOffset", "Convert to a manual AimOffset", EUserInterfaceActionType::Button, FInputChord())
		UI_COMMAND( ConvertToAimOffsetGraph, "Convert to AimOffset Graph", "Convert to an AimOffset graph", EUserInterfaceActionType::Button, FInputChord())

		UI_COMMAND(ConvertToPoseBlender, "Convert to Pose Blender", "Convert to pose blender that can blend by source curves", EUserInterfaceActionType::Button, FInputChord())
		UI_COMMAND(ConvertToPoseByName, "Convert to Pose By Name", "Convert to pose node that returns by name", EUserInterfaceActionType::Button, FInputChord())

		UI_COMMAND( OpenRelatedAsset, "Open Asset", "Opens the asset related to this node", EUserInterfaceActionType::Button, FInputChord() )
		*/

		/**
		FAnimationEditorCommands：
		UI_COMMAND(ImportAnimation, "Import Animation", "Import new animation for the skeleton.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportAnimation, "Reimport Animation", "Reimport current animation.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ApplyCompression, "Apply Compression", "Apply compression to current animation", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportToFBX_AnimData, "Animation Data", "Export current animation source data to FBX", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportToFBX_PreviewMesh, "Preview Mesh", "Export current animation by playing on the current preview mesh, including retargeting, post process graph, or anything you see on the preview mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddLoopingInterpolation, "Add Looping Interpolation", "Add an extra first frame at the end of the animation to create interpolation when looping", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetKey, "Set Key", "Add Bone Transform to Additive Layer Tracks", EUserInterfaceActionType::Button, FInputChord(EKeys::S));	
		UI_COMMAND(RemoveBoneTracks, "Remove All Bone Tracks", "Remove all bone tracks. This doesn't remove notifies or curves.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FSoundClassEditorCommands：
		UI_COMMAND(ToggleSolo, "Solo", "Toggles Soloing this sound class", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::S));
		UI_COMMAND(ToggleMute, "Mute", "Toggles Muting this sound class", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::M));	
		*/

		/**
		FSoundCueGraphEditorCommands：
		UI_COMMAND(PlayCue, "Play Cue", "Plays the SoundCue", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PlayNode, "Play Node", "Plays the currently selected node", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(StopCueNode, "Stop", "Stops the currently playing cue/node", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(TogglePlayback, "Toggle Playback", "Plays the SoundCue or stops the currently playing cue/node", EUserInterfaceActionType::Button, FInputChord(EKeys::SpaceBar));

		UI_COMMAND(BrowserSync, "Sync to Browser", "Selects the SoundWave in the content browser", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddInput, "Add Input", "Adds an input to the node", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteInput, "Delete Input", "Removes an input from the node", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(ToggleSolo, "Solo", "Toggles Soloing this cue", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::S));
		UI_COMMAND(ToggleMute, "Mute", "Toggles Muting this cue", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::M));
		*/

		/**
		FBTCommonCommands：
		UI_COMMAND(SearchBT, "Search", "Search this Behavior Tree.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F));
		UI_COMMAND(NewBlackboard, "New Blackboard", "Create a new Blackboard Data Asset", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FBTDebuggerCommands：
		UI_COMMAND(BackInto, "Back: Into", "Show state from previous step, can go into subtrees", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(BackOver, "Back: Over", "Show state from previous step, don't go into subtrees", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ForwardInto, "Forward: Into", "Show state from next step, can go into subtrees", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ForwardOver, "Forward: Over", "Show state from next step, don't go into subtrees", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(StepOut, "Step Out", "Show state from next step, leave current subtree", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(PausePlaySession, "Pause", "Pause simulation", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ResumePlaySession, "Resume", "Resume simulation", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND(StopPlaySession, "Stop", "Stop simulation", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(CurrentValues, "Current", "View current values", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SavedValues, "Saved", "View saved values", EUserInterfaceActionType::RadioButton, FInputChord());
		*/

		/**
		FDiffListCommands：
		UI_COMMAND(Previous, "Prev", "Go to previous difference", EUserInterfaceActionType::Button, FInputChord(EKeys::F7, EModifierKey::Control));
		UI_COMMAND(Next, "Next", "Go to next difference", EUserInterfaceActionType::Button, FInputChord(EKeys::F7));
		*/

		/**
		FCascadeCommands：
		UI_COMMAND(RestartSimulation, "Restart Sim", "Restart Simulation", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RestartInLevel, "Restart Level", "Restart in Level", EUserInterfaceActionType::Button, FInputChord(EKeys::SpaceBar));
		UI_COMMAND(SaveThumbnailImage, "Thumbnail", "Generate Thumbnail", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CascadePlay, "Play/Pause", "Play/Pause Simulation", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(AnimSpeed_100, "100%", "100% Speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AnimSpeed_50, "50%", "50% Speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AnimSpeed_25, "25%", "25% Speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AnimSpeed_10, "10%", "10% Speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AnimSpeed_1, "1%", "1% Speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(RegenerateLowestLODDuplicatingHighest, "Regen LOD", "Regenerate Lowest LOD, Duplicating Highest", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RegenerateLowestLOD, "Regen LOD", "Regenerate Lowest LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(JumpToHighestLOD, "Highest LOD", "Select Highest LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(JumpToHigherLOD, "Higher LOD", "Select Higher LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddLODAfterCurrent, "Add LOD", "Add LOD After Current", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddLODBeforeCurrent, "Add LOD", "Add LOD Before Current", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(JumpToLowerLOD, "Lower LOD", "Select Lower LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(JumpToLowestLOD, "Lowest LOD", "Select Lowest LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteLOD, "Delete LOD", "Delete Selected LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(JumpToLOD0, "Jump To LOD0", "LOD0", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::M));
		UI_COMMAND(JumpToLOD1, "Jump To LOD1", "LOD1", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Comma));
		UI_COMMAND(JumpToLOD2, "Jump To LOD2", "LOD2", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Period));
		UI_COMMAND(JumpToLOD3, "Jump To LOD3", "LOD3", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Slash));

		UI_COMMAND(ToggleOriginAxis, "Origin Axis", "Display Origin Axis", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(View_ParticleCounts, "Particle Counts", "Display Particle Counts", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(View_ParticleEventCounts, "Particle Event Counts", "Display Particle Event Counts", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(View_ParticleTimes, "Particle Times", "Display Particle Times", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(View_ParticleMemory, "Particle Memory", "Display Particle Memory", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(View_SystemCompleted, "System Completed", "Display 'Completed' when the particle system has finished playing and has not been reset (only for non-looping systems)", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(View_EmitterTickTimes, "Emitter Tick Times", "Show the tick duration for each emitter", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewMode_Wireframe, "Wireframe", "Select Wireframe Render Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewMode_Unlit, "Unlit", "Select Unlit Render Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewMode_Lit, "Lit", "Select Lit Render Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewMode_ShaderComplexity, "Shader Complexity", "Select Shader Complexity Render Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DetailMode_Low, "Low", "Select Low Detail Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DetailMode_Medium, "Medium", "Select Medium Detail Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DetailMode_High, "High", "Select High Detail Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DetailMode_Epic, "Epic", "Select Epic Detail Mode", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(Significance_Critical, "Critical", "Require >= Critical Significance", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(Significance_High, "High", "Require High >= Significance", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(Significance_Medium, "Medium", "Require >= Medium Significance", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(Significance_Low, "Low", "Require >= Low Significance", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ToggleGeometry, "Geometry", "Display preview mesh", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleGeometry_Properties, "Geometry Properties", "Display Preview Mesh Properties", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ToggleLocalVectorFields, "Vector Fields", "Display Local Vector Fields", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleOrbitMode, "Orbit Mode", "Toggle Orbit Mode", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleMotion, "Motion", "Toggle Motion", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetMotionRadius, "Motion Radius", "Set Motion Radius", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ToggleBounds, "Bounds", "Display Bounds", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleBounds_SetFixedBounds, "Set Fixed Bounds", "Set Fixed Bounds", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(TogglePostProcess, "Post Process", "Toggle Post Process", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleGrid, "Grid", "Display Grid", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleLoopSystem, "Loop", "Toggle Looping", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleRealtime, "Realtime", "Toggles real time rendering in this viewport", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(CascadeBackgroundColor, "Background Color", "Change Background Color", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ToggleWireframeSphere, "Wireframe Sphere", "Display Wireframe Sphere", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(DeleteModule, "Delete Module", "Delete Module", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RefreshModule, "Refresh Module", "Refresh Module", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SyncMaterial, "Sync Material", "Sync Material", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(UseMaterial, "Use Material", "Use Material", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DupeFromHigher, "Duplicate From Higher", "Duplicate From Higher LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ShareFromHigher, "Share From Higher", "Share From Higher LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DupeFromHighest, "Duplicate From Highest", "Duplicate From Second Highest LOD", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetRandomSeed, "Set Random Seed", "Set Random Seed", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertToSeeded, "Convert To Seeded", "Convert To Seeded Module", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RenameEmitter, "Rename Emitter", "Rename Emitter", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DuplicateEmitter, "Duplicate Emitter", "Duplicate Emitter", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DuplicateShareEmitter, "Duplicate and Share Emitter", "Duplicate and Share Emitter", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteEmitter, "Delete Emitter", "Delete Emitter", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportEmitter, "Export Emitter", "Export Emitter", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportAllEmitters, "Export All", "Export All Emitters", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectParticleSystem, "Select Particle System", "Select Particle System", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(NewEmitterBefore, "Add New Emitter Before", "Add New Emitter Before Selected", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(NewEmitterAfter, "Add New Emitter After", "Add New Emitter After Selected", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveDuplicateModules, "Remove Duplicate Modules", "Remove Duplicate Modules", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FClothPaintToolCommands_Gradient：
		UI_COMMAND(ApplyGradient, "Apply gradient", "Apply the gradient when the clothing paint gradient tool is active.", EUserInterfaceActionType::Button, FInputChord(EKeys::Enter));
		*/

		/**
		FClothPainterCommands：
		UI_COMMAND(TogglePaintMode, "Enable Cloth Paint", "Toggles between selection and clothing paint modes.", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		FClothingAssetListCommands：
		UI_COMMAND(DeleteAsset, "Delete Asset", "Deletes a clothing asset from the mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RebuildAssetParams, "Rebuild Asset Parameter Masks", "Takes the parameter masks in LOD0 and creates masks in all lower LODs to match, casting those parameter masks to the new mesh.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FSplineComponentVisualizerCommands：
		UI_COMMAND(DeleteKey, "Delete Spline Point", "Delete the currently selected spline point.", EUserInterfaceActionType::Button, FInputChord(EKeys::Delete));
		UI_COMMAND(DuplicateKey, "Duplicate Spline Point", "Duplicate the currently selected spline point.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddKey, "Add Spline Point Here", "Add a new spline point at the cursor location.", EUserInterfaceActionType::Button, FInputChord(EKeys::A));
		UI_COMMAND(SelectAll, "Select All Spline Points", "Select all spline points.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectNextSplinePoint, "Select Next Spline Point", "Select next spline point.", EUserInterfaceActionType::Button, FInputChord(EKeys::Period));
		UI_COMMAND(SelectPrevSplinePoint, "Select Prev Spline Point", "Select prev spline point.", EUserInterfaceActionType::Button, FInputChord(EKeys::Comma));
		UI_COMMAND(AddNextSplinePoint, "Add Next Spline Point", "Add next spline point.", EUserInterfaceActionType::Button, FInputChord(EKeys::Period, EModifierKey::Shift));
		UI_COMMAND(AddPrevSplinePoint, "Add Prev Spline Point", "Add prev spline point.", EUserInterfaceActionType::Button, FInputChord(EKeys::Comma, EModifierKey::Shift));
		UI_COMMAND(ResetToUnclampedTangent, "Unclamped Tangent", "Reset the tangent for this spline point to its default unclamped value.", EUserInterfaceActionType::Button, FInputChord(EKeys::T));
		UI_COMMAND(ResetToClampedTangent, "Clamped Tangent", "Reset the tangent for this spline point to its default clamped value.", EUserInterfaceActionType::Button, FInputChord(EKeys::T, EModifierKey::Shift));
		UI_COMMAND(SetKeyToCurve, "Curve", "Set spline point to Curve type", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetKeyToLinear, "Linear", "Set spline point to Linear type", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetKeyToConstant, "Constant", "Set spline point to Constant type", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(FocusViewportToSelection, "Focus Selected", "Moves the camera in front of the selection", EUserInterfaceActionType::Button, FInputChord(EKeys::F));
		UI_COMMAND(SnapKeyToNearestSplinePoint, "Snap to Nearest Spline Point", "Snap selected spline point to nearest non-adjacent spline point on current or nearby spline.", EUserInterfaceActionType::Button, FInputChord(EKeys::P, EModifierKey::Shift));
		UI_COMMAND(AlignKeyToNearestSplinePoint, "Align to Nearest Spline Point", "Align selected spline point to nearest non-adjacent spline point on current or nearby spline.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AlignKeyPerpendicularToNearestSplinePoint, "Align Perpendicular to Nearest Spline Point", "Align perpendicular selected spline point to nearest non-adjacent spline point on current or nearby spline.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapKeyToActor, "Snap to Actor", "Snap selected spline point to actor, Ctrl-LMB to select the actor after choosing this option.", EUserInterfaceActionType::Button, FInputChord(EKeys::P, (EModifierKey::Alt | EModifierKey::Shift)));
		UI_COMMAND(AlignKeyToActor, "Align to Actor", "Align selected spline point to actor, Ctrl-LMB to select the actor after choosing this option.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AlignKeyPerpendicularToActor, "Align Perpendicular to Actor", "Align perpendicular  selected spline point to actor, Ctrl-LMB to select the actor after choosing this option.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapAllToSelectedX, "Snap All To Selected X", "Snap all spline points to selected spline point world X position.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapAllToSelectedY, "Snap All To Selected Y", "Snap all spline points to selected spline point world Y position.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapAllToSelectedZ, "Snap All To Selected Z", "Snap all spline points to selected spline point world Z position.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapToLastSelectedX, "Snap To Last Selected X", "Snap selected spline points to world X position of last selected spline point.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapToLastSelectedY, "Snap To Last Selected Y", "Snap selected spline points to world Y position of last selected spline point.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapToLastSelectedZ, "Snap To Last Selected Z", "Snap selected spline points to world Z position of last selected spline point.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetLockedAxisNone, "None", "New spline point axis is not fixed.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetLockedAxisX, "X", "Fix X axis when adding new spline points.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetLockedAxisY, "Y", "Fix Y axis when adding new spline points.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetLockedAxisZ, "Z", "Fix Z axis when adding new spline points.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(VisualizeRollAndScale, "Visualize Roll and Scale", "Whether the visualization should show roll and scale on this spline.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(DiscontinuousSpline, "Allow Discontinuous Splines", "Whether the visualization allows Arrive and Leave tangents to be set separately.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ResetToDefault, "Reset to Default", "Reset this spline to its archetype default.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FContentBrowserCommands：
		UI_COMMAND(OpenAssetsOrFolders, "Open Assets or Folders", "Opens the selected assets or folders, depending on the selection", EUserInterfaceActionType::Button, FInputChord(EKeys::Enter));
		UI_COMMAND(PreviewAssets, "Preview Assets", "Loads the selected assets and previews them if possible", EUserInterfaceActionType::Button, FInputChord(EKeys::SpaceBar));
		UI_COMMAND(CreateNewFolder, "Create New Folder", "Creates new folder in selected path", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::N));
		UI_COMMAND(SaveSelectedAsset, "Save Selected Asset", "Save the selected asset", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::S));
		UI_COMMAND(SaveAllCurrentFolder, "Save All", "Save All in current folder", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::S));
		UI_COMMAND(ResaveAllCurrentFolder, "Resave All", "Resave all assets contained in the current folder", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FCurveEditorCommands：
		UI_COMMAND(ZoomToFitHorizontal, "Fit Horizontal", "Zoom to Fit - Horizontal", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ZoomToFitVertical, "Fit Vertical", "Zoom to Fit - Vertical", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ZoomToFit, "Fit", "Zoom to Fit", EUserInterfaceActionType::Button, FInputChord(EKeys::F));
		UI_COMMAND(ZoomToFitAll, "FitAll", "Zoom to Fit All", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(ToggleInputSnapping, "Input Snapping", "Toggle Time Snapping", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleOutputSnapping, "Output Snapping", "Toggle Value Snapping", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(ToggleExpandCollapseNodes, "Expand/Collapse Nodes", "Toggle expand or collapse selected nodes", EUserInterfaceActionType::Button, FInputChord(EKeys::V) );
		UI_COMMAND(ToggleExpandCollapseNodesAndDescendants, "Expand/Collapse Nodes and Descendants", "Toggle expand or collapse selected nodes and descendants", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::V) );

		UI_COMMAND(InterpolationConstant, "Constant", "Constant interpolation", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Five));
		UI_COMMAND(InterpolationLinear, "Linear", "Linear interpolation", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Four));
		UI_COMMAND(InterpolationCubicSmartAuto, "Smart Auto", "Cubic interpolation - Smart Automatic tangents", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Zero));
		UI_COMMAND(InterpolationCubicAuto, "Auto", "Cubic interpolation - Automatic tangents", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::One));
		UI_COMMAND(InterpolationCubicUser, "User", "Cubic interpolation - User flat tangents", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Two));
		UI_COMMAND(InterpolationCubicBreak, "Break", "Cubic interpolation - User broken tangents", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Three));
		UI_COMMAND(InterpolationToggleWeighted, "Weighted Tangents", "Toggle weighted tangents for cubic interpolation modes. Only supported on some curve types", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control, EKeys::W));

		UI_COMMAND(FlattenTangents, "Flatten", "Flatten Tangents", EUserInterfaceActionType::Button, FInputChord(EKeys::Six));
		UI_COMMAND(StraightenTangents, "Straighten", "Straighten Tangents", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(BakeCurve, "Bake", "Bake curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReduceCurve, "Reduce", "Reduce curve", EUserInterfaceActionType::Button, FInputChord());

		// Pre and Post Infinity
		UI_COMMAND(SetPreInfinityExtrapCycle, "Cycle", "Cycle creates a repeating cycle from the first to last key, effectively modulating the input time. This can create jumps if the terminus values are not the same value.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPreInfinityExtrapCycleWithOffset, "Cycle with Offset", "Creates a repeating cycle where the value is added to the last value of the previous Cycle. This will avoid jumps but will cause drift over time if there's a net change in value.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPreInfinityExtrapOscillate, "Oscillate (Ping Pong)", "Creates a repeating cycle which ping pongs and will play from beginning to end, then end to beginning.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPreInfinityExtrapLinear, "Linear", "Linearly interpolates based on the in tangent of the first key.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPreInfinityExtrapConstant, "Constant", "Extrapolation will always return the value of the first key.", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(SetPostInfinityExtrapCycle, "Cycle", "Cycle creates a repeating cycle from the first to last key, effectively modulating the input time. This can create jumps if the terminus values are not the same value", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPostInfinityExtrapCycleWithOffset, "Cycle with Offset", "Creates a repeating cycle where the value is added to the last value of the previous Cycle. This will avoid jumps but will cause drift over time if there's a net change in value.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPostInfinityExtrapOscillate, "Oscillate (Ping Pong)", "Creates a repeating cycle which ping pongs and will play from beginning to end, then end to beginning.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPostInfinityExtrapLinear, "Linear", "Linearly interpolates based on the in tangent of the last key.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetPostInfinityExtrapConstant, "Constant", "Extrapolation will always return the value of the last key.", EUserInterfaceActionType::RadioButton, FInputChord());

		// Tangent Visibility
		UI_COMMAND(SetAllTangentsVisibility, "All Tangents", "Show all tangents in the curve editor.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetSelectedKeysTangentVisibility, "Selected Keys", "Show tangents for selected keys in the curve editor.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SetNoTangentsVisibility, "No Tangents", "Show no tangents in the curve editor.", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(ToggleAutoFrameCurveEditor, "Auto Frame Curves", "Auto frame curves when they are selected.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND(ToggleSnapTimeToSelection, "Snap Time to Selection", "Snap the current time to the first selected key time.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND(ToggleShowBufferedCurves, "Buffered Curves", "Show buffered curves for the selected curves.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND(ToggleShowCurveEditorCurveToolTips, "Curve Tool Tips", "Show a tool tip with name and values when hovering over a curve.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND(ToggleShowBars, "Show Bars", "Show Bars like Constraints and Spaces", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(AddKeyHovered, "Add Key", "Add a new key to this curve at the current position.", EUserInterfaceActionType::Button, FInputChord(EKeys::MiddleMouseButton) );
		UI_COMMAND(PasteKeysHovered, "Paste", "Paste clipboard contents", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::V));
		UI_COMMAND(PasteOverwriteRange, "Paste Overwrite", "Pastes the keys from the clipboard, overwriting any key in destination track between the first and last pasted keys.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::V));

		UI_COMMAND(AddKeyToAllCurves, "Add Key", "Add a new key to all curves at the current time.", EUserInterfaceActionType::Button, FInputChord(EKeys::Enter) );

		// Curve Editor Colors
		UI_COMMAND(SetRandomCurveColorsForSelected, "Set Random Curve Colors", "Set random colors on the selected curves. Note they are stored in the Level Sequence Actor Editor Preferences.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetCurveColorsForSelected, "Set Curve Color For Selected", "Set the chosen color on the selected curves. Note they are stored in the Level Sequence Actor Editor Preferences.", EUserInterfaceActionType::Button, FInputChord());

		// Graph Viewing Modes
		UI_COMMAND(SetViewModeAbsolute, "Absolute View Mode", "Absolute view displays all curves overlapping with the Y axis proportionally scaled.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetViewModeStacked, "Stacked View Mode", "Stacked view displays each curve in its own graph with the Y axis normalized [-1, 1].", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetViewModeNormalized, "Normalized View Mode", "Normalized view displays all curves overlapping with the Y axis normalized [-1, 1].", EUserInterfaceActionType::ToggleButton, FInputChord());

		// Deactivate the currently active tool
		UI_COMMAND(DeactivateCurrentTool, "Deactivate Tool", "Deactivates the current tool and returns to just supporting selection.", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Q));

		// User Implementable Filter window
		UI_COMMAND(OpenUserImplementableFilterWindow, "Filter...", "Opens a window which lets you choose from user implementable filter classes with advanced settings.", EUserInterfaceActionType::Button, FInputChord());
		
		UI_COMMAND(SelectAllKeys, "Select All Keys", "Select all keys.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::A));
		// Deselect any keys that the user has selected.
		UI_COMMAND(DeselectAllKeys, "Deselect All Keys", "Clears your current key selection.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::D));

		UI_COMMAND(SelectForward, "Select All Keys Forward", "Select all keys forward from the current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::RightBracket));
		UI_COMMAND(SelectBackward, "Select All Keys Backward", "Select all keys backward from the current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::LeftBracket));

		UI_COMMAND(SelectNone, "Select None", "Select none", EUserInterfaceActionType::Button, FInputChord(EKeys::Escape));

		// Buffer and Apply Curves. Like copy and paste, but directly onto the curves they were stored from.
		// These names are overwritten in CurveEditorContextMenu to show the number of stashed curves.
		UI_COMMAND(BufferVisibleCurves, "Buffer Curves", "Stores a copy of the selected curves which can be applied back onto themselves.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SwapBufferedCurves, "Swap Buffered Curves", "Applies the buffered curves to the curves they were stored from and stores the current curves to the buffer.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ApplyBufferedCurves, "Apply Buffered Curves", "Applies the buffered curves to the curves they were stored from.", EUserInterfaceActionType::Button, FInputChord());

		// Axis Snapping
		UI_COMMAND(SetAxisSnappingNone, "Both", "Disable axis snapping and allow movement on both the X and Y directions.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetAxisSnappingHorizontal, "X Only", "Snap transform tool axis movement to X direction.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetAxisSnappingVertical, "Y Only", "Snap transform tool axis movement to Y direction.", EUserInterfaceActionType::Button, FInputChord());	
		
		//Key Movement
		UI_COMMAND(TranslateSelectedKeysLeft, "Translate Selected Keys Left", "Translate selected keys one frame to the left", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Left));
		UI_COMMAND(TranslateSelectedKeysRight, "Translate Selected Keys Right", "Translate selected keys one frame to the right", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Right));

		// Time Management
		UI_COMMAND(StepToNextKey, "Step to Next Key", "Step to the next key", EUserInterfaceActionType::Button, FInputChord(EKeys::Period));
		UI_COMMAND(StepToPreviousKey, "Step to Previous Key", "Step to the previous key", EUserInterfaceActionType::Button, FInputChord(EKeys::Comma));
		UI_COMMAND(StepForward, "Step Forward", "Step the timeline forward", EUserInterfaceActionType::Button, FInputChord(EKeys::Right));
		UI_COMMAND(StepBackward, "Step Backward", "Step the timeline backward", EUserInterfaceActionType::Button, FInputChord(EKeys::Left));
		UI_COMMAND(JumpToStart, "Jump to Start", "Jump to the start of the playback range", EUserInterfaceActionType::Button, FInputChord(EKeys::Up));
		UI_COMMAND(JumpToEnd, "Jump to End", "Jump to the end of the playback range", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Up));
		UI_COMMAND(ScrubTime, "Scrub Time", "Scrub mouse left and right to change time", EUserInterfaceActionType::Button, FInputChord(EKeys::B));

		// Selection Range
		UI_COMMAND(SetSelectionRangeStart, "Set Selection Start", "Sets the start of the selection range", EUserInterfaceActionType::Button, FInputChord(EKeys::I) );
		UI_COMMAND(SetSelectionRangeEnd, "Set Selection End", "Sets the end of the selection range", EUserInterfaceActionType::Button, FInputChord(EKeys::O) );
		UI_COMMAND(ClearSelectionRange, "Clear Selection Range", "Clear the selection range", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::X) );
		*/

		/**
		FCurveTableEditorCommands：
		UI_COMMAND(CurveViewToggle, "Curve View", "Changes the view of the curve table from grid to curve view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(AppendKeyColumn, "Append Key Column", "Append a new column to the curve table.\nEvery Curve or Table Row will have a new key appended.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteSelectedCurves, "Delete Curves", "Deleted the selected curve rows.", EUserInterfaceActionType::None, FInputChord());
		UI_COMMAND(RenameSelectedCurve, "Rename Curve", "Rename the selected curve row.", EUserInterfaceActionType::None, FInputChord());
		*/

		/**
		FDerivedDataStatusBarMenuCommands：
		UI_COMMAND(ChangeSettings, "Change Cache Settings", "Opens a dialog to change Cache settings.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ViewCacheStatistics, "View Cache Statistics", "Opens the Cache Statistics panel.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ViewResourceUsage, "View Resource Usage", "Opens the Resource Usage panel.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FDistCurveEditorCommands：
		UI_COMMAND(RemoveCurve, "Remove Curve", "Remove Curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveAllCurves, "Remove All Curves", "Remove All Curves", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetTime, "Set Time", "Set Time", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetValue, "Set Value", "Set Value", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetColor, "Set Color", "Set Color", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteKeys, "Delete Key", "Delete Key", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ScaleTimes, "Scale All Times", "Scales the times of all points of all visible tracks", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ScaleValues, "Scale All Values", "Scales the values of all points of all visible tracks", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ScaleSingleCurveTimes, "Scale Curve Times", "Scales the times of all points of this curve & its sub-curves", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ScaleSingleCurveValues, "Scale Curve Values", "Scales the values of all points of this curve & its sub-curves", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ScaleSingleSubCurveValues, "Scale Sub-Curve Values", "Scales the values of all points of this curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(FitHorizontally, "Horizontal", "Fit Horizontally", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(FitVertically, "Vertical", "Fit Vertically", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Fit, "Fit", "Fit to Selected", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PanMode, "Pan", "Pan Mode", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ZoomMode, "Zoom", "Zoom Mode", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(CurveAuto, "Auto", "Curve Auto", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(CurveAutoClamped, "Auto/Clamped", "Curve Auto/Clamped", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(CurveUser, "User", "Curve User", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(CurveBreak, "Break", "Curve Break", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(Linear, "Linear", "Linear", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(Constant, "Constant", "Constant", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(FlattenTangents, "Flatten", "Flatten Tangents", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(StraightenTangents, "Straighten", "Straighten Tangents", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ShowAllTangents, "Show All", "ShowAll Tangents", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(CreateTab, "Create", "Create Tab", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteTab, "Delete", "Delete Tab", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FFoliageEditCommands：
		UI_COMMAND( DecreaseBrushSize, "Decrease Brush Size", "Decreases the size of the foliage brush", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftBracket) );
		UI_COMMAND( IncreaseBrushSize, "Increase Brush Size", "Increases the size of the foliage brush", EUserInterfaceActionType::Button, FInputChord(EKeys::RightBracket) );

		UI_COMMAND( DecreasePaintDensity, "Decrease Brush Density", "Decreases the density of the foliage brush", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::LeftBracket) );
		UI_COMMAND( IncreasePaintDensity, "Increase Brush Density", "Increases the density of the foliage brush", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::RightBracket) );

		UI_COMMAND( DecreaseUnpaintDensity, "Decrease Erase Density", "Decreases the density of the foliage eraser", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::LeftBracket));
		UI_COMMAND( IncreaseUnpaintDensity, "Increase Erase Density", "Increases the density of the foliage eraser", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::RightBracket));

		UI_COMMAND( SetPaint, "Paint", "Paint", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetReapplySettings, "Reapply", "Reapply settings to instances", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetSelect, "Select", "Select", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetLassoSelect, "Lasso", "Lasso Select", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetPaintBucket, "Fill", "Paint Bucket", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( SetNoSettings, "Hide Details", "Hide details.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetPaintSettings, "Show Painting settings", "Show painting settings.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetClusterSettings, "Show Instance settings", "Show settings for placed instances.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		*/

		/**
		FFoliagePaletteCommands：
		UI_COMMAND(ActivateFoliageType, "Activate", "Sets the selected foliage types in the palette as active (i.e. included in brush actions).", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeactivateFoliageType, "Deactivate", "Sets the selected foliage types in the palette as inactive (i.e. excluded in brush actions).", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveFoliageType, "Remove", "Remove this foliage type from the palette. Removes all associated instances as well.", EUserInterfaceActionType::Button, FInputChord(EKeys::Delete));
		UI_COMMAND(ShowFoliageTypeInCB, "Show in Content Browser", "Show asset in Content Browser.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReflectSelectionInPalette, "Reflect Selection in Palette.", "Select foliage type in palette based on selected foliage instances.", EUserInterfaceActionType::None, FInputChord());
		UI_COMMAND(SelectAllInstances, "Select All Instances", "Select all instances of this foliage type (must be in a selection mode).", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeselectAllInstances, "Deselect All Instances", "Deselect all instances of this foliage type (must be in a selection mode).", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectInvalidInstances, "Select Invalid Instances", "Select all instances of this foliage type that are off ground (must be in a selection mode).", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FFontEditorCommands：
		UI_COMMAND(Update, "Update", "Imports a texture to replace the currently selected page.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(UpdateAll, "Update All", "Imports a set of textures to replace all pages.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportPage, "Export", "Exports the currently selected page.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportAllPages, "Export All", "Exports all pages.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(FontBackgroundColor, "Background", "Changes the background color of the previewer.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(FontForegroundColor, "Foreground", "Changes the foreground color of the previewer.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FGraphEditorCommandsImpl：
		UI_COMMAND( ReconstructNodes, "Refresh Nodes", "Refreshes nodes", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( BreakNodeLinks, "Break Node Link(s)", "Breaks the selected node from all connected pins", EUserInterfaceActionType::Button, FInputChord() )
		
		UI_COMMAND( AddExecutionPin, "Add Execution Pin", "Adds another execution output pin to an execution sequence or switch node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( InsertExecutionPinBefore, "Insert Execution Pin Before", "Adds another execution output pin before this one, to an execution sequence node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( InsertExecutionPinAfter, "Insert Execution Pin After", "Adds another execution output pin after this one, to an execution sequence node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( RemoveExecutionPin, "Remove Execution Pin", "Removes an execution output pin from an execution sequence or switch node", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( RemoveThisStructVarPin, "Remove This Struct Variable Pin", "Removes the selected input pin", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( RemoveOtherStructVarPins, "Remove All Other Pins", "Removes all variable input pins, except for the selected one", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( RestoreAllStructVarPins, "Restore All Structure Pins", "Restore all structure pins", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( AddOptionPin, "Add Option Pin", "Adds another option input pin to the node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( RemoveOptionPin, "Remove Option Pin", "Removes the last option input pin from the node", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( ChangePinType, "Change Pin Type", "Changes the type of this pin (boolean, int, etc.)", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( DeleteAndReconnectNodes, "Delete and Reconnect Exec Pins", "Deletes the currently selected nodes and makes connections between all input pins to their output pins.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Delete), FInputChord(EModifierKey::Shift, EKeys::BackSpace))

		UI_COMMAND( ShowAllPins, "Show All Pins", "Shows all pins", EUserInterfaceActionType::RadioButton, FInputChord() )
		UI_COMMAND( HideNoConnectionPins, "Hide Unconnected Pins", "Hides all pins with no connections", EUserInterfaceActionType::RadioButton, FInputChord() )
		UI_COMMAND( HideNoConnectionNoDefaultPins, "Hide Unused Pins", "Hides all pins with no connections and no default value", EUserInterfaceActionType::RadioButton, FInputChord() )

		UI_COMMAND( AddParentNode, "Add Call to Parent Function", "Adds a node that calls this function's parent", EUserInterfaceActionType::Button, FInputChord() )
		
		UI_COMMAND( CreateMatchingFunction, "Create Matching Function", "Adds a function to the blueprint with a matching signature", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( ToggleBreakpoint, "Toggle Breakpoint", "Adds or removes a breakpoint on each selected node", EUserInterfaceActionType::Button, FInputChord(EKeys::F9) )
		UI_COMMAND( AddBreakpoint, "Add Breakpoint", "Adds a breakpoint to each selected node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( RemoveBreakpoint, "Remove Breakpoint", "Removes any breakpoints on each selected node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( EnableBreakpoint, "Enable Breakpoint", "Enables any breakpoints on each selected node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( DisableBreakpoint, "Disable Breakpoint", "Disables any breakpoints on each selected node", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( CollapseNodes, "Collapse Nodes", "Collapses selected nodes into a single node", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( PromoteSelectionToFunction, "Promote to Function", "Promotes selected collapsed graphs to functions.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( PromoteSelectionToMacro, "Promote to Macro", "Promotes selected collapsed graphs to macros.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ExpandNodes, "Expand Node", "Expands the node's internal graph into the current graph and removes this node.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( CollapseSelectionToFunction, "Collapse to Function", "Collapses selected nodes into a single function node.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( CollapseSelectionToMacro, "Collapse to Macro", "Collapses selected nodes into a single macro node.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ConvertFunctionToEvent, "Convert Function to Event", "Converts selected function to an event and removes the function defintion.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ConvertEventToFunction, "Convert Event to Function", "Converts the selected event to a function graph and removes this event node.", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( AlignNodesTop, "Align Top", "Aligns the top edges of the selected nodes", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::W) )
		UI_COMMAND( AlignNodesMiddle, "Align Middle", "Aligns the vertical middles of the selected nodes", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift|EModifierKey::Alt, EKeys::W) )
		UI_COMMAND( AlignNodesBottom, "Align Bottom", "Aligns the bottom edges of the selected nodes", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::S) )
		UI_COMMAND( AlignNodesLeft, "Align Left", "Aligns the left edges of the selected nodes", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::A) )
		UI_COMMAND( AlignNodesCenter, "Align Center", "Aligns the horizontal centers of the selected nodes", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift | EModifierKey::Alt, EKeys::S) )
		UI_COMMAND( AlignNodesRight, "Align Right", "Aligns the right edges of the selected nodes", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::D) )

		UI_COMMAND( StraightenConnections, "Straighten Connection(s)", "Straightens connections between the selected nodes.", EUserInterfaceActionType::Button, FInputChord(EKeys::Q) )

		UI_COMMAND( DistributeNodesHorizontally, "Distribute Horizontally", "Evenly distributes the selected nodes horizontally", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( DistributeNodesVertically, "Distribute Vertically", "Evenly distributes the selected nodes vertically", EUserInterfaceActionType::Button, FInputChord() )
		
		UI_COMMAND( EnableNodes, "Enable Nodes", "Selected node(s) will be enabled.", EUserInterfaceActionType::Check, FInputChord() )
		UI_COMMAND( DisableNodes, "Disable Nodes", "Selected node(s) will be disabled.", EUserInterfaceActionType::Check, FInputChord() )
		UI_COMMAND( EnableNodes_Always, "Enable Nodes (Always)", "Selected node(s) will always be enabled.", EUserInterfaceActionType::RadioButton, FInputChord() )
		UI_COMMAND( EnableNodes_DevelopmentOnly, "Enable Nodes (Development Only)", "Selected node(s) will be enabled in development mode only.", EUserInterfaceActionType::RadioButton, FInputChord() )

		UI_COMMAND( SelectReferenceInLevel, "Find Actor in Level", "Select the actor referenced by this node in the level", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( AssignReferencedActor, "Assign Selected Actor", "Assign the selected actor to be this node's referenced object", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( FindReferences, "Find References", "Find references of this item", EUserInterfaceActionType::Button, FInputChord(EKeys::F, EModifierKey::Shift | EModifierKey::Alt) )
		UI_COMMAND( FindAndReplaceReferences, "Replace References", "Brings up a window to help find and replace all instances of this item", EUserInterfaceActionType::Button, FInputChord() )
		
		UI_COMMAND( GoToDefinition, "Goto Definition", "Jumps to the defintion of the selected node if available, e.g., C++ code for a native function or the graph for a Blueprint function.", EUserInterfaceActionType::Button, FInputChord(EKeys::G, EModifierKey::Alt) )

		UI_COMMAND( BreakThisLink, "Break This Link", "Breaks the selected pin's only link.", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( BreakPinLinks, "Break All Pin Links", "Breaks all of the selected pin's links", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( PromoteToVariable, "Promote to Variable", "Promotes something to a variable", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( PromoteToLocalVariable, "Promote to Local Variable", "Promotes something to a local variable of the current function", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( SplitStructPin, "Split Struct Pin", "Breaks a struct pin in to a separate pin per element", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( RecombineStructPin, "Recombine Struct Pin", "Takes struct pins that have been broken in to composite elements and combines them back to a single struct pin", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( StartWatchingPin, "Watch This Value", "Adds this pin or variable to the watch list", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( StopWatchingPin, "Stop Watching This Value", "Removes this pin or variable from the watch list ", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( ResetPinToDefaultValue, "Reset to Default Value", "Reset value of this pin to the default", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( SelectAllInputNodes, "Select All Input Nodes", "Adds all input Nodes linked to this Pin to selection", EUserInterfaceActionType::Button, FInputChord() )
		UI_COMMAND( SelectAllOutputNodes, "Select All Output Nodes", "Adds all output Nodes linked to this Pin to selection", EUserInterfaceActionType::Button, FInputChord() )

		UI_COMMAND( CreateComment, "Create Comment", "Create a comment box", EUserInterfaceActionType::Button, FInputChord(EKeys::C))

		UI_COMMAND( ZoomIn, "Zoom In", "Zoom in on the graph editor", EUserInterfaceActionType::Button, FInputChord(EKeys::Add))
		UI_COMMAND( ZoomOut, "Zoom Out", "Zoom out from the graph editor", EUserInterfaceActionType::Button, FInputChord(EKeys::Subtract))

		UI_COMMAND( GoToDocumentation, "View Documentation", "View documentation for this node.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( SummonCreateNodeMenu, "Open Create Node Menu", "Opens the create node menu at the last known mouse position.", EUserInterfaceActionType::Button, FInputChord(EKeys::Tab) );
		*/

		/**
		FBlueprintDebuggerCommands：
		UI_COMMAND(ShowCallStackViewer, "Call Stack", "Toggles visibility of the Call Stack window", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(ShowExecutionTrace, "Data Flow", "Toggles visibility of the Data Flow window", EUserInterfaceActionType::Check, FInputChord());
		*/

		/**
		FBlueprintEditorCommands：
		UI_COMMAND( FindInBlueprint, "Find", "Finds references to functions, events, variables, and pins in the current Blueprint (use Ctrl+Shift+F to search in all Blueprints)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F) );
		UI_COMMAND( FindInBlueprints, "Find in Blueprints", "Find references to functions, events and variables in ALL Blueprints", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::F) );
		UI_COMMAND( ReparentBlueprint, "Reparent Blueprint", "Change the parent of this Blueprint", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( CompileBlueprint, "Compile", "Compile the blueprint", EUserInterfaceActionType::Button, FInputChord(EKeys::F7) );
		UI_COMMAND( RefreshAllNodes, "Refresh All nodes", "Refreshes all nodes in the graph to account for external changes", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeleteUnusedVariables, "Delete Unused Variables", "Deletes any variables that are never used", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( FindReferencesFromClass, "List references (from class)", "Find all objects that the class references", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( FindReferencesFromBlueprint, "List referenced (from blueprint)", "Find all objects that the blueprint references", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RepairCorruptedBlueprint, "Repair corrupted blueprint", "Attempts to repair a corrupted blueprint that cannot be saved", EUserInterfaceActionType::Button, FInputChord() );

		// View commands 
		UI_COMMAND( ZoomToWindow, "Zoom to Graph Extents", "Fit the current view to the entire graph", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ZoomToSelection, "Zoom to Selection", "Fit the current view to the selection", EUserInterfaceActionType::Button, FInputChord(EKeys::Home) );
		UI_COMMAND( NavigateToParent, "Go to parent graph", "Open the parent graph", EUserInterfaceActionType::Button, FInputChord(EKeys::PageUp) );
		UI_COMMAND( NavigateToParentBackspace, "Go to parent graph", "Open the parent graph", EUserInterfaceActionType::Button, FInputChord(EKeys::BackSpace) );
		UI_COMMAND( NavigateToChild, "Go to child graph", "Open the child graph", EUserInterfaceActionType::Button, FInputChord(EKeys::PageDown) );

		// Preview commands
		UI_COMMAND( ResetCamera, "Reset Camera", "Resets the camera to focus on the mesh", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( EnableSimulation, "Simulation", "Enables simulation of components in the viewport", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowFloor, "Show Floor", "Toggles a ground mesh for collision", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowGrid, "Show Grid", "Toggles viewport grid", EUserInterfaceActionType::ToggleButton, FInputChord() );

		// Debugging commands
		UI_COMMAND( EnableAllBreakpoints,"Enable All Breakpoints", "Enable all breakpoints", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DisableAllBreakpoints, "Disable All Breakpoints", "Disable all breakpoints", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ClearAllBreakpoints, "Delete All Breakpoints", "Delete all breakpoints", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::F9) );
		UI_COMMAND(	ClearAllWatches, "Delete All Watches", "Delete all watches", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenBlueprintDebugger, "Blueprint Debugger", "Open the Blueprint Debugger tab.", EUserInterfaceActionType::Button, FInputChord() );

		// New documents
		UI_COMMAND( AddNewVariable, "Variable", "Adds a new variable to this blueprint.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddNewLocalVariable, "Local Variable", "Adds a new local variable to this graph.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddNewFunction, "Function", "Add a new function graph", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND(	AddNewMacroDeclaration, "Macro", "Add a new macro declaration graph", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddNewAnimationLayer, "Animation Layer", "Add a new animation layer", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddNewEventGraph, "Graph", "Add a new event graph", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddNewDelegate, "Event Dispatcher", "Add a new event dispatcher", EUserInterfaceActionType::Button, FInputChord() );

		// Development commands
		UI_COMMAND( SaveIntermediateBuildProducts, "Save Intermediate Build Products", "Should the compiler save intermediate build products for debugging.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND(GenerateSearchIndex, "Generate Search Index", "Generate the search index for this blueprint.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DumpCachedIndexData, "Dump Cached Index Data", "Dump the cached index data for this blueprint.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ShowActionMenuItemSignatures, "Show Action Menu Item Signatures", "If enabled, tooltips on action menu items will show the associated action's signature id (can be used to setup custom favorites menus).", EUserInterfaceActionType::ToggleButton, FInputChord());
		
		// SCC commands
		UI_COMMAND( BeginBlueprintMerge, "Merge", "Shows the Blueprint merge panel and toolbar, allowing the user to resolve conflicted blueprints", EUserInterfaceActionType::Button, FInputChord() );
		
		// Hide unrelated nodes
		UI_COMMAND( ToggleHideUnrelatedNodes, "Hide Unrelated", "Toggles automatically hiding nodes which are unrelated to the selected nodes.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		*/

		/**
		FFullBlueprintEditorCommands：
		UI_COMMAND(Compile, "Compile", "Compile the blueprint", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(SaveOnCompile_Never, "Never", "Sets the save-on-compile option to 'Never', meaning that your Blueprints will not be saved when they are compiled", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SaveOnCompile_SuccessOnly, "On Success Only", "Sets the save-on-compile option to 'Success Only', meaning that your Blueprints will be saved whenever they are successfully compiled", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SaveOnCompile_Always, "Always", "Sets the save-on-compile option to 'Always', meaning that your Blueprints will be saved whenever they are compiled (even if there were errors)", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(SwitchToScriptingMode, "Graph", "Switches to Graph Editing Mode", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SwitchToBlueprintDefaultsMode, "Defaults", "Switches to Class Defaults Mode", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SwitchToComponentsMode, "Components", "Switches to Components Mode", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(EditGlobalOptions, "Class Settings", "Edit Class Settings (Previously known as Blueprint Props)", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(EditClassDefaults, "Class Defaults", "Edit the initial values of your class.", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(JumpToErrorNode, "Jump to Error Node", "When enabled, then the Blueprint will snap focus to nodes producing an error during compilation", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		FBlueprintFavoritesPaletteCommands：
		UI_COMMAND(RemoveSingleFavorite, "Remove from Favorites",          "Removes this item from your favorites list.",                 EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveSubFavorites,   "Remove Category from Favorites", "Removes all the nodes in this category from your favorites.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ClearFavorites,       "Clear All Favorites",			   "Clears out all of your favorited nodes.",                     EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FBlueprintLibraryPaletteCommands：
		UI_COMMAND(AddSingleFavorite,    "Add to Favorites",               "Adds this item to your favorites list.",                      EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddSubFavorites,      "Add Category to Favorites",      "Adds all the nodes in this category to your favorites.",      EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveSingleFavorite, "Remove from Favorites",          "Removes this item from your favorites list.",                 EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveSubFavorites,   "Remove Category from Favorites", "Removes all the nodes in this category from your favorites.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FBlueprintPaletteCommands：
		UI_COMMAND(RefreshPalette, "Refresh List", "Refreshes the list of nodes.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FMyBlueprintCommands：
		UI_COMMAND( OpenGraph, "Open Graph", "Opens up this function, macro, or event graph's graph panel up.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenGraphInNewTab, "Open in New Tab", "Opens up this function, macro, or event graph's graph panel up in a new tab. Hold down Ctrl and double click for shortcut.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenExternalGraph, "Open External Graph", "Opens up this external graph's graph panel in its own asset editor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( FocusNode, "Focus", "Focuses on the associated node", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( FocusNodeInNewTab, "Focus in New Tab", "Focuses on the associated node in a new tab", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ImplementFunction, "Implement event", "Implements this overridable function as a new event.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeleteEntry, "Delete", "Deletes this function or variable from this blueprint.", EUserInterfaceActionType::Button, FInputChord(EKeys::Platform_Delete));
		UI_COMMAND( PasteVariable, "Paste Variable", "Pastes the variable to this blueprint.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( PasteLocalVariable, "Paste Local Variable", "Pastes the variable to this scope.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( PasteFunction, "Paste Function", "Pastes the function to this blueprint.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( PasteMacro, "Paste Macro", "Pastes the macro to this blueprint.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( GotoNativeVarDefinition, "Goto Code Definition", "Goto the native code definition of this variable", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MoveVariableToParent, "Move to Parent Class", "Moves the variable to its parent class", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MoveFunctionToParent, "Move to Parent Class", "Moves the function to its parent class", EUserInterfaceActionType::Button, FInputChord() );
		*/

		/**
		FLandscapeEditorCommands：
		UI_COMMAND(ManageMode, "Mode - Manage", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SculptMode, "Mode - Sculpt", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PaintMode, "Mode - Paint", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(NewLandscape, "New", "Create or import a new landscape", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ResizeLandscape, "Resize", "Change Component Size", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ImportExportTool, "Import", "Import or Export landscape data", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SculptTool, "Sculpt", "Sculpt height data.\n\nClick to raise, Shift+Click to lower.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(EraseTool, "Erase", "Erase height data.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PaintTool, "Paint", "Paint weight data.\n\nClick to paint, Shift+Click to erase.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SmoothTool, "Smooth", "Smooths heightmaps or blend layers.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(FlattenTool, "Flatten", "Flattens an area of heightmap or blend layer.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(RampTool, "Ramp", "Creates a ramp between two points.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ErosionTool, "Erosion", "Thermal Erosion - Simulates erosion caused by the movement of soil from higher areas to lower areas", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(HydroErosionTool, "Hydro", "Hydro Erosion - Simulates erosion caused by rainfall", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(NoiseTool, "Noise", "Adds noise to the heightmap or blend layer", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(RetopologizeTool, "Retop", "Automatically adjusts landscape vertices with an X/Y offset map to improve vertex density on cliffs, reducing texture stretching.\nNote: An X/Y offset map makes the landscape slower to render and paint on with other tools, so only use if needed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(VisibilityTool, "Visibility", "Mask out individual quads in the landscape, leaving a hole.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(BlueprintBrushTool, "Blueprint", "Custom painting tools created using Blueprint.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SelectComponentTool, "Select", "Select components to use with other tools", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AddComponentTool, "Add", "Add components to the landscape", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DeleteComponentTool, "Delete", "Delete components from the landscape, leaving a hole", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MoveToLevelTool, "Move", "Move landscape components to a landscape proxy in the currently active streaming level, so that they can be streamed in/out independently of the rest of the landscape", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(RegionSelectTool, "Select", "Select a region of landscape to use as a mask for other tools", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(RegionCopyPasteTool, "Copy", "Copy/Paste areas of the landscape, or import/export a copied area of landscape from disk", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MirrorTool, "Mirror", "Copies one side of a landscape to the other, to easily create a mirrored landscape.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SplineTool, "Splines", "Ctrl+click to add control points\n\nHaving a control point selected when you ctrl+click will connect to the new control point with a segment\n\nSpline mesh settings can be found on the details panel when you have segments selected", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CircleBrush, "Circle", "Simple circular brush", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AlphaBrush, "Alpha", "Alpha brush, orients a mask image with the brush stroke", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(AlphaBrush_Pattern, "Pattern", "Pattern brush, tiles a mask image across the landscape", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ComponentBrush, "Component", "Work with entire landscape components", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(GizmoBrush, "Gizmo", "Work with the landscape gizmo, used for copy/pasting landscape", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CircleBrush_Smooth, "Smooth", "Smooth falloff", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CircleBrush_Linear, "Linear", "Sharp, linear falloff", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CircleBrush_Spherical, "Spherical", "Spherical falloff, smooth at the center and sharp at the edge", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CircleBrush_Tip, "Tip", "Tip falloff, sharp at the center and smooth at the edge", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(ViewModeNormal, "Normal", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewModeLOD, "LOD", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewModeLayerUsage, "Layer Usage", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewModeLayerDensity, "Layer Density", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewModeLayerDebug, "Layer Debug", "", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ViewModeWireframeOnTop, "Wireframe on Top", "", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(ViewModeLayerContribution, "Layer Contribution", "", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(IncreaseBrushSize, "Increase Brush Size", "Press this key to increase brush size by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EKeys::RightBracket));
		UI_COMMAND(DecreaseBrushSize, "Decrease Brush Size", "Press this key to decrease brush size by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EKeys::LeftBracket));
		UI_COMMAND(IncreaseBrushFalloff, "Increase Brush Falloff", "Press this key to increase brush falloff by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::RightBracket));
		UI_COMMAND(DecreaseBrushFalloff, "Decrease Brush Falloff", "Press this key to decrease brush falloff by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::LeftBracket));
		UI_COMMAND(IncreaseBrushStrength, "Increase Brush Strength", "Press this key to increase brush strength by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Control, EKeys::RightBracket));
		UI_COMMAND(DecreaseBrushStrength, "Decrease Brush Strength", "Press this key to decrease brush strength by a fixed increment.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Control, EKeys::LeftBracket));
		UI_COMMAND(IncreaseAlphaBrushRotation, "Increase Alpha Brush Rotation", "Press this key to increase alpha brush rotation by a fixed increment.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DecreaseAlphaBrushRotation, "Decrease Alpha Brush Rotation", "Press this key to decrease alpha brush rotation by a fixed increment.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(DragBrushSizeAndFalloff, "Change Brush Size And Falloff", "Hold this key and then drag to increase or decrease brush size (right/left) or falloff (up/down).", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::RightMouseButton));
		UI_COMMAND(DragBrushSize, "Change Brush Size", "Hold this key and then drag to increase or decrease brush size.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DragBrushFalloff, "Change Brush Falloff", "Hold this key and then drag to increase or decrease brush falloff.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DragBrushStrength, "Change Brush Strength", "Hold this key and then drag to increase or decrease brush strength.", EUserInterfaceActionType::RadioButton, FInputChord());
		*/

		/**
		FLayersViewCommands：
		UI_COMMAND( CreateEmptyLayer, "Create Empty Layer", "Creates a new empty Layer", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddSelectedActorsToNewLayer, "Add Selected Actors to New Layer", "Adds the actors currently selected in the active viewport to a new layer", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddSelectedActorsToSelectedLayer, "Add Selected Actors to Selected Layers", "Adds the actors currently selected in the viewport to the selected layers", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemoveSelectedActorsFromSelectedLayer, "Remove Selected Actors from Layers", "Removes the actors currently selected in the viewport from the selected layers", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SelectActors, "Select Actors", "Actors in the selected Layers becomes the viewport's selection", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AppendActorsToSelection, "Append Actors to Selection", "Adds the Actors in the selected Layers to the viewport's existing selection", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeselectActors, "Deselect Actors", "Removes the Actors in the selected Layers from the viewport's existing selection", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ToggleSelectedLayersVisibility, "Toggle Visibility of Selected Layers", "Toggles the visibility of the selected layers in the viewports", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MakeAllLayersVisible, "Make All Layers Visible", "Toggles all layers to a visible state in the viewports", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( RequestRenameLayer, "Rename", "Rename the selected layer.", EUserInterfaceActionType::Button, FInputChord( EKeys::F2 ) );	
		*/

		/**
		FLevelEditorCommands：
		Level Editor页面：UI_COMMAND( BrowseDocumentation, "Level Editor Documentation", "Details on how to use the Level Editor", EUserInterfaceActionType::Button, FInputChord( EKeys::F1 ) );
      	Viewport Controls页面：UI_COMMAND( BrowseViewportControls, "Viewport Controls", "Ways to move around in the 3D viewport", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( NewLevel, "New Level...", "Create a new level, or choose a level template to start from.", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::N ) );
      	UI_COMMAND( OpenLevel, "Open Level...", "Loads an existing level", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::O ) );
      	UI_COMMAND( Save, "Save Current Level", "Saves the current level to disk", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::S) );
      	UI_COMMAND( SaveAs, "Save Current Level As...", "Save the current level as...", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control|EModifierKey::Alt, EKeys::S ) );
      	UI_COMMAND( SaveAllLevels, "Save All Levels", "Saves all unsaved levels to disk", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BrowseLevel, "Browse To Level", "Browses to the associated level and selects it in the most recently used Content Browser (summoning one if necessary)", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( ToggleFavorite, "Toggle Favorite", "Sets whether the currently loaded level will appear in the list of favorite levels", EUserInterfaceActionType::Button, FInputChord() );

      	UI_COMMAND( ClearRecentFiles, "Clear Recent Levels", "Clear the list of recently opened levels", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( ImportScene, "Import Into Level...", "Imports a scene from a FBX or OBJ format into the current level", EUserInterfaceActionType::Button, FInputChord());
      	UI_COMMAND( ExportAll, "Export All...", "Exports the entire level to a file on disk (multiple formats are supported.)", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( ExportSelected, "Export Selected...", "Exports currently-selected objects to a file on disk (multiple formats are supported.)", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( Build, "Build All Levels", "Builds all levels (precomputes lighting data and visibility data, generates navigation networks and updates brush models.)\nThis action is not available while Play in Editor is active, static lighting is disabled in the project settings, or when previewing less than Shader Model 5", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildAndSubmitToSourceControl, "Build and Submit...", "Displays a window that allows you to build all levels and submit them to revision control", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildLightingOnly, "Build Lighting", "Only precomputes lighting (all levels.)\nThis action is not available while Play in Editor is active, static lighting is disabled in the project settings, or when previewing less than Shader Model 5", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::Semicolon) );
      	UI_COMMAND( BuildReflectionCapturesOnly, "Build Reflection Captures", "Updates Reflection Captures and stores their data in the BuildData package.\nThis action is not available while Play in Editor is active, static lighting is disabled in the project settings", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildLightingOnly_VisibilityOnly, "Precompute Static Visibility", "Only precomputes static visibility data (all levels.)", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( LightingBuildOptions_UseErrorColoring, "Use Error Coloring", "When enabled, errors during lighting precomputation will be baked as colors into light map data", EUserInterfaceActionType::ToggleButton, FInputChord() );
      	UI_COMMAND( LightingBuildOptions_ShowLightingStats, "Show Lighting Stats", "When enabled, a window containing metrics about lighting performance and memory will be displayed after a successful build.", EUserInterfaceActionType::ToggleButton, FInputChord() );
      	UI_COMMAND( BuildGeometryOnly, "Build Geometry", "Only builds geometry (all levels.)", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildGeometryOnly_OnlyCurrentLevel, "Build Geometry (Current Level)", "Builds geometry, only for the current level", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildPathsOnly, "Build Paths", "Only builds paths (all levels.)", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( BuildHLODs, "Build HLODs", "Builds all HLODs for the current world", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( BuildMinimap, "Build World Partition Editor Minimap", "Builds the minimap for the current world", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildLandscapeSplineMeshes, "Build Landscape Spline Meshes", "Builds landscape spline meshes for the current world", EUserInterfaceActionType::Button, FInputChord());
      	UI_COMMAND( BuildTextureStreamingOnly, "Build Texture Streaming", "Build texture streaming data", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( BuildVirtualTextureOnly, "Build Virtual Textures", "Build runtime virtual texture low mips streaming data", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( BuildAllLandscape, "Build Landscape", "Build all data related to landscape (grass maps, physical material, Nanite, dirty height and weight maps)", EUserInterfaceActionType::Button, FInputChord());

      	UI_COMMAND( LightingQuality_Production, "Production", "Sets precomputed lighting quality to highest possible quality (slowest computation time.)", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingQuality_High, "High", "Sets precomputed lighting quality to high quality", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingQuality_Medium, "Medium", "Sets precomputed lighting quality to medium quality", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingQuality_Preview, "Preview", "Sets precomputed lighting quality to preview quality (fastest computation time.)", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingDensity_RenderGrayscale, "Render Grayscale", "Renders the lightmap density.", EUserInterfaceActionType::ToggleButton, FInputChord() );
      	UI_COMMAND( LightingResolution_CurrentLevel, "Current Level", "Adjust only primitives in the current level.", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingResolution_SelectedLevels, "Selected Levels", "Adjust only primitives in the selected levels.", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingResolution_AllLoadedLevels, "All Loaded Levels", "Adjust primitives in all loaded levels.", EUserInterfaceActionType::RadioButton, FInputChord() );
      	UI_COMMAND( LightingResolution_SelectedObjectsOnly, "Selected Objects Only", "Adjust only selected objects in the levels.", EUserInterfaceActionType::ToggleButton, FInputChord() );
      	UI_COMMAND( LightingStaticMeshInfo, "Lighting StaticMesh Info...", "Shows the lighting information for the StaticMeshes.", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( SceneStats, "Open Scene Stats", "Opens the Scene Stats viewer", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( TextureStats, "Open Texture Stats", "Opens the Texture Stats viewer", EUserInterfaceActionType::Button, FInputChord() );
      	UI_COMMAND( MapCheck, "Open Map Check", "Checks map for errors", EUserInterfaceActionType::Button, FInputChord() );

      	UI_COMMAND( RecompileGameCode, "Recompile Game Code", "Recompiles and reloads C++ code for game systems on the fly", EUserInterfaceActionType::Button, FInputChord( EKeys::P, EModifierKey::Alt | EModifierKey::Control | EModifierKey::Shift ) );

		UI_COMMAND( LiveCoding_Enable, "Enable Live Coding", "Hot-patches C++ function changes into the current process.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( LiveCoding_StartSession, "Start Session", "Starts a live coding session.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( LiveCoding_ShowConsole, "Show Console", "Displays the live coding console window.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( LiveCoding_Settings, "Settings...", "Open the live coding settings", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( EditAsset, "Edit Asset", "Edits the asset associated with the selected actor", EUserInterfaceActionType::Button, FInputChord( EKeys::E, EModifierKey::Control ) );
		UI_COMMAND( EditAssetNoConfirmMultiple, "Edit Multiple Assets", "Edits multiple assets associated with the selected actor without a confirmation prompt", EUserInterfaceActionType::Button, FInputChord( EKeys::E, EModifierKey::Control | EModifierKey::Shift ) );
		UI_COMMAND( OpenSelectionInPropertyMatrix, "Edit Selection in Property Matrix", "Bulk edit the selected assets in the Property Matrix", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( GoHere, "Go Here", "Moves the camera to the current mouse position", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SnapCameraToObject, "Snap View to Object", "Snaps the view to the selected object", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapObjectToCamera, "Snap Object to View", "Snaps the selected object to the view", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND(CopyActorFilePathtoClipboard, "Copy Selected Actor(s) File Path", "Copy the file path of the selected actors", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SaveActor, "Save Selected Actor(s)", "Save the selected actors", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ShowActorHistory, "Show Actor History", "Shows the history of the file containing the actor.", EUserInterfaceActionType::Button, FInputChord());	

		UI_COMMAND( GoToCodeForActor, "Go to C++ Code for Actor", "Opens a code editing IDE and navigates to the source file associated with the seleced actor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( GoToDocsForActor, "Go to Documentation for Actor", "Opens documentation for the Actor in the default web browser", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( PasteHere, "Paste Here", "Pastes the actor at the click location", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SnapOriginToGrid, "Snap Origin to Grid", "Snaps the actor to the nearest grid location at its origin", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::End ) );
		UI_COMMAND( SnapOriginToGridPerActor, "Snap Origin to Grid Per Actor", "Snaps each selected actor separately to the nearest grid location at its origin", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AlignOriginToGrid, "Align Origin to Grid", "Aligns the actor to the nearest grid location at its origin", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SnapTo2DLayer, "Snap to 2D Layer", "Snaps the actor to the current 2D snap layer", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MoveSelectionUpIn2DLayers, "Bring selection forward a snap layer", "Bring selection forward a snap layer", EUserInterfaceActionType::Button, FInputChord(EKeys::PageUp, EModifierKey::Control) );
		UI_COMMAND( MoveSelectionDownIn2DLayers, "Send selection backward a snap layer", "Send selection backward a snap layer", EUserInterfaceActionType::Button, FInputChord(EKeys::PageDown, EModifierKey::Control) );
		UI_COMMAND( MoveSelectionToTop2DLayer, "Bring selection to the front snap layer", "Bring selection to the front snap layer", EUserInterfaceActionType::Button, FInputChord(EKeys::PageUp, EModifierKey::Shift | EModifierKey::Control) );
		UI_COMMAND( MoveSelectionToBottom2DLayer, "Send selection to the back snap layer", "Send selection to the back snap layer", EUserInterfaceActionType::Button, FInputChord(EKeys::PageDown, EModifierKey::Shift | EModifierKey::Control) );
		UI_COMMAND( Select2DLayerAbove, "Select next 2D layer", "Changes the active layer to the next 2D layer", EUserInterfaceActionType::Button, FInputChord(EKeys::PageUp, EModifierKey::Alt) );
		UI_COMMAND( Select2DLayerBelow, "Select previous 2D layer", "Changes the active layer to the previous 2D layer", EUserInterfaceActionType::Button, FInputChord(EKeys::PageDown, EModifierKey::Alt) );

		UI_COMMAND( SnapToFloor, "Snap to Floor", "Snaps the actor or component to the floor below it", EUserInterfaceActionType::Button, FInputChord( EKeys::End ) );
		UI_COMMAND( AlignToFloor, "Align to Floor", "Aligns the actor or component with the floor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapPivotToFloor, "Snap Pivot to Floor", "Snaps the actor to the floor at its pivot point", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Alt, EKeys::End ) );	
		UI_COMMAND( AlignPivotToFloor, "Align Pivot to Floor", "Aligns the actor with the floor at its pivot point", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapBottomCenterBoundsToFloor, "Snap Bottom Center Bounds to Floor", "Snaps the actor to the floor at its bottom center bounds", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::End ) );
		UI_COMMAND( AlignBottomCenterBoundsToFloor, "Align Bottom Center Bounds to Floor", "Aligns the actor with the floor at its bottom center bounds", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapOriginToActor, "Snap Origin to Actor", "SNaps the actor to another actor at its origin", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AlignOriginToActor, "Align Origin to Actor", "Aligns the actor to another actor at its origin", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapToActor, "Snap to Actor", "Snaps the actor to another actor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AlignToActor, "Align to Actor", "Aligns the actor with another actor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapPivotToActor, "Snap Pivot to Actor", "Snaps the actor to another actor at its pivot point", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AlignPivotToActor, "Align Pivot to Actor", "Aligns the actor with another actor at its pivot point", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapBottomCenterBoundsToActor, "Snap Bottom Center Bounds to Actor", "Snaps the actor to another actor at its bottom center bounds", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AlignBottomCenterBoundsToActor, "Align Bottom Center Bounds to Actor", "Aligns the actor with another actor at its bottom center bounds", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeltaTransformToActors, "Delta Transform", "Apply Delta Transform to selected elements", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MirrorActorX, "Mirror X", "Mirrors the element along the X axis", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MirrorActorY, "Mirror Y", "Mirrors the element along the Y axis", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MirrorActorZ, "Mirror Z", "Mirrors the element along the Z axis", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( LockActorMovement, "Lock Actor Movement", "Locks the actor so it cannot be moved", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( DetachFromParent, "Detach", "Detach the actor from its parent", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AttachSelectedActors, "Attach Selected Actors", "Attach the selected actors to the last selected actor", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::B) );
		UI_COMMAND( AttachActorIteractive, "Attach Actor Interactive", "Start an interactive actor picker to let you choose a parent for the currently selected actor", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::A) );
		UI_COMMAND( CreateNewOutlinerFolder, "Create Folder", "Place the selected actors in a new folder", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( HoldToEnableVertexSnapping, "Hold to Enable Vertex Snapping", "When the key binding is pressed and held vertex snapping will be enabled", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::V) );
		UI_COMMAND( HoldToEnablePivotVertexSnapping, "Hold to Enable Pivot Vertex Snapping", "Hold to enable vertex snapping while dragging a pivot. Alt must be a modifier in this command or it will not work.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::V) );

		UI_COMMAND( SavePivotToPrePivot, "Set as Pivot Offset", "Sets the current pivot location as the pivot offset for this actor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ResetPrePivot, "Reset Pivot Offset", "Resets the pivot offset for this actor", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ResetPivot, "Reset Pivot", "Resets the pivot", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MovePivotHere, "Set Pivot Offset Here", "Sets the pivot offset to the clicked location", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MovePivotHereSnapped, "Set Pivot Offset Here (Snapped)", "Sets the pivot offset to the nearest grid point to the clicked location", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MovePivotToCenter, "Center on Selection", "Centers the pivot to the middle of the selection", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ConvertToAdditive, "Additive", "Converts the selected brushes to additive brushes", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertToSubtractive, "Subtractive", "Converts the selected brushes to subtractive brushes", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( OrderFirst, "To First", "Changes the drawing order of the selected brushes so they are the first to draw", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OrderLast, "To Last", "Changes the drawing order of the selected brushes so they are the last to draw", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( MakeSolid, "Solid", "Makes the selected brushes solid", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MakeSemiSolid, "Semi-Solid", "Makes the selected brushes semi-solid", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MakeNonSolid, "Non-Solid", "Makes the selected brushes non-solid", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( MergePolys, "Merge", "Merges multiple polygons on a brush face into as few as possible", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SeparatePolys, "Separate", "Reverses the effect of a previous merge", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AlignBrushVerticesToGrid, "Align Brush Vertices To Grid", "Align brush vertices to the grid", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( GroupActors, "Group", "Groups the selected actors", EUserInterfaceActionType::Button, FInputChord( EKeys::G, EModifierKey::Control ) );
		UI_COMMAND( RegroupActors, "Regroup", "Regroups the selected actors into a new group, removing any current groups in the selection", EUserInterfaceActionType::Button, FInputChord( EKeys::G, EModifierKey::Control ) );
		UI_COMMAND( UngroupActors, "Ungroup", "Ungroups the selected actors", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::G ) );
		UI_COMMAND( AddActorsToGroup, "Add to Group", "Adds the selected actors to the selected group", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemoveActorsFromGroup, "Remove from Group", "Removes the selected actors from the selected groups", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( LockGroup, "Lock", "Locks the selected groups", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( UnlockGroup, "Unlock", "Unlocks the selected groups", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( FixupGroupActor, "Fixup Group Actor", "Removes null actors and deletes the GroupActor if it is empty.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( ShowAll, "Show All Actors", "Shows all actors", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::H ) );

		UI_COMMAND( ShowSelectedOnly, "Show Only Selected", "Shows only the selected actors", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ShowSelected, "Show Selected", "Shows the selected actors", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::H ) );
		UI_COMMAND( HideSelected, "Hide Selected", "Hides the selected actors", EUserInterfaceActionType::Button, FInputChord( EKeys::H ) );
		UI_COMMAND( ShowAllStartup, "Show All At Startup", "Shows all actors at startup", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ShowSelectedStartup, "Show Selected At Startup", "Shows selected actors at startup", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( HideSelectedStartup, "Hide Selected At Startup", "Hide selected actors at startup", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CycleNavigationDataDrawn, "Cycle Navigation Data Drawn", "Cycles through navigation data (navmeshes for example) to draw one at a time", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Alt, EKeys::N ) );

		UI_COMMAND( SelectNone, "Unselect All", "Unselects all actors", EUserInterfaceActionType::Button, FInputChord( EKeys::Escape ) ) ;
		UI_COMMAND( InvertSelection, "Invert Selection", "Inverts the current selection", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SelectImmediateChildren, "Select Immediate Children", "Selects immediate children of the current selection", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Alt|EModifierKey::Control, EKeys::D) );
		UI_COMMAND( SelectAllDescendants, "Select All Descendants", "Selects all descendants of the current selection", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift|EModifierKey::Control, EKeys::D) );
		UI_COMMAND( SelectAllActorsOfSameClass, "Select All Actors of Same Class", "Selects all the actors that have the same class", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift|EModifierKey::Control, EKeys::A) );
		UI_COMMAND( SelectAllActorsOfSameClassWithArchetype, "Select All Actors with Same Archetype", "Selects all the actors of the same class that have the same archetype", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectComponentOwnerActor, "Select Component Owner", "Select the actor that owns the currently selected component(s)", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectRelevantLights, "Select Relevant Lights", "Select all lights relevant to the current selection", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectStaticMeshesOfSameClass, "Select All Using Selected Static Meshes (Selected Actor Types)", "Selects all actors with the same static mesh and actor class as the selection", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectOwningHierarchicalLODCluster, "Select Owning Hierarchical LOD cluster Using Selected Static Mesh (Selected Actor Types)", "Select Owning Hierarchical LOD cluster for the selected actor", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( SelectStaticMeshesAllClasses, "Select All Using Selected Static Meshes (All Actor Types)", "Selects all actors with the same static mesh as the selection", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::E ) ); 
		UI_COMMAND( SelectSkeletalMeshesOfSameClass, "Select All Using Selected Skeletal Meshes (Selected Actor Types)", "Selects all actors with the same skeletal mesh and actor class as the selection", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectSkeletalMeshesAllClasses, "Select All Using Selected Skeletal Meshes (All Actor Types)", "Selects all actors with the same skeletal mesh as the selection", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectAllWithSameMaterial, "Select All With Same Material", "Selects all actors with the same material as the selection", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectMatchingEmitter, "Select All Matching Emitters", "Selects all emitters with the same particle system as the selection", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectAllLights, "Select All Lights", "Selects all lights", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectStationaryLightsExceedingOverlap, "Select Stationary Lights exceeding overlap", "Selects all stationary lights exceeding the overlap limit", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectAllAddditiveBrushes, "Select All Additive Brushes", "Selects all additive brushes", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( SelectAllSubtractiveBrushes, "Select All Subtractive Brushes", "Selects all subtractive brushes", EUserInterfaceActionType::Button, FInputChord() ); 

		UI_COMMAND( SelectAllSurfaces, "Select All Surfaces", "Selects all bsp surfaces", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::S) ); 

		UI_COMMAND( SurfSelectAllMatchingBrush, "Select Matching Brush", "Selects the surfaces belonging to the same brush as the selected surfaces", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::B) ); 
		UI_COMMAND( SurfSelectAllMatchingTexture, "Select Matching Material", "Selects all surfaces with the same material as the selected surfaces", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::T) ); 
		UI_COMMAND( SurfSelectAllAdjacents, "Select All Adjacent Surfaces", "Selects all surfaces adjacent to the currently selected surfaces", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::J) ); 
		UI_COMMAND( SurfSelectAllAdjacentCoplanars, "Select All Coplanar Surfaces", "Selects all surfaces adjacent and coplanar with the selected surfaces", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::C) ); 
		UI_COMMAND( SurfSelectAllAdjacentWalls, "Select All Adjacent Wall Surfaces", "Selects all adjacent upright surfaces", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::W) ); 
		UI_COMMAND( SurfSelectAllAdjacentFloors, "Select All Adjacent Floor Surfaces", "Selects all adjacent floor sufaces(ones with normals pointing up)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::U) ); 
		UI_COMMAND( SurfSelectAllAdjacentSlants, "Select All Adjacent Slant Surfaces", "Selects all adjacent slant surfaces (surfaces that are not walls, floors, or ceilings according to their normals) to the currently selected surfaces.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Y) ); 
		UI_COMMAND( SurfSelectReverse, "Invert Surface Selection", "Inverts the current surface selection", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Q) );
		UI_COMMAND( SurfSelectMemorize, "Memorize Surface Selection", "Stores the current surface selection in memory", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::M) ); 
		UI_COMMAND( SurfSelectRecall, "Recall Surface Selection", "Replace the current selection with the selection saved in memory", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::R) ); 
		UI_COMMAND( SurfSelectOr, "Surface Selection OR", "Replace the current selection with only the surfaces which are both currently selected and contained within the saved selection in memory", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::O) ); 
		UI_COMMAND( SurfSelectAnd, "Surface Selection AND", "Add the selection of surfaces saved in memory to the current selection", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::A) ); 
		UI_COMMAND( SurfSelectXor, "Surace Selection XOR", " Replace the current selection with only the surfaces that are not in both the current selection and the selection saved in memory", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::X) ); 
		UI_COMMAND( SurfUnalign, "Align Surface Default", "Default surface alignment", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SurfAlignPlanarAuto, "Align Surface Planar", "Planar surface alignment", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SurfAlignPlanarWall, "Align Surface Planar Wall", "Planar wall surface alignment", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SurfAlignPlanarFloor, "Align Surface Planar Floor", "Planar floor surface alignment", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SurfAlignBox, "Align Surface Box", "Box surface alignment", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SurfAlignFit, "Align Surface Fit", "Best fit surface alignment", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ApplyMaterialToSurface, "Apply Material to Surface Selection", "Applies the selected material to the selected surfaces", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( CreateBoundingBoxVolume, "Create Bounding Box Blocking Volume From Mesh", "Create a bounding box blocking volume from the static mesh", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateHeavyConvexVolume, "Heavy Convex Blocking Volume From Mesh", "Creates a heavy convex blocking volume from the static mesh", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateNormalConvexVolume, "Normal Convex Blocking Volume From Mesh", "Creates a normal convex blocking volume from the static mesh", EUserInterfaceActionType::Button, FInputChord() ); 
		UI_COMMAND( CreateLightConvexVolume, "Light Convex Blocking Volume From Mesh", "Creates a light convex blocking volume from the static mesh", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateRoughConvexVolume, "Rough Convex Blocking Volume From Mesh", "Creates a rough convex blocking volume from the static mesh", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( KeepSimulationChanges, "Keep Simulation Changes", "Saves the changes made to this actor in Simulate mode to the actor's default state.", EUserInterfaceActionType::Button, FInputChord( EKeys::K ) );

		UI_COMMAND( MakeActorLevelCurrent, "Make Selected Actor's Level Current", "Makes the selected actor's level the current level", EUserInterfaceActionType::Button, FInputChord( EKeys::M ) );

		UI_COMMAND( MoveSelectedToCurrentLevel, "Move Selection to Current Level", "Moves the selected actors to the current level", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::M ) );

		UI_COMMAND( FindActorLevelInContentBrowser, "Find Actor Level in Content Browser", "Finds the selected actors' level in the content browser", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( FindLevelsInLevelBrowser, "Find Levels in Level Browser", "Finds the selected actors' levels in the level browser", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddLevelsToSelection, "Add Levels to Selection", "Adds the selected actors' levels to the current level browser selection", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemoveLevelsFromSelection, "Remove Levels from Selection", "Removes the selected actors' levels from the current level browser selection", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( FindActorInLevelScript, "Find in Level Blueprint", "Finds any references to the selected actor in its level's blueprint", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( WorldProperties, "World Settings", "Displays the world settings", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenPlaceActors, "Place Actors Panel", "Opens the Place Actors Panel", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenContentBrowser, "Open Content Browser", "Opens the Content Browser", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::F) );
		UI_COMMAND( OpenMarketplace, "Unreal Marketplace", "Opens the Marketplace", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ImportContent, "Import Content...", "Import Content into a specified location", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( ToggleVR, "Toggle VR", "Toggles VR (Virtual Reality) mode", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Shift, EKeys::V ) );

		UI_COMMAND( OpenLevelBlueprint, "Open Level Blueprint", "Edit the Level Blueprint for the current level", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CheckOutProjectSettingsConfig, "Check Out", "Checks out the project settings config file so the game mode can be set.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateBlankBlueprintClass, "New Empty Blueprint Class...", "Create a new Blueprint Class", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertSelectionToBlueprint, "Convert Selection to Blueprint Class...", "Replace all of the selected actors with a new Blueprint Class", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ShowTransformWidget, "Show Transform Widget", "Toggles the visibility of the transform widgets", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( AllowTranslucentSelection, "Allow Translucent Selection", "Allows translucent objects to be selected", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::T) );
		UI_COMMAND( AllowGroupSelection, "Allow Group Selection", "Allows actor groups to be selected", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::G) );
		UI_COMMAND( StrictBoxSelect, "Strict Box Selection", "When enabled an object must be entirely encompassed by the selection box when marquee box selecting", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( TransparentBoxSelect, "Box Select Occluded Objects", "When enabled, marquee box select operations will also select objects that are occluded by other objects.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowSelectionSubcomponents, "Show Subcomponents", "Toggles the visibility of the subcomponents related to the current selection", EUserInterfaceActionType::ToggleButton, FInputChord() );
		
		UI_COMMAND( DrawBrushMarkerPolys, "Draw Brush Polys", "Draws semi-transparent polygons around a brush when selected", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( OnlyLoadVisibleInPIE, "Only Load Visible Levels in Game Preview", "If enabled, when game preview starts, only visible levels will be loaded", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSocketSnapping, "Enable Socket Snapping", "Enables or disables snapping to sockets", EUserInterfaceActionType::ToggleButton, FInputChord() ); 
		UI_COMMAND( ToggleParticleSystemLOD, "Enable Particle System LOD Switching", "If enabled particle systems will use distance LOD switching in perspective viewports", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleFreezeParticleSimulation, "Freeze Particle Simulation", "If enabled particle systems will freeze their simulation state", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleParticleSystemHelpers, "Toggle Particle System Helpers", "Toggles showing particle system helper widgets in viewports", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleLODViewLocking, "Enable LOD View Locking", "If enabled viewports of the same type will use the same LOD", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( LevelStreamingVolumePrevis, "Enable Automatic Level Streaming", "If enabled, the viewport will stream in levels automatically when the camera is moved", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( EnableActorSnap, "Enable Actor Snapping", "If enabled, actors will snap to the location of other actors when they are within distance", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::K) );
		UI_COMMAND( EnableVertexSnap, "Enable Vertex Snapping","If enabled, actors will snap to the location of the nearest vertex on another actor in the direction of movement", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleHideViewportUI, "Hide Viewport UI", "Toggles hidden viewport UI mode. Hides all overlaid viewport UI widgets", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ShowSelectedDetails, "Show Actor Details", "Opens a details panel for the selected actors", EUserInterfaceActionType::Button, FInputChord( EKeys::F4 ) );

		UI_COMMAND( RecompileShaders, "Recompile Changed Shaders", "Recompiles shaders which are out of date", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift|EModifierKey::Control, EKeys::Period ) );
		UI_COMMAND( ProfileGPU, "Profile GPU", "Profiles the GPU for the next frame and opens a window with profiled data", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift|EModifierKey::Control, EKeys::Comma ) );
		UI_COMMAND( DumpGPU, "Dump GPU", "Dump the GPU intermediary resources for the next frame and opens explorer", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift|EModifierKey::Control, EKeys::Slash ) );

		UI_COMMAND( ResetAllParticleSystems, "Reset All Particle Systems", "Resets all particle system emitters (removes all active particles and restarts them)", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::Slash ) );
		UI_COMMAND( ResetSelectedParticleSystem, "Resets Selected Particle Systems" , "Resets selected particle system emitters (removes all active particles and restarts them)", EUserInterfaceActionType::Button, FInputChord( EKeys::Slash ) );

		UI_COMMAND( SelectActorsInLayers, "Select all actors in selected actor's layers", "Selects all actors belonging to the layers of the currently selected actors", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::L ) );

		UI_COMMAND(MaterialQualityLevel_Low, "Low", "Sets material quality in the scene to low.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MaterialQualityLevel_Medium, "Medium", "Sets material quality in the scene to medium.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MaterialQualityLevel_High, "High", "Sets material quality in the scene to high.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MaterialQualityLevel_Epic, "Epic", "Sets material quality in the scene to Epic.", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(ToggleFeatureLevelPreview, "Preview Mode Toggle", "Toggles the Preview Mode on or off for the currently selected Preview target", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		FLevelViewportCommands：
		UI_COMMAND( ToggleMaximize, "Maximize Viewport", "Toggles the Maximize state of the current viewport", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleGameView, "Game View", "Toggles game view.  Game view shows the scene as it appears in game", EUserInterfaceActionType::ToggleButton, FInputChord( EKeys::G ) );
		UI_COMMAND( ToggleImmersive, "Immersive Mode", "Switches this viewport between immersive mode and regular mode", EUserInterfaceActionType::ToggleButton, PLATFORM_MAC ? FInputChord( EModifierKey::Control, EKeys::F11 ) : FInputChord( EKeys::F11 ) );
		UI_COMMAND(ToggleSidebarAllTabs, "Sidebar All Tabs", "Moves all tabs except the level editor to a sidebar or restores any previous state before if all tabs are already sidebared", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::F10));

		UI_COMMAND( HighResScreenshot, "High Resolution Screenshot...", "Opens the control panel for high resolution screenshots", EUserInterfaceActionType::Button, FInputChord() );
		
		UI_COMMAND( UseDefaultShowFlags, "Use Defaults", "Resets all show flags to default", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( PilotSelectedActor, "Pilot Selected Actor", "Move the selected actor around using the viewport controls, and bind the viewport to the actor's location and orientation.", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control | EModifierKey::Shift, EKeys::P ) );
		UI_COMMAND( EjectActorPilot, "Eject from Actor Pilot", "Stop piloting an actor with the current viewport. Unlocks the viewport's position and orientation from the actor the viewport is currently piloting.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ToggleActorPilotCameraView, "Actor Pilot Camera View", "Toggles showing the exact camera view when using the viewport to pilot a camera", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control | EModifierKey::Shift, EKeys::C ) );

		UI_COMMAND( ViewportConfig_OnePane, "Layout One Pane", "Changes the viewport arrangement to one pane", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_TwoPanesH, "Layout Two Panes (horizontal)", "Changes the viewport arrangement to two panes, side-by-side", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_TwoPanesV, "Layout Two Panes (vertical)", "Changes the viewport arrangement to two panes, one above the other", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_ThreePanesLeft, "Layout Three Panes (one left, two right)", "Changes the viewport arrangement to three panes, one on the left, two on the right", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_ThreePanesRight, "Layout Three Panes (one right, two left)", "Changes the viewport arrangement to three panes, one on the right, two on the left", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_ThreePanesTop, "Layout Three Panes (one top, two bottom)", "Changes the viewport arrangement to three panes, one on the top, two on the bottom", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_ThreePanesBottom, "Layout Three Panes (one bottom, two top)", "Changes the viewport arrangement to three panes, one on the bottom, two on the top", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_FourPanesLeft, "Layout Four Panes (one left, three right)", "Changes the viewport arrangement to four panes, one on the left, three on the right", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_FourPanesRight, "Layout Four Panes (one right, three left)", "Changes the viewport arrangement to four panes, one on the right, three on the left", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_FourPanesTop, "Layout Four Panes (one top, three bottom)", "Changes the viewport arrangement to four panes, one on the top, three on the bottom", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_FourPanesBottom, "Layout Four Panes (one bottom, three top)", "Changes the viewport arrangement to four panes, one on the bottom, three on the top", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ViewportConfig_FourPanes2x2, "Layout Four Panes (2x2)", "Changes the viewport arrangement to four panes, in a 2x2 grid", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( SetDefaultViewportType, "Default Viewport", "Reconfigures this viewport to the default arrangement", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( ToggleViewportToolbar, "Show Toolbar", "Defines whether a toolbar should be displayed on this viewport", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::T) );

		UI_COMMAND( ApplyMaterialToActor, "Apply Material", "Attempts to apply a dropped material to this object", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ToggleCinematicPreview, "Allow Cinematic Control", "If enabled, allows cinematic (Sequencer) previews to play in this viewport", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( FindInLevelScriptBlueprint, "Find In Level Script", "Finds references of a selected actor in the level script blueprint", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::K) );
		UI_COMMAND( AdvancedSettings, "Advanced Settings...", "Opens the advanced viewport settings", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( ShowAllVolumes, "Show All Volumes", "Shows all volumes", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( HideAllVolumes, "Hide All Volumes", "Hides all volumes", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ShowAllLayers, "Show All Layers", "Shows all layers", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( HideAllLayers, "Hide All Layers", "Hides all layers", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ShowAllSprites, "Show All Sprites", "Shows all sprites", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( HideAllSprites, "Hide All Sprites", "Hides all sprites", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND(HideAllStats, "Hide All Stats", "Hides all Stats", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( CompactBookmarks, "Compact Bookmarks", "Attempts to move bookmark indices so they are continuous (does not mapped bookmarks).", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ClearAllBookmarks, "Clear All Bookmarks", "Clears all the bookmarks", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( EnablePreviewMesh, "Hold To Enable Preview Mesh", "When held down a preview mesh appears under the cursor", EUserInterfaceActionType::Button, FInputChord(EKeys::Backslash) );
		UI_COMMAND( CyclePreviewMesh, "Cycles Preview Mesh", "Cycles available preview meshes", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::Backslash ) );
		*/

		/**
		FLightEditingCommands：
		UI_COMMAND(SwapLightType, "Add Key Frame", "Inserts a new key frame at the current time", EUserInterfaceActionType::Button, FInputChord(EKeys::P, EModifierKey::Shift));
		*/

		/**
		FLevelInstanceEditorModeCommands：
		UI_COMMAND(ExitMode, "Exit Mode", "Exits mode asking to save pending changes", EUserInterfaceActionType::Button, FInputChord(EKeys::Escape));
		UI_COMMAND(ToggleContextRestriction, "Toggle Context Restriction", "Toggles edit restrictions like selection to current level edit", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::L, EModifierKey::Shift));
		*/

		/**
		FLocalizationTargetEditorCommands：
		UI_COMMAND(GatherText, "Gather Text", "Gather text for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportTextAllCultures, "Import Text", "Import translations for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportTextAllCultures, "Export Text", "Export translations for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportDialogueScriptAllCultures, "Import Script", "Import dialogue scripts for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportDialogueScriptAllCultures, "Export Script", "Export dialogue scripts for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportDialogueAllCultures, "Import Dialogue", "Import dialogue WAV files for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CountWords, "Count Words", "Count translations for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CompileTextAllCultures, "Compile Text", "Compile translations for all cultures of this target.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FLocalizationDashboardCommands：
		UI_COMMAND(GatherTextAllTargets, "Gather Text", "Gather text for all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportTextAllTargets, "Import Text", "Import translations for all cultures of all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportTextAllTargets, "Export Text", "Export translations for all cultures of all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportDialogueScriptAllTargets, "Import Script", "Import dialogue scripts for all cultures of all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportDialogueScriptAllTargets, "Export Script", "Export dialogue scripts for all cultures of all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportDialogueAllTargets, "Import Dialogue", "Import dialogue WAV files for all cultures of all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CountWordsForAllTargets, "Count Words", "Count translations for all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CompileTextAllTargets, "Compile Text", "Compile translations for all targets in the project.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FMainFrameCommands：
		UI_COMMAND( SaveAll, "Save All", "Saves all unsaved levels and assets to disk", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control | EModifierKey::Shift, EKeys::S ) );
		UI_COMMAND( ChooseFilesToSave, "Choose Files to Save...", "Opens a dialog with save options for content and levels", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control | EModifierKey::Alt | EModifierKey::Shift, EKeys::S ) );
		UI_COMMAND( ViewChangelists, "View Changes", "Opens a dialog displaying current changes.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SubmitContent, "Submit Content", "Opens a dialog with check in options for content and levels.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SyncContent, "Sync Content", "Saves all unsaved levels and assets to disk and then downloads the latest versions from revision control.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConnectToSourceControl, "Connect to Revision Control...", "Connect to a revision control system for tracking changes to your content and levels.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ChangeSourceControlSettings, "Change Revision Control Settings...", "Opens a dialog to change revision control settings.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( NewProject, "New Project...", "Opens a dialog to create a new game project", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenProject, "Open Project...", "Opens a dialog to choose a game project to open", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND(AddCodeToProject, "New C++ Class...", "Adds C++ code to the project. The code can only be compiled if you have an appropriate C++ compiler installed.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RefreshCodeProject, "Refresh code project", "Refreshes your C++ code project.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(OpenIDE, "Open IDE", "Opens your C++ code in an integrated development environment.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ZipUpProject, "Zip Project", "Zips the project into a zip file.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( Exit, "Exit", "Exits the application", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenDeviceManagerApp, "Device Manager", "Opens up the device manager app", EUserInterfaceActionType::Check, FInputChord() );
		UI_COMMAND( OpenSessionManagerApp, "Session Manager", "Opens up the session manager app", EUserInterfaceActionType::Check, FInputChord() );
		UI_COMMAND(OpenMarketplace, "Open Marketplace", "Opens the Marketplace", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DocumentationHome, "Documentation Home", "Authoritative, in-depth technical resources for using Unreal Engine", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(BrowseAPIReference, "C++ API Reference", "Classes, functions, and other elements that make up the C++ API", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(BrowseCVars, "Console Variables", "Reference companion for console variables and commands", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(VisitCommunityHome, "Dev Community", "Join the worldwide community of Unreal developers and explore all the resources it has to offer", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(VisitOnlineLearning, "Learning Library", "Learn Unreal Engine for free with easy-to-follow video courses and guided learning paths", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(VisitForums, "Forums", "View announcements and engage in discussions with other developers", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(VisitSearchForAnswersPage, "Q&A", "Search for answers, ask questions, and share your knowledge with other developers", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(VisitCommunitySnippets, "Snippets", "Access and share ready-to-use code blocks and scripts", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(VisitSupportWebSite, "Support", "Options for personalized technical support", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReportABug, "Report a Bug", "Found a bug? Let us know about it", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(OpenIssueTracker, "Issue Tracker", "Check the current status of public bugs and other issues", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( AboutUnrealEd, "About Unreal Editor", "Version and copyright information", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreditsUnrealEd, "Credits", "Contributors to this version of Unreal Engine", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND(VisitEpicGamesDotCom, "Visit UnrealEngine.com", "Learn more about Unreal technology", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportLayout, "Import Layout...", "Import a custom layout (or set of layouts) from a different directory and load it into your current instance of the Unreal Editor UI", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SaveLayoutAs, "Save Layout As...", "Save the current layout customization on disk so it can be loaded later", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ExportLayout, "Export Layout...", "Export the custom layout customization to a different directory", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveUserLayouts, "Remove All User Layouts...", "Remove all the layout customizations created by the user", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ToggleFullscreen, "Enable Fullscreen", "Enables fullscreen mode for the application, expanding across the entire monitor", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Shift, EKeys::F11) );
		UI_COMMAND(OpenWidgetReflector, "Open Widget Reflector", "Opens the Widget Reflector", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift | EModifierKey::Control , EKeys::W));
		*/

		/**
		FMaterialEditorCommands：
		UI_COMMAND( Apply, "Apply", "Apply changes to original material and its use in the world.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( Flatten, "Flatten", "Flatten the material to a texture for mobile devices.", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ShowAllMaterialParameters, "Show Inactive", "Show the material instance parameters currently hidden behind static switches.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( SetCylinderPreview, "Cylinder", "Sets the preview mesh to a cylinder primitive.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetSpherePreview, "Sphere", "Sets the preview mesh to a sphere primitive.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetPlanePreview, "Plane", "Sets the preview mesh to a plane primitive.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetCubePreview, "Cube", "Sets the preview mesh to a cube primitive.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetPreviewMeshFromSelection, "Mesh", "Sets the preview mesh based on the current content browser selection.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( TogglePreviewGrid, "Grid", "Toggles the preview pane's grid.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( TogglePreviewBackground, "Background", "Toggles the preview pane's background.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( CameraHome, "Home", "Goes home on the canvas.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CleanUnusedExpressions, "Clean Up", "Cleans up any unused Expressions.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ShowHideConnectors, "Hide Unused Connectors", "Hide unused connectors to clean up the graph view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ToggleLivePreview, "Preview Material", "Toggles real time update of the preview material.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ToggleRealtimeExpressions, "Realtime Nodes", "Nodes impacted by time-based functions such as panners, etc. will update realtime.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( AlwaysRefreshAllPreviews, "All Node Previews", "All node previews are updated upon any change to the graph.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleMaterialStats, "Stats", "Toggles displaying of the material's stats.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( TogglePlatformStats, "Platform Stats", "Toggles the window that shows material stats and compilation errors for multiple platforms.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleHideUnrelatedNodes, "Hide Unrelated", "Toggles hiding nodes which are unrelated to the selected nodes automatically.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( NewComment, "New Comment", "Creates a new comment node.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MatertialPasteHere, "Paste Here", "Pastes copied items at this location.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( UseCurrentTexture, "Use Current Texture", "Uses the current texture selected in the content browser.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertObjects, "Convert to Parameter", "Converts the objects to parameters.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( PromoteToDouble, "Promote to Double", "Converts the parameters to double precision.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( PromoteToFloat, "Promote to Float", "Converts the parameters to float precision.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ConvertToConstant, "Convert to Constant", "Converts the parameters to constants.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectNamedRerouteDeclaration, "Select Named Reroute Declaration", "Select this named reroute's declaration node.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectNamedRerouteUsages, "Select Named Reroute Usages", "Select this named reroute's usage nodes.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertRerouteToNamedReroute, "Convert to Named Reroute", "Replace this reroute with a named reroute.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertNamedRerouteToReroute, "Convert to Reroute", "Replace this named reroute with an (unnamed) reroute node.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertToTextureObjects, "Convert to Texture Object", "Converts the objects to texture objects.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertToTextureSamples, "Convert to Texture Sample", "Converts the objects to texture samples.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( StopPreviewNode, "Stop Previewing Node", "Stops the preview viewport from previewing this node", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( StartPreviewNode, "Start Previewing Node", "Makes the preview viewport start previewing this node", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( EnableRealtimePreviewNode, "Enable Realtime Preview", "Enables realtime previewing of this expression node", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DisableRealtimePreviewNode, "Disable Realtime Preview", "Disables realtime previewing of this expression node", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( BreakAllLinks, "Break All Links", "Breaks all links leading out of this node.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DuplicateObjects, "Duplicate Object(s)", "Duplicates the selected objects.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeleteObjects, "Delete Object(s)", "Deletes the selected objects.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectDownstreamNodes, "Select Downstream Nodes", "Selects all nodes that use this node's outgoing links.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectUpstreamNodes, "Select Upstream Nodes", "Selects all nodes that feed links into this node.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemoveFromFavorites, "Remove From Favorites", "Removes this expression from your favorites.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddToFavorites, "Add To Favorites", "Adds this expression to your favorites.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( BreakLink, "Break Link", "Deletes this link.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ForceRefreshPreviews, "Force Refresh Previews", "Forces a refresh of all previews", EUserInterfaceActionType::Button, FInputChord(EKeys::SpaceBar) );
		UI_COMMAND( CreateComponentMaskNode, "Create ComponentMask Node", "Creates a ComponentMask node at the current cursor position.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::C));
		UI_COMMAND( FindInMaterial, "Search", "Finds expressions and comments in the current Material", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F));
		UI_COMMAND( PromoteToParameter, "Promote to Parameter", "Promote selected Pin to parameter of pin type", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( CreateSlabNode, "Create Slab Node", "Create a Slab Node linked to the pin", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( CreateHorizontalMixNode, "Create Horizontal Mix Node", "Create a Horizontal Mix Node linked to the pin", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( CreateVerticalLayerNode, "Create Vertical Layer Node", "Create a Vertical Layer Node linked to the pin", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( CreateWeightNode, "Create Weight Node", "Create a Weight Node linked to the pin", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(QualityLevel_All, "All", "Sets node preview to show all quality levels.)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(QualityLevel_Epic, "Epic", "Sets node preview to Epic quality.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(QualityLevel_High, "High", "Sets node preview to high quality.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(QualityLevel_Medium, "Medium", "Sets node preview to medium quality.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(QualityLevel_Low, "Low", "Sets node preview to low quality.", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(FeatureLevel_All, "All", "Sets node preview to show all feature levels.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(FeatureLevel_Mobile, "Mobile", "Sets node preview to show the Mobile feature level.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(FeatureLevel_SM5, "SM5", "Sets node preview to show the SM5 feature level.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(FeatureLevel_SM6, "SM6", "Sets node preview to show the SM6 feature level.", EUserInterfaceActionType::RadioButton, FInputChord());
		*/

		/**
		FMeshPainterCommands：
		UI_COMMAND(IncreaseBrushRadius, "Increase Brush Radius", "Press this key to increase brush radius by a percentage of its current size.", EUserInterfaceActionType::Button, FInputChord(EKeys::RightBracket));
		UI_COMMAND(DecreaseBrushRadius, "Decrease Brush Size", "Press this key to decrease brush radius by a percentage of its current size.", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftBracket));
		UI_COMMAND(IncreaseBrushStrength, "Increase Brush Strength", "Press this key to increase brush strength by a fixed increment.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::RightBracket));
		UI_COMMAND(DecreaseBrushStrength, "Decrease Brush Strength", "Press this key to decrease brush strength by a fixed increment.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::LeftBracket));
		UI_COMMAND(IncreaseBrushFalloff, "Increase Brush Falloff", "Press this key to increase brush falloff by a fixed increment.", EUserInterfaceActionType::Button, FInputChord(FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::RightBracket)));
		UI_COMMAND(DecreaseBrushFalloff, "Decrease Brush Falloff", "Press this key to decrease brush falloff by a fixed increment.", EUserInterfaceActionType::Button, FInputChord(FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::LeftBracket)));
		*/

		/**
		FCameraCutTrackCommands：
		UI_COMMAND( ToggleLockCamera, "Toggle Lock Camera", "Toggle locking the viewport to the camera cut track.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::C) );
		*/

		/**
		FPListEditorCommands：
		UI_COMMAND( NewCommand, "New", "Creates a new plist file", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::N) );
		UI_COMMAND( OpenCommand, "Open", "Opens an existing plist file", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::O) );
		UI_COMMAND( SaveCommand, "Save", "Saves the current plist file", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::S) );
		UI_COMMAND( SaveAsCommand, "Save As", "Saves the current plist file to a specific location", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::S) );
		UI_COMMAND( DeleteSelectedCommand, "Remove Selected", "Removed the selected entries from the plist", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::R) );
		UI_COMMAND( MoveUpCommand, "Move Up", "Moves the selected entry up within its parent", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::U) );
		UI_COMMAND( MoveDownCommand, "Move Down", "Moves the selected entry down within its parent", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::D) );
		UI_COMMAND( AddDictionaryCommand, "Add Dictionary", "Adds a new dictionary to the selected file or array", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( AddArrayCommand, "Add Array", "Adds a new array to the selected file, array, or dictionary", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( AddStringCommand, "Add String", "Adds a new string to the selected file, array, or dictionary", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( AddBooleanCommand, "Add Boolean", "Adds a new boolean to the selected file, array, or dictionary", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FAnimSequenceCurveEditorCommands：
		UI_COMMAND(EditSelectedCurves, "Edit Selected Curves", "Edit the selected curves in the curve editor tab", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FAnimSequenceTimelineCommands：
		UI_COMMAND(PasteDataIntoCurve, "Paste Clipboard Data Into Curve", "Paste curve data from the clipboard into the selected curve", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::V));
		UI_COMMAND(EditSelectedCurves, "Edit Selected Curves", "Edit the selected curves in the curve editor tab", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddNotifyTrack, "Add Notify Track", "Add a new notify track", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(InsertNotifyTrack, "Insert Notify Track", "Insert a new notify track above here", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveNotifyTrack, "Remove Notify Track", "Remove this notify track", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddCurve, "Add Curve...", "Add a new variable float curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(EditCurve, "Edit Curve", "Edit this curve in the curve editor tab", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ShowCurveKeys, "Show Curve Keys", "Show keys for all curves in the timeline", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(AddMetadata, "Add Metadata...", "Add a new constant (metadata) float curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertCurveToMetaData, "Convert To Metadata", "Convert this curve to a constant (metadata) curve.\nThis is a destructive operation and will remove all keys from this curve.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertMetaDataToCurve, "Convert To Curve", "Convert this metadata curve to a full curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveCurve, "Remove Curve", "Remove this curve", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveAllCurves, "Remove All Curves", "Remove all the curves in this animation", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CopySelectedCurveNames, "Copy Selected Curve Names", "Copy the name of the selected curves to the clipboard", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DisplaySeconds, "Seconds", "Display the time in seconds", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DisplayFrames, "Frames", "Display the time in frames", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DisplayPercentage, "Percentage", "Display the percentage along with the time with the scrubber", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(DisplaySecondaryFormat, "Secondary", "Display the time or frame count as a secondary format along with the scrubber", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SnapToFrames, "Frames", "Snap to frame boundaries", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SnapToNotifies, "Notifies", "Snap to notifies and notify states", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SnapToMontageSections, "Montage Sections", "Snap to montage sections", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SnapToCompositeSegments, "Composite Segments", "Snap to composite segments", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		FAnimViewportLODCommands：
		UI_COMMAND( LODDebug, "LOD Debug", "Sync the LOD with the currently debugged instance", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( LODAuto, "LOD Auto", "Automatically select LOD", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( LOD0, "LOD 0", "Force select LOD 0", EUserInterfaceActionType::RadioButton, FInputChord() );
		*/

		/**
		FAnimViewportMenuCommands：
		UI_COMMAND( PreviewSceneSettings, "Preview Scene Settings...", "The Advanced Preview Settings tab will let you alter the preview scene's settings.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( CameraFollowNone, "Free Camera", "Camera is free to move.", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( CameraFollowBounds, "Orbit Bounds", "Camera orbits the bounds of the mesh.", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( CameraFollowRoot, "Orbit Root", "Camera orbits the root bone while keeping the mesh vertically centered.", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( CameraFollowBone, "Orbit Bone", "Camera focuses on a specified bone.", EUserInterfaceActionType::RadioButton, FInputChord() );
		
		UI_COMMAND( TogglePauseAnimationOnCameraMove, "Pause Animation On Camera Move", "Pause the preview animation when moving the camera and resume when finished.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( SetCPUSkinning, "CPU Skinning", "Toggles display of CPU skinning in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( SetShowNormals, "Normals", "Toggles display of vertex normals in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetShowTangents, "Tangents", "Toggles display of vertex tangents in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetShowBinormals, "Binormals", "Toggles display of vertex binormals (orthogonal vector to normal and tangent) in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( AnimSetDrawUVs, "UV", "Toggles display of the mesh's UVs for the specified channel.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND(SaveCameraAsDefault, "Save Camera As Default", "Save the current camera as default for this mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ClearDefaultCamera, "Clear Default Camera", "Clear default camera for this mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(JumpToDefaultCamera, "Jump To Default Camera", "Jump to the default camera (if set).", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::F));
		*/

		/**
		FAnimViewportPlaybackCommands：
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::OneTenth],	"x0.1", "Set the animation playback speed to a tenth of normal", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::Quarter],		"x0.25", "Set the animation playback speed to a quarter of normal", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::Half],		"x0.5", "Set the animation playback speed to a half of normal", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::ThreeQuarters],		"x0.75", "Set the animation playback speed to three quarters of normal", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::Normal],		"x1.0", "Set the animation playback speed to normal", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::Double],		"x2.0", "Set the animation playback speed to double the speed of normal", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::FiveTimes],	"x5.0", "Set the animation playback speed to five times the normal speed", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::TenTimes],	"x10.0", "Set the animation playback speed to ten times the normal speed", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( PlaybackSpeedCommands[EAnimationPlaybackSpeeds::Custom],	"xCustom", "Set the animation playback speed to assigned custom speed", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::OneTenth], "x0.1", "Set the turn table rotation speed to a tenth of normal", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::Quarter], "x0.25", "Set the turn table rotation speed to a quarter of normal", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::Half], "x0.5", "Set the turn table rotation speed to a half of normal", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::ThreeQuarters], "x0.75", "Set the turn table rotation speed to three quarters of normal", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::Normal], "x1.0", "Set the turn table rotation speed to normal", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::Double], "x2.0", "Set the turn table rotation speed to double the speed of normal", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::FiveTimes], "x5.0", "Set the turn table rotation speed to five times the normal speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::TenTimes], "x10.0", "Set the turn table rotation speed to ten times the normal speed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TurnTableSpeeds[EAnimationPlaybackSpeeds::Custom], "xCustom", "Set the animation playback speed to assigned custom speed", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(PersonaTurnTablePlay, "Play", "Turn table rotates", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PersonaTurnTablePause, "Pause", "Freeze with current rotation", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PersonaTurnTableStop, "Stop", "Stop and Reset orientation", EUserInterfaceActionType::RadioButton, FInputChord());
		*/

		/**
		FAnimViewportShowCommands：
		UI_COMMAND( AutoAlignFloorToMesh, "Auto Align Floor to Mesh", "Auto align floor to mesh bounds", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( MuteAudio, "Mute Audio", "Mute audio from the preview", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( UseAudioAttenuation, "Use Audio Attenuation", "Use audio attenuation when playing back audio in the preview", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND(DoNotProcessRootMotion, "Ignore", "Preview mesh will not consume root motion", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ProcessRootMotionLoopAndReset, "Loop and Reset", "Preview mesh will consume root motion resetting the position back to the origin every time the animation loops", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ProcessRootMotionLoop, "Loop", "Preview mesh will consume root motion continually", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(DisablePostProcessBlueprint, "Disable Post Process", "Disable the evaluation of post process animation blueprints on the preview instance.", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( ShowRetargetBasePose, "Retarget Base Pose", "Show retarget Base pose on preview mesh", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowBound, "Bound", "Show bound on preview mesh", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( UseInGameBound, "In-game Bound", "Use in-game bound on preview mesh when showing bounds. Otherwise bounds will always be calculated from bones alone.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( UseFixedBounds, "Fixed Bounds", "Preview using the 'Fixed Bounds' option, which will use bounds from skel mesh and not bones at all, for speed.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( UsePreSkinnedBounds, "Pre-skinned Bounds", "Preview using the 'Pre-skinned' option, which will use local space pre-skinned(base pose) bounds from skel mesh. Overrides all other bounds preview settings.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ShowPreviewMesh, "Mesh", "Show the preview mesh", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowMorphTargets, "Morph Targets", "Display applied morph targets of the mesh", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ShowBoneNames, "Bone Names", "Display bone names in the viewport", EUserInterfaceActionType::ToggleButton, FInputChord() );

		// below 3 menus are radio button styles
		UI_COMMAND(ShowDisplayInfoBasic, "Basic", "Display basic mesh info in the viewport", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ShowDisplayInfoDetailed, "Detailed", "Display detailed mesh info in the viewport", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ShowDisplayInfoSkelControls, "Skeletal Controls", "Display selected skeletal control info in the viewport", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(HideDisplayInfo, "None", "Hide all display info in the viewport", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND( ShowOverlayNone, "None", "Clear overlay display", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowBoneWeight, "Selected Bone Weight", "Display color overlay of the weight from selected bone in the viewport", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowMorphTargetVerts, "Selected Morph Target Vertices", "Display color overlay with the change of selected morph target in the viewport", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND( ShowRawAnimation, "Uncompressed Animation", "Display skeleton with uncompressed animation data", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowNonRetargetedAnimation, "Non-Retargeted Animation", "Display Skeleton With non-retargeted animation data", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowAdditiveBaseBones, "Additive Base", "Display skeleton in additive base pose", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowSourceRawAnimation, "Source Animation", "Display skeleton in source raw animation if you have track curves modified", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowBakedAnimation, "Baked Animation", "Display skeleton in baked raw animation if you have track curves modified", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowSockets, "Sockets", "Display socket hitpoints", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ShowAttributes, "Attributes", "Display transform attributes in the viewport", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ShowBoneDrawNone, "None", "Hide bone selection", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowBoneDrawSelected, "Selected Only", "Show only the selected bone", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowBoneDrawSelectedAndParents, "Selected and Parents", "Show the selected bone and its parents, to the root", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowBoneDrawSelectedAndChildren, "Selected and Children", "Show the selected bone and its children", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowBoneDrawSelectedAndParentsAndChildren, "Selected and Parents and Children", "Show the selected bone and its parents and children", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowBoneDrawAll, "All Hierarchy", "Show all hierarchy joints", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND( ShowLocalAxesNone, "None", "Hide all local hierarchy axis", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowLocalAxesSelected, "Selected Only", "Show only the local axes of the selected bones", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowLocalAxesAll, "All", "Show all local hierarchy axes", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( EnableClothSimulation, "Enable Cloth Simulation", "Show simulated cloth mesh", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ResetClothSimulation, "Reset Cloth Simulation", "Reset simulated cloth to its initial state", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::C) );

		UI_COMMAND( EnableCollisionWithAttachedClothChildren, "Collide with Cloth Children", "Enables collision detection between collision primitives in the base mesh and clothing on any attachments in the preview scene", EUserInterfaceActionType::ToggleButton, FInputChord() );	
		UI_COMMAND(PauseClothWithAnim, "Pause with Animation", "If enabled, the clothing simulation will pause when the animation is paused using the scrub panel", EUserInterfaceActionType::ToggleButton, FInputChord());

		// below 3 menus are radio button styles
		UI_COMMAND(ShowAllSections, "Show All Sections", "Display all sections including cloth mapped sections", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ShowOnlyClothSections, "Show Only Cloth Sections", "Display only cloth mapped sections", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(HideOnlyClothSections, "Hide Only Cloth Sections", "Display all except cloth mapped sections", EUserInterfaceActionType::RadioButton, FInputChord());
		*/

		/**
		FCurveViewerCommands：
		UI_COMMAND( AddCurve, "Add Curve", "Add a curve to the Skeleton", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FPoseEditorCommands：
		UI_COMMAND(PasteAllNames, "Paste All Pose Names", "Paste all pose names from clipboard", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(UpdatePoseToCurrent, "Update Pose to Current", "Updates the selected pose to match the pose currently shown in the viewport", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddPoseFromCurrent, "Add Pose from Current", "Adds a new pose matching the pose currently shown in the viewport", EUserInterfaceActionType::Button, FInputChord());	
		UI_COMMAND(AddPoseFromReference, "Add Pose from Reference", "Adds a new pose matching the Skeleton its reference pose", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FAnimNotifyPanelCommands：
		UI_COMMAND(DeleteNotify, "Delete", "Deletes the selected notifies.", EUserInterfaceActionType::Button, FInputChord(EKeys::Platform_Delete));
		UI_COMMAND(CopyNotifies, "Copy", "Copy animation notify events.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::C));
		UI_COMMAND(PasteNotifies, "Paste", "Paste animation notify event here.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::V));
		*/

		/**
		FAnimSegmentsPanelCommands：
		UI_COMMAND(DeleteSegment, "Delete", "Deletes the selected segment", EUserInterfaceActionType::Button, FInputChord(EKeys::Platform_Delete));
		*/

		/**
		FPersonaCommonCommands：
		UI_COMMAND(TogglePlay, "Play/Pause", "Play or pause the current animation", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::SpaceBar));
		*/

		/**
		FPhysicsAssetEditorCommands：
		UI_COMMAND(RegenerateBodies, "Regenerate Bodies", "Regenerates the selected bodies using the current generation settings (see the Tools tab)", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddBodies, "Add/Replace Bodies", "Adds or replaces bodies for the selected bones using the current generation settings (see the Tools tab)", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(ApplyPhysicalMaterial, "Physical Material", "Apply a Physical Material to All Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CopyBodies, "Copy Selected Bodies/Constraints To Clipboard", "Copy selected bodies/constraints to clipboard", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::C));
		UI_COMMAND(PasteBodies, "Paste Bodies/Constraints From Clipboard", "Paste bodies/constraints from clipboard", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::V));
		UI_COMMAND(CopyShapes, "Copy Selected Shapes To Clipboard", "Copy selected shapes to clipboard", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PasteShapes, "Paste Selected Shapes From Clipboard", "Paste shapes from clipboard to selected bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CopyProperties, "Copy Properties", "Copy Properties: Copy Properties Of Currently Selected Object To Next Selected Object", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::C));
		UI_COMMAND(PasteProperties, "Paste Properties", "Paste Properties: Copy Properties Of Currently Selected Object To Next Selected Object", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::V));
		UI_COMMAND(RepeatLastSimulation, "Simulate", "Previews Physics Simulation", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(SimulationNoGravity, "No Gravity Simulation", "Run Physics Simulation without gravity. Use this to debug issues with your ragdoll. If the setup is correct, the asset should not move!", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SimulationFloorCollision, "Enable Floor Collisions", "Run Physics Simulation with collisions between physics bodies and the floor enabled.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SelectedSimulation, "Simulate Selected", "Run Physics Simulation on selected objects. Use this to tune  specific parts of your ragdoll.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Alt | EModifierKey::Shift, EKeys::I));
		UI_COMMAND(SimulationAll, "Simulate", "Run Physics Simulation on all objects.", EUserInterfaceActionType::RadioButton, FInputChord(EModifierKey::Alt, EKeys::I));

		UI_COMMAND(MeshRenderingMode_Solid, "Solid", "Solid Mesh Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MeshRenderingMode_Wireframe, "Wireframe", "Wireframe Mesh Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MeshRenderingMode_None, "None", "No Mesh Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_Solid, "Solid", "Solid Collision Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_Wireframe, "Wireframe", "Wireframe Collision Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_SolidWireframe, "Solid + Wireframe", "Solid + Wireframe Collision Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_None, "None", "No Collision Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ConstraintRenderingMode_None, "None", "No Constraint Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ConstraintRenderingMode_AllPositions, "All Positions", "All Positions Constraint Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ConstraintRenderingMode_AllLimits, "All Limits", "All Limits Constraint Rendering Mode (Edit)", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(MeshRenderingMode_Simulation_Solid, "Solid", "Solid Mesh Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MeshRenderingMode_Simulation_Wireframe, "Wireframe", "Wireframe Mesh Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MeshRenderingMode_Simulation_None, "None", "No Mesh Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_Simulation_Solid, "Solid", "Solid Collision Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_Simulation_Wireframe, "Wireframe", "Wireframe Collision Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_Simulation_SolidWireframe, "Solid + Wireframe", "Solid + Wireframe Collision Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CollisionRenderingMode_Simulation_None, "None", "No Collision Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ConstraintRenderingMode_Simulation_None, "None", "No Constraint Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ConstraintRenderingMode_Simulation_AllPositions, "All Positions", "All Positions Constraint Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(ConstraintRenderingMode_Simulation_AllLimits, "All Limits", "All Limits Constraint Rendering Mode (Simulation)", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(RenderOnlySelectedSolid, "Only Selected Solid", "Only render selected collision as 'solid'", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(HideSimulatedBodies, "Hide Simulated Bodies", "Hide rendering for simulated bodies", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(HideKinematicBodies, "Hide Kinematic Bodies", "Hide rendering for kinematic bodies", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(RenderOnlySelectedConstraints, "Only Selected Constraints", "Draw only selected constraints.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(DrawConstraintsAsPoints, "Draw Constraints As Points", "Draw Constraints As Points", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleMassProperties, "Mass Properties", "Show Mass Properties For Bodies When Simulation Is Enabled", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(DisableCollision, "Disable Collision", "Disable collision between the currently selected bodies", EUserInterfaceActionType::Button, FInputChord(EKeys::RightBracket));
		UI_COMMAND(DisableCollisionAll, "Disable Collision All", "Disable collision between the currently selected bodies and all bodies", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::RightBracket));
		UI_COMMAND(EnableCollision, "Enable Collision", "Enable collision between the currently selected bodies", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftBracket));
		UI_COMMAND(EnableCollisionAll, "Enable Collision All", "Enable collision between the currently selected bodies and all bodies", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::LeftBracket));
		UI_COMMAND(WeldToBody, "Weld", "Weld Body: Weld Currently Selected Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddSphere, "Add Sphere", "Add Sphere To Selected Bone", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::One));
		UI_COMMAND(AddSphyl, "Add Capsule", "Add Capsule To Selected Bone", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Two));
		UI_COMMAND(AddBox, "Add Box", "Add Box To Selected Bone", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Three));
		UI_COMMAND(AddTaperedCapsule, "Add Tapered Capsule (Clothing Only)", "Add Tapered Capsule To Selected Bone. This is only used by clothing, so will have no effect on rigid body collision, overlaps or bounds.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Four));
		UI_COMMAND(DeletePrimitive, "Delete", "Delete Selected Primitive(s)", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PrimitiveQueryAndPhysics, "Query and Physics", "Enable all collision on selected primitive(s)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PrimitiveQueryAndProbe, "Query and Probe", "Enable query and probe collision on selected primitive(s)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PrimitiveQueryOnly, "Query Only", "Enable query collision only on selected primitive(s)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PrimitivePhysicsOnly, "Physics Only", "Enable physics collision only on selected primitive(s)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PrimitiveProbeOnly, "Probe Only", "Enable probe collision only on selected primitive(s)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PrimitiveNoCollision, "No Collision", "Disable all collision on Selected primitive(s)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PrimitiveContributeToMass, "Primitive Contributes To Mass", "Toggle the contribution of selected primitive's volume to the overall mass of the body", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(DuplicatePrimitive, "Duplicate", "Duplicate Selected Primitive(s)", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConstrainChildBodiesToParentBody, "Constrain selected bodies", "Create a constraint between all selected bodies as children and the last selected body as parent", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Y));
		UI_COMMAND(ResetConstraint, "Reset", "Reset Constraint", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::P));
		UI_COMMAND(SnapConstraint, "Snap All Transforms", "Snap Constraint Transforms To Bone", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::P));
		UI_COMMAND(SnapConstraintChildPosition, "Snap Child Position", "Snap Constraint Child Positions To Bone", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapConstraintChildOrientation, "Snap Child Rotation", "Snap Constraint Child Rotations To Bone", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapConstraintParentPosition, "Snap Parent Position", "Snap Constraint Parent Positions To Bone", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SnapConstraintParentOrientation, "Snap Parent Rotation", "Snap Constraint Parent Rotations To Bone", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertToBallAndSocket, "To Ball & Socket", "Convert Selected Constraint To Ball-And-Socket", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertToHinge, "To Hinge", "Convert Selected Constraint To Hinge", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertToPrismatic, "To Prismatic", "Convert Selected Constraint To Prismatic", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertToSkeletal, "To Skeletal", "Convert Selected Constraint To Skeletal", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteConstraint, "Delete", "Delete Selected Constraint", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ShowSkeleton, "Skeleton", "Show Skeleton", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(MakeBodyKinematic, "Kinematic", "Make Body Kinematic", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MakeBodySimulated, "Simulated", "Make Body Simulated", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(MakeBodyDefault, "Default", "Reset This Body To Default", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(KinematicAllBodiesBelow, "Set All Bodies Below To Kinematic", "Set All Bodies Below To Kinematic", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SimulatedAllBodiesBelow, "Set All Bodies Below To Simulated", "Set All Bodies Below To Simulated", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(MakeAllBodiesBelowDefault, "Reset All Bodies Below To Default", "Reset All Bodies Below To Default", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteBody, "Delete", "Delete Selected Body", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteAllBodiesBelow, "Delete All Bodies Below", "Delete All Bodies Below", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectAllBodies, "Select All Bodies", "Select All Bodies", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::A));
		UI_COMMAND(SelectSimulatedBodies, "Select Simulated Bodies", "Select Simulated Bodies", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::J));
		UI_COMMAND(SelectKinematicBodies, "Select Kinematic Bodies", "Select Kinematic Bodies", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::K));
		UI_COMMAND(SelectShapesQueryOnly, "Select QueryOnly Shapes", "Select Kinematic Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectShapesQueryAndPhysics, "Select QueryAndPhysics Shapes", "Select Kinematic Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectShapesPhysicsOnly, "Select PhysicsOnly Shapes", "Select Kinematic Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectShapesQueryAndProbe, "Select QueryAndProbe Shapes", "Select Kinematic Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectShapesProbeOnly, "Select ProbeOnly Shapes", "Select Kinematic Bodies", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectAllConstraints, "Select All Constraints", "Select All Constraints", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::A));
		UI_COMMAND(ToggleSelectionType, "Toggle Selection Type", "Select bodies from constraints, or constraints from bodies, depending on selection.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::T));
		UI_COMMAND(ToggleSelectionTypeWithUserConstraints, "Toggle Selection Type (With User Constraints)", "Select bodies from constraints, or constraints from bodies, depending on selection (account for user constraints).", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::T));
		UI_COMMAND(ToggleShowSelected, "Toggle Show Selected", "Show/hide selected bodies/constraints.", EUserInterfaceActionType::Button, FInputChord(EKeys::H));
		UI_COMMAND(ShowSelected, "Show Selected", "Show selected bodies/constraints.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::H));
		UI_COMMAND(HideSelected, "Hide Selected", "Hide selected bodies/constraints.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::H));
		UI_COMMAND(ToggleShowOnlyColliding, "Toggle Isolate Colliding Bodies", "Show only the selected body and the ones that can collide with it, hiding all others or Show all.", EUserInterfaceActionType::Button, FInputChord(EKeys::C));
		UI_COMMAND(ToggleShowOnlyConstrained, "Toggle Isolate Constrained Bodies", "Show only the selected body and the ones that are joint constrained to it, also works from constraints, hiding all others or Show all.", EUserInterfaceActionType::Button, FInputChord(EKeys::J));
		UI_COMMAND(ToggleShowOnlySelected, "Toggle Isolate Selected", "Show the selected bodies/constraints, hiding all others, or Show all.", EUserInterfaceActionType::Button, FInputChord(EKeys::G));
		UI_COMMAND(ShowAll, "Show All", "Show all bodies/constraints.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::G));
		UI_COMMAND(HideAll, "Hide All", "Hide all bodies/constraints.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::G));
		UI_COMMAND(DeselectAll, "Deselect All Bodies", "Deselect All", EUserInterfaceActionType::Button, FInputChord(EKeys::Escape));
		UI_COMMAND(Mirror, "Mirror", "Finds the body on the other side and duplicates constraint and body", EUserInterfaceActionType::Button, FInputChord(EKeys::M));

		UI_COMMAND(NewPhysicalAnimationProfile, "New", "Creates a new physical animation profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DuplicatePhysicalAnimationProfile, "Duplicate", "Duplicates the current physical animation profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteCurrentPhysicalAnimationProfile, "Delete", "Deletes the current physical animation profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddBodyToPhysicalAnimationProfile, "Assign", "Assigns the selected bodies to the current physical animation profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectAllBodiesInCurrentPhysicalAnimationProfile, "Select All Bodies", "Select all bodies that are assigned to the current physical animation profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveBodyFromPhysicalAnimationProfile, "Unassign", "Unassigns the selected bodies from the current physical animation profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(NewConstraintProfile, "New", "Creates a new constraint profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DuplicateConstraintProfile, "Duplicate", "Duplicates the current constraint profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DeleteCurrentConstraintProfile, "Delete", "Deletes the current constraint profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddConstraintToCurrentConstraintProfile, "Assign", "Assigns the selected constraints to the current constraint profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveConstraintFromCurrentConstraintProfile, "Unassign", "Unassigns the selected constraints from the current constraint profile", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SelectAllBodiesInCurrentConstraintProfile, "Select All Bodies", "Select all bodies that are assigned to the current constraint profile", EUserInterfaceActionType::Button, FInputChord());
		
		UI_COMMAND(ShowBodies, "Show Bodies", "Display bodies in the tree view. Bodies are a collection of primitive shapes used for collision.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ShowSimulatedBodies, "Show Simulated Bodies", "Display simulated bodies in the tree view. Bodies are a collection of primitive shapes used for collision.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ShowKinematicBodies, "Show Kinematic Bodies", "Display kinematic bodies in the tree view. Bodies are a collection of primitive shapes used for collision.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ShowConstraints, "Show Constraints", "Display constraints in the tree view. Constraints are used to control how bodies can move in relation to one another.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ShowConstraintsOnParentBodies, "Show Constraints on Parent Bodies", "When showing constraints, display them on bothe the parent and the child body.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ShowPrimitives, "Show Primitives", "Display primitive shapes (sphere, boxes, capsules etc.) in the tree view", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(DeleteSelected, "Delete selected primitive or constraint", "", EUserInterfaceActionType::Button, FInputChord(EKeys::Platform_Delete));
		UI_COMMAND(CycleConstraintOrientation, "Cycle Constraint Orientation", "Cycles constraint orientation between different cardinal axes", EUserInterfaceActionType::Button, FInputChord(EKeys::Q));
		UI_COMMAND(CycleConstraintActive, "Cycle Active Constraint", "Cycles whether each constraint axis is active in isolation", EUserInterfaceActionType::Button, FInputChord(EKeys::Four));
		UI_COMMAND(ToggleSwing1, "Lock Swing 1", "Set swing 1 to be locked or limited", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::One));
		UI_COMMAND(ToggleSwing2, "Lock Swing 2", "Set swing 2 to be locked or limited", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Two));
		UI_COMMAND(ToggleTwist, "Lock Twist", "Set twist to be locked or limited", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Three));
		UI_COMMAND(FocusOnSelection, "Focus the viewport on the current selection", "", EUserInterfaceActionType::Button, FInputChord(EKeys::F));
		*/

		/**
		FContextMenuCommands：
		UI_COMMAND(Command_FindInContentBrowser,"Browse to Asset", "Browses to the associated asset and selects it in the most recently used Content Browser (summoning one if necessary)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::B));
		*/

		/**
		FSequenceRecorderCommands：
		UI_COMMAND(RecordAll, "Record", "Record all recordings", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::R));
		UI_COMMAND(StopAll, "StopAll", "Stop all recordings", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::S));
		UI_COMMAND(AddRecording, "Add", "Add a new recording for selected actors. If nothing selected, an empty recording will be added", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddCurrentPlayerRecording, "Add Player", "Add a new recording for the current player.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveRecording, "Remove", "Remove selected recording", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveAllRecordings, "Remove All", "Remove all recordings", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AddRecordingGroup, "Add Group", "Adds a new group for Actor recordings to be stored with", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveRecordingGroup, "Remove Group", "Removes the currently selected recording group", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(DuplicateRecordingGroup, "Duplicate Group", "Duplicates the current recording group", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FSequencerCommands：
		UI_COMMAND( TogglePlay, "Toggle Play", "Toggle the timeline playing", EUserInterfaceActionType::Button, FInputChord(EKeys::SpaceBar) );
		UI_COMMAND( TogglePlayViewport, "Toggle Play (Viewport)", "Toggle the timeline playing in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::SpaceBar));
		UI_COMMAND( ScrubTimeViewport, "Scrub Time (Viewport)", "Scrub mouse left and right to change time", EUserInterfaceActionType::Button, FInputChord(EKeys::B) );
		UI_COMMAND( PlayForward, "Play Forward", "Play the timeline forward", EUserInterfaceActionType::Button, FInputChord(EKeys::Down) );
		UI_COMMAND( JumpToStart, "Jump to Start", "Jump to the start of the playback range", EUserInterfaceActionType::Button, FInputChord(EKeys::Up) );
		UI_COMMAND( JumpToEnd, "Jump to End", "Jump to the end of the playback range", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Up) );
		UI_COMMAND( JumpToStartViewport, "Jump to Start (Viewport)", "Jump to the start of the playback range in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( JumpToEndViewport, "Jump to End (Viewport)", "Jump to the end of the playback range in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ShuttleBackward, "Shuttle Backward", "Shuttle backward", EUserInterfaceActionType::Button, FInputChord(EKeys::J) );
		UI_COMMAND( ShuttleForward, "Shuttle Forward", "Shuttle forward", EUserInterfaceActionType::Button, FInputChord(EKeys::L) );
		UI_COMMAND( Pause, "Pause", "Pause playback", EUserInterfaceActionType::Button, FInputChord(EKeys::K) );
		UI_COMMAND( RestorePlaybackSpeed, "Restore Speed", "Restores the playback speed to 1.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( StepForward, "Step Forward", "Step the timeline forward", EUserInterfaceActionType::Button, FInputChord(EKeys::Right) );
		UI_COMMAND( StepBackward, "Step Backward", "Step the timeline backward", EUserInterfaceActionType::Button, FInputChord(EKeys::Left) );
		UI_COMMAND( StepForwardViewport, "Step Forward (Viewport)", "Step the timeline forward in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::Period) );
		UI_COMMAND( StepBackwardViewport, "Step Backward (Viewport)", "Step the timeline backward in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::Comma) );
		UI_COMMAND( JumpForward, "Jump Forward", "Jump the timeline forward a user defined number of frames/times", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Right) );
		UI_COMMAND( JumpBackward, "Jump Backward", "Jump the timeline backward a user defined number of frames/times", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Left) );
		UI_COMMAND( StepToNextKey, "Step to Next Key (Viewport)", "Step to the next key in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord(EKeys::Period) );
		UI_COMMAND( StepToPreviousKey, "Step to Previous Key (Viewport)", "Step to the previous key in all viewports and sequencer", EUserInterfaceActionType::Button, FInputChord(EKeys::Comma) );
		UI_COMMAND( StepToNextCameraKey, "Step to Next Camera Key", "Step to the next camera key", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( StepToPreviousCameraKey, "Step to Previous Camera Key", "Step to the previous camera key", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( StepToNextShot, "Step to Next Shot", "Step to the next shot", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Period) );
		UI_COMMAND( StepToPreviousShot, "Step to Previous Shot", "Step to the previous shot", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::Comma) );
		UI_COMMAND( SetStartPlaybackRange, "Set Start Playback Range", "Set the start playback range", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftBracket) );
		UI_COMMAND( SetEndPlaybackRange, "Set End Playback Range", "Set the end playback range", EUserInterfaceActionType::Button, FInputChord(EKeys::RightBracket) );
		UI_COMMAND( ResetViewRange, "Reset View Range", "Reset view range to the playback range", EUserInterfaceActionType::Button, FInputChord(EKeys::Home) );
		UI_COMMAND( ZoomToFit, "Zoom to Fit", "Zoom to Fit", EUserInterfaceActionType::Button, FInputChord(EKeys::F) );
		UI_COMMAND( ZoomInViewRange, "Zoom into the View Range", "Zoom into the view range", EUserInterfaceActionType::Button, FInputChord(EKeys::Equals) );
		UI_COMMAND( ZoomOutViewRange, "Zoom out of the View Range", "Zoom out of the view range", EUserInterfaceActionType::Button, FInputChord(EKeys::Hyphen) );
		UI_COMMAND( NavigateBackward, "Navigate Backward", "Go backward to the previously viewed shot/subsequence", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::Left));
		UI_COMMAND( NavigateForward, "Navigate Forward", "Go forward to the previously viewed shot/subsequence", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::Right));

		UI_COMMAND( SetSelectionRangeToNextShot, "Set Selection Range to Next Shot", "Set the selection range to the next shot", EUserInterfaceActionType::Button, FInputChord(EKeys::PageUp) );
		UI_COMMAND( SetSelectionRangeToPreviousShot, "Set Selection Range to Previous Shot", "Set the selection range to the previous shot", EUserInterfaceActionType::Button, FInputChord(EKeys::PageDown) );
		UI_COMMAND( SetPlaybackRangeToAllShots, "Set Playback Range to All Shots", "Set the playback range to all the shots", EUserInterfaceActionType::Button, FInputChord(EKeys::End) );

		UI_COMMAND( TogglePlaybackRangeLocked, "Playback Range Locked", "Prevent editing the start and end times for the sequence.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleCleanPlaybackMode, "Game View (Clean Playback Mode)", "Enable game view and hide viewport buttons while playing.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleRerunConstructionScripts, "Rerun Construction Scripts", "Rerun construction scripts on bound actors every frame.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleAsyncEvaluation, "Async Evaluation", "When enabled, enables a single asynchronous evaluation once per-frame. When disabled, forces a full blocking evaluation every time this sequence is evaluated (should be avoided for real-time content).", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleDynamicWeighting, "Dynamic Weighting", "When enabled, all blendable tracks will cache their initial values to ensure that they are able to correctly blend in/out when dynamic weights are being used.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleResetPlayheadWhenNavigating, "Reset Playhead When Navigating", "When checked, if the playhead is outside the playback range, it will be reset to the beginning when navigating in and out of subsequences", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ToggleKeepCursorInPlaybackRangeWhileScrubbing, "Keep Playhead in Playback Range While Scrubbing", "When checked, the playhead will be constrained to the current playback range while scrubbing", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleKeepPlaybackRangeInSectionBounds, "Keep Playback Range in Section Bounds", "When checked, the playback range will be synchronized to the section bounds", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleAutoExpandNodesOnSelection, "Auto Expand Nodes on Selection", "Toggle auto expanding the outliner tree on child selection", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ToggleExpandCollapseNodes, "Expand/Collapse Nodes", "Toggle expand or collapse selected nodes", EUserInterfaceActionType::Button, FInputChord(EKeys::V) );
		UI_COMMAND( ToggleExpandCollapseNodesAndDescendants, "Expand/Collapse Nodes and Descendants", "Toggle expand or collapse selected nodes and descendants", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::V) );
		UI_COMMAND( ExpandAllNodes, "Expand All Nodes", "Expand all nodes and descendants", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CollapseAllNodes, "Collapse All Nodes", "Collapse all nodes and descendants", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SortAllNodesAndDescendants, "Sort All Nodes", "Sorts all nodes by type and then alphabetically.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ResetFilters, "Reset Filters", "Reset all enabled filters.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND( SetSelectionRangeEnd, "Set Selection End", "Sets the end of the selection range", EUserInterfaceActionType::Button, FInputChord(EKeys::O) );
		UI_COMMAND( SetSelectionRangeStart, "Set Selection Start", "Sets the start of the selection range", EUserInterfaceActionType::Button, FInputChord(EKeys::I) );
		UI_COMMAND( ClearSelectionRange, "Clear Selection Range", "Clear the selection range", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::X) );
		UI_COMMAND( SelectKeysInSelectionRange, "Select Keys in Selection Range", "Select all keys that fall into the selection range", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectSectionsInSelectionRange, "Select Sections in Selection Range", "Select all sections that fall into the selection range", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectAllInSelectionRange, "Select All in Selection Range", "Select all keys and section that fall into the selection range", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SelectForward, "Select All Keys and Sections Forward", "Select all keys and sections forward from the current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::RightBracket) );
		UI_COMMAND( SelectBackward, "Select All Keys and Sections Backward", "Select all keys and sections backward from the current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::LeftBracket) );
		UI_COMMAND( SelectNone, "Select None", "Select none", EUserInterfaceActionType::Button, FInputChord(EKeys::Escape));

		UI_COMMAND( AddActorsToSequencer, "Add Actors", "Add actors to sequencer", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::A) );
		UI_COMMAND( SetKey, "Set Key", "Sets a key on the selected tracks", EUserInterfaceActionType::Button, FInputChord(EKeys::Enter) );
		UI_COMMAND(SetInterpolationCubicSmartAuto, "Set Key Smart Auto", "Cubic interpolation - Smart Automatic tangents", EUserInterfaceActionType::Button, FInputChord(EKeys::Zero));
		UI_COMMAND( SetInterpolationCubicAuto, "Set Key Auto", "Cubic interpolation - Automatic tangents", EUserInterfaceActionType::Button, FInputChord(EKeys::One));
		UI_COMMAND( SetInterpolationCubicUser, "Set Key User", "Cubic interpolation - User flat tangents", EUserInterfaceActionType::Button, FInputChord(EKeys::Two));
		UI_COMMAND( SetInterpolationCubicBreak, "Set Key Break", "Cubic interpolation - User broken tangents", EUserInterfaceActionType::Button, FInputChord(EKeys::Three));

		UI_COMMAND( SetInterpolationLinear, "Set Key Linear", "Linear interpolation", EUserInterfaceActionType::Button, FInputChord(EKeys::Four));
		UI_COMMAND( SetInterpolationConstant, "Set Key Constant", "Constant interpolation", EUserInterfaceActionType::Button, FInputChord(EKeys::Five));

		UI_COMMAND( ToggleWeightedTangents, "Toggle Weighted Tangents", "Toggles cubic tangents to be weighted/non-weighted", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( TrimSectionLeft, "Trim Section Left", "Trim section at current time to the left (keeps the right)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Comma) );
		UI_COMMAND( TrimSectionRight, "Trim Section Right", "Trim section at current time to the right (keeps the left)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Period) );
		UI_COMMAND( TrimOrExtendSectionLeft, "Trim or Extend Section Left", "Trim or extend closest sections to the left for the selected tracks (or all tracks if none selected) to the current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::LeftBracket) );
		UI_COMMAND( TrimOrExtendSectionRight, "Trim or Extend Section Right", "Trim or extend closest sections to the right for the selected tracks (or all tracks if none selected) to the current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::RightBracket) );
		UI_COMMAND( SplitSection, "Split Section", "Split section at current time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Slash) );

		UI_COMMAND( TranslateLeft, "Translate Left", "Translate selected keys and sections to the left", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Left) );
		UI_COMMAND( TranslateRight, "Translate Right", "Translate selected keys and sections to the right", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Right) );

		UI_COMMAND( SetAutoKey, "Auto-key", "Create a key when channels/properties change. Only automatically adds a key when there's already a track and at least one key.", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SetAutoTrack, "Auto-track", "Create a track when channels/properties change.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( SetAutoChangeAll, "All", "Create a key and a track if it doesn't exist when channels/properties change.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( SetAutoChangeNone, "None", "Disable auto-keying and auto-tracking.", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( AllowAllEdits, "Allow All Edits", "Allow any edits to occur, some of which may produce tracks/keys or modify default properties.", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( AllowSequencerEditsOnly, "Allow Sequencer Edits Only", "All edits will produce either a track or a key.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( AllowLevelEditsOnly, "Allow Level Edits Only", "Properties in the details panel will be disabled if they have a track.", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(ToggleAutoKeyEnabled, "Auto-key", "Create a key when channels/properties change. Only automatically adds a key when there's already a track and at least one key.", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( SetKeyChanged, "Key Changed", "Key just the changed channel when it changes.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( SetKeyGroup, "Key Group", "Key the groups channels/properties when only one of them changes. ie. Keys all three translation channels when only translation Y changes", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( SetKeyAll, "Key All", "Key all channels/properties when only one of them changes. ie. Keys all translation, rotation, scale channels when only translation Y changes", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND( ToggleMarkAtPlayPosition, "Toggle Mark", "Sets or clears a mark at the current play position.", EUserInterfaceActionType::Button, FInputChord(EKeys::M) );
		UI_COMMAND( StepToNextMark, "Step to Next Marked Frame", "Step to the next marked frame", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::Period) );
		UI_COMMAND( StepToPreviousMark, "Step to Previous Marked Frame", "Step to the previous marked frame", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::Comma) );
		UI_COMMAND( ToggleMarksLocked, "Marked Frames Locked", "Prevent editing the marked frames.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleAutoScroll, "Auto Scroll", "Toggle auto-scroll: When enabled, automatically scrolls the sequencer view to keep the current time visible", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Shift, EKeys::S) );

		UI_COMMAND( ChangeTimeDisplayFormat, "Change Time Display Format", "Rotates through supported display formats for time", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control|EModifierKey::Shift, EKeys::T) );
		UI_COMMAND( ToggleShowGotoBox, "Go to Time...", "Go to a particular point on the timeline", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::T) );
		UI_COMMAND( ToggleShowTransformBox, "Transform Selection...", "Transform the selected keys and sections by a given amount", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::M));
		UI_COMMAND( ToggleShowStretchBox, "Stretch/Shrink...", "Stretch or shrink a given amount, moving keys forwards/backwards as necessary", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenDirectorBlueprint, "Open Director Blueprint", "Opens the director blueprint for this sequence.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenTaggedBindingManager, "Open Binding Tag Manager", "Specifies options for tagging bindings within this sequence for external systems to reference as a persistent name.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenNodeGroupsManager, "Open Sequencer Group Manager", "Manage groups within this sequence.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ToggleShowRangeSlider, "Range Slider", "Enables and disables showing the time range slider", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ToggleShowStatusBar, "Status Bar", "Enables and disables showing the status bar", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ToggleIsSnapEnabled, "Enable Snapping", "Enables and disables snapping", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleSnapKeyTimesToInterval, "Snap to the Interval", "Snap keys to the time snapping interval", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapKeyTimesToKeys, "Snap to Keys and Sections", "Snap keys to other keys and sections in this sequence", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleSnapSectionTimesToInterval, "Snap to the Interval", "Snap sections to the time snapping interval", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapSectionTimesToSections, "Snap to Keys and Sections", "Snap sections to other keys and sections in this sequence", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapKeysAndSectionsToPlayRange, "Snap Keys and Sections to the Playback Range", "When checked, keys and sections will be snapped to the playback range bounds", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( ToggleSnapPlayTimeToKeys, "Snap to Keys While Scrubbing", "Snap the playhead to keys of the selected track while scrubbing", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapPlayTimeToSections, "Snap to Sections While Scrubbing", "Snap the playhead to section bounds while scrubbing", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapPlayTimeToMarkers, "Snap to Markers While Scrubbing", "Snap the playhead to markers while scrubbing", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapPlayTimeToInterval, "Snap to the Interval While Scrubbing", "Snap the playhead to the time snapping interval while scrubbing", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapPlayTimeToPressedKey, "Snap to the Pressed Key", "Snap the playhead to the pressed key", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleSnapPlayTimeToDraggedKey, "Snap to the Dragged Key", "Snap the playhead to the dragged key", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleSnapCurveValueToInterval, "Snap Curve Key Values", "Snap curve keys to the value snapping interval", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( FindInContentBrowser, "Find in Content Browser", "Find the viewed sequence asset in the content browser", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ToggleLayerBars, "Layer Bars", "Show/hide the layer bars to edit keyframes in bulk", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleKeyBars, "Key Bars", "Show/hide key bar connectors for quickly retiming pairs of keys", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleChannelColors, "Channel Colors", "Show/hide the channel colors for the key bars", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleShowSelectedNodesOnly, "Selected Nodes Only", "Show selected nodes only", EUserInterfaceActionType::ToggleButton, FInputChord() );
		
		UI_COMMAND( ToggleShowCurveEditor, "Curve Editor", "Show the animation keys in a curve editor", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleLinkCurveEditorTimeRange, "Link Curve Editor Time Range", "Link the curve editor time range to the sequence", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleShowPreAndPostRoll, "Pre/Post Roll", "Toggles visualization of pre and post roll", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( RenderMovie, "Render Movie", "Render this movie to a video, or image frame sequence", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateCamera, "Create Camera", "Create a new camera and set it as the current camera cut", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( PasteFromHistory, "Paste From History", "Paste from the sequencer clipboard history", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::V) );

		UI_COMMAND( ConvertToSpawnable, "Convert to Spawnable", "Make the specified possessed objects spawnable from sequencer. This will allow sequencer to have control over the lifetime of the object.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertToPossessable, "Convert to Possessable", "Make the specified spawned objects possessed by sequencer.", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( SaveCurrentSpawnableState, "Save Default State", "Save the current state of this spawnable object as its default properties.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RestoreAnimatedState, "Restore Pre-Animated State", "Restore any objects that have been animated by sequencer back to their original state.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::R) );

		UI_COMMAND( FixPossessableObjectClass, "Fix Possessable Object Class", "Try to automatically fix up possessables whose object class don't match the object class of their currently bound objects.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RebindPossessableReferences, "Rebind Possesable References", "Rebinds all possessables in the current sequence to ensure they're using the most robust referencing mechanism.", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ToggleEvaluateSubSequencesInIsolation, "Evaluate Sub Sequences In Isolation", "When enabled, will only evaluate the currently focused sequence; otherwise evaluate from the root sequence.", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( QuickTreeSearch, "Quick Tree Search", "Jumps keyboard focus to the tree searchbox to allow searching for tracks in the current Sequence.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::F));
		
		UI_COMMAND( MoveToNewFolder, "Move to New Folder", "Move selected nodes to new folder", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::G));
		UI_COMMAND( RemoveFromFolder, "Remove from Folder", "Remove selected nodes from their folders", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::G));

		UI_COMMAND(AddTransformKey, "Add Transform Key", "Add a transform key at the current time for the selected actor.", EUserInterfaceActionType::Button, FInputChord(EKeys::S));
		UI_COMMAND(AddTranslationKey, "Add Translation Key", "Add a translation key at the current time for the selected actor.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::W));
		UI_COMMAND(AddRotationKey, "Add Rotation Key", "Add a rotation key at the current time for the selected actor.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::E));
		UI_COMMAND(AddScaleKey, "Add Scale Key", "Add a scale key at the current time for the selected actor.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::R));

		UI_COMMAND( SetKeyTime, "Set Key Time", "Set the key to a specified time", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( Rekey, "Rekey", "Set the selected key's time to the current time", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SnapToFrame, "Snap To Frame", "Snap selected keys to frame", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeleteKeys, "Delete Keys", "Deletes the selected keys", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND(TogglePilotCamera, "Pilot Camera", "Toggle piloting the last camera or the camera cut camera.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Shift, EKeys::P));

		UI_COMMAND(RefreshUI, "Refresh UI", "Forcibly refresh the UI from source data.", EUserInterfaceActionType::Button, FInputChord(EKeys::F5));
		*/

		/**
		FSequencerTrackFilter_AnimatedCommands：
		UI_COMMAND(ToggleAnimatedTracks, "Animated Tracks", "Toggle the filter for Animated Tracks.", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::U));
		*/

		/**
		FSkeletalMeshEditorCommands：
		UI_COMMAND(ReimportMesh, "Reimport Base Mesh", "Reimport the base mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportMeshWithNewFile, "Reimport Base Mesh With New File", "Reimport the base mesh using a new source file.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportAllMesh, "Reimport Base Mesh + LODs", "Reimport the base mesh and all the custom LODs.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportAllMeshWithNewFile, "Reimport Base Mesh + LODs With New File", "Reimport the base mesh using a new source file and all the custom LODs (No new source file for LODs).", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(BakeMaterials, "Bake Out Materials", "Bake out Materials for given LOD(s).", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FSkeletonEditorCommands：
		UI_COMMAND(ChangeSkeletonPreviewMesh, "Set Preview Mesh as Default", "Changes the skeletons default preview mesh to the current open preview mesh. The skeleton will require saving after this action.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveUnusedBones, "Remove Unused Bones from Skeleton", "Removes any bones from the skeleton that are not used by any of its meshes. The skeleton and associated animations will require saving after this action.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(TestSkeletonCurveMetaDataForUse, "Test Skeleton Curve Metadata for Use", "Iterates over all Animations and Meshes for this skeleton to look for unused morph/material curves", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AnimNotifyWindow, "Anim Notifies", "You can manage animation notifies that belong to the skeleton.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RetargetManager, "Retarget Manager", "Manager retarget setups. ", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ImportMesh, "Import Mesh", "Import new mesh for this skeleton. ", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(UpdateSkeletonRefPose, "Update Skeleton RefPose", "Update Skeleton ref pose based on current preview mesh", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FSkeletonTreeCommands：
		UI_COMMAND( ShowAllBones, "Show All Bones", "Show every bone in the skeleton", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowMeshBones, "Show Mesh Bones", "Show bones that are used in the mesh", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowLODBones, "Show LOD Bones", "Show bones that are used in the LOD displayed", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( ShowWeightedBones, "Show Weighted Bones", "Show bones that have vertices weighted to them", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( HideBones, "Hide Bones", "Hides all bones (sockets and attached assets will still be listed)", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowRetargeting, "Show Retargeting Options", "Show retargeting options for each bone.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ShowDebugVisualization, "Show Debug Visualization Options", "Show debug visualization options for objects in the viewport", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( FilteringFlattensHierarchy, "Filtering Flattens Hierarchy", "Whether to keep the hierarchy or flatten it when searching for tree items", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( HideParentsWhenFiltering, "Hide Parents When Filtering", "Whether to show parent items grayed out, or hide them entirely when filtering", EUserInterfaceActionType::ToggleButton, FInputChord());
		
		UI_COMMAND( CopyBoneNames, "Copy Selected Bone Names", "Copy selected bone names to clipboard", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ResetBoneTransforms, "Reset Selected Bone Transforms", "Reset the transforms of the selected bones", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CopySockets, "Copy Selected Sockets", "Copy selected sockets to clipboard", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::C ) );
		UI_COMMAND( PasteSockets, "Paste Sockets", "Paste sockets from clipboard (try to add them to the original copy bone or root if that bone is not available)", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::V ) );
		UI_COMMAND( PasteSocketsToSelectedBone, "Paste Sockets To Selected Bone", "Paste sockets from clipboard to selected bone", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::V));

		UI_COMMAND( AddSocket, "Add Socket", "Add a socket to this bone in the skeleton (disabled when socket filter is set to \"Mesh Sockets\" or \"Sockets Hidden\" mode)", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateMeshSocket, "Create Mesh Socket", "Duplicate this socket from skeleton to the current mesh and modify the socket data for it", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemoveMeshSocket, "Remove Mesh Socket", "Remove duplicated version of this socket for the current mesh (reverts to the socket in the skeleton)", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( PromoteSocketToSkeleton, "Promote Socket To Skeleton", "Makes this socket available for all meshes that use the same skeleton (copies the socket from this mesh to the skeleton)", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND(DeleteSelectedRows, "Delete", "Delete all selected items in the tree", EUserInterfaceActionType::Button, FInputChord(EKeys::Platform_Delete));

		UI_COMMAND( ShowActiveSockets, "Show Active Sockets", "Show mesh and skeleton sockets, hiding the skeleton sockets that have a customized mesh socket", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowAllSockets, "Show All Sockets", "Show all sockets that are in the mesh and skeleton", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowMeshSockets, "Show Mesh Sockets", "Show sockets that are in the mesh only", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShowSkeletonSockets, "Show Skeleton Sockets", "Show sockets that are in the skeleton only", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( HideSockets, "Hide Sockets", "Show no sockets", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( FocusCamera, "Focus Camera", "Focus the camera on the current selection", EUserInterfaceActionType::Button, FInputChord(EKeys::F) );

		UI_COMMAND( CreateTimeBlendProfile, "Add Time Blend Profile", "Add a new time blend profile for this skeleton", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateWeightBlendProfile, "Add Weight Blend Profile", "Add a new weight blend profile for this skeleton", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( CreateBlendMask, "Add Blend Mask", "Add a new blend mask for this skeleton", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeleteCurrentBlendProfile, "Delete the Current Blend Profile", "Delete the active blend profile for this skeleton", EUserInterfaceActionType::Button, FInputChord() );
		*/

		/**
		FStaticMeshEditorCommands：
		UI_COMMAND(SetShowNaniteFallback, "Nanite Fallback", "Toggles the display of the Nanite fallback mesh. The fallback mesh is used when Nanite is not available such as platforms that do not support it.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control, EKeys::N));
		UI_COMMAND(SetShowWireframe, "Wireframe", "Toggles the viewmode of the Preview Pane between a lit view and a wireframe view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetShowVertexColor, "Vert Colors", "Toggles vertex colors.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetShowPhysicalMaterialMasks, "Physical Material Masks", "Toggles physical material masks.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetDrawUVs, "UV", "Toggles display of the static mesh's UVs for the specified channel.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetShowGrid, "Grid", "Displays the viewport grid.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetShowBounds, "Bounds", "Toggles display of the bounds of the static mesh.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetShowSimpleCollision, "Simple Collision", "Toggles display of the simplified collision mesh of the static mesh, if present.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SetShowComplexCollision, "Complex Collision", "Toggles display of the complex collision for this static mesh.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ResetCamera, "Reset Camera", "Resets the camera to focus on the static mesh", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetShowSockets, "Sockets", "Displays the static mesh sockets.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::S));
		UI_COMMAND(SetDrawAdditionalData, "Additional Data", "Draw additional user data associated with asset.", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(ReimportMesh, "Reimport Base Mesh", "Reimport the base mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportMeshWithNewFile, "Reimport Base Mesh With New File", "Reimport the base mesh using a new source file.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportAllMesh, "Reimport Base Mesh + LODs", "Reimport the base mesh and all the custom LODs.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ReimportAllMeshWithNewFile, "Reimport Base Mesh + LODs With New File", "Reimport the base mesh using a new source file and all the custom LODs (No new source file for the custom LODs).", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(ToggleShowNormals, "Normals", "Toggles display of vertex normals in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowTangents, "Tangents", "Toggles display of vertex tangents in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowBinormals, "Binormals", "Toggles display of vertex binormals (orthogonal vector to normal and tangent) in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowVertices, "Vertices", "Toggles display of vertices in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowPivots, "Show Pivot", "Display the pivot location of the static mesh.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowGrids, "Grid", "Displays the viewport grid.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowBounds, "Bounds", "Toggles display of the bounds of the static mesh.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowSimpleCollisions, "Simple Collision", "Toggles display of the simplified collision mesh of the static mesh, if present.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowComplexCollisions, "Complex Collision", "Toggles display of the complex collision for this static mesh.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowSockets, "Sockets", "Displays the static mesh sockets.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowWireframes, "Wireframe", "Toggles the viewmode of the Preview Pane between a lit view and a wireframe view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleShowVertexColors, "Vert Colors", "Toggles vertex colors.", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(SetShowNormals, "Normals", "Toggles display of vertex normals in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::N));
		UI_COMMAND(SetShowTangents, "Tangents", "Toggles display of vertex tangents in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::T));
		UI_COMMAND(SetShowBinormals, "Binormals", "Toggles display of vertex binormals (orthogonal vector to normal and tangent) in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::B));
		UI_COMMAND(SetShowVertices, "Vertices", "Toggles display of vertices in the Preview Pane.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::V));
		UI_COMMAND(SetShowPivot, "Show Pivot", "Display the pivot location of the static mesh.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Alt, EKeys::P));

		UI_COMMAND(CreateDOP10X, "Add 10DOP-X Simplified Collision", "Generates a new axis-aligned box collision mesh with the 4 X-axis aligned edges beveled (10 total sides) encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateDOP10Y, "Add 10DOP-Y Simplified Collision", "Generates a new axis-aligned box collision mesh with the 4 Y-axis aligned edges beveled (10 total sides) encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateDOP10Z, "Add 10DOP-Z Simplified Collision", "Generates a new axis-aligned box collision mesh with the 4 Z-axis aligned edges beveled (10 total sides) encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateDOP18, "Add 18DOP Simplified Collision", "Generates a new axis-aligned box collision mesh with all edges beveled (18 total sides) encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateDOP26, "Add 26DOP Simplified Collision", "Generates a new axis-aligned box collision mesh with all edges and corners beveled (26 total sides) encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(CreateBoxCollision, "Add Box Simplified Collision", "Generates a new box collision mesh encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateSphereCollision, "Add Sphere Simplified Collision", "Generates a new sphere collision mesh encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateSphylCollision, "Add Capsule Simplified Collision", "Generates a new capsule collision mesh encompassing the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CreateAutoConvexCollision, "Auto Convex Collision", "Opens the Auto Convex Collision Tool for generating a new convex collision mesh, or meshes.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveCollision, "Remove Collision", "Removes any simplified collision assigned to the static mesh.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertBoxesToConvex, "Convert Boxes to Convex", "Converts any simple box collision meshes to convex collision meshes.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(CopyCollisionFromSelectedMesh, "Copy Collision from Selected Static Mesh", "Copy collision from the static mesh selected in Content Browser.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(FindSource, "Find Source", "Opens explorer at the location of this asset.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(ChangeMesh, "Change Mesh", "Changes the static mesh asset loaded in the Static Mesh Editor to the asset currently selected in the Content Browser.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(SaveGeneratedLODs, "Save Generated LODs", "Saves the generated LODs in the mesh package.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(BakeMaterials, "Bake Out Materials", "Bake out Materials for given LOD(s).", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FStaticMeshViewportLODCommands：
		UI_COMMAND( LODAuto, "LOD Auto", "Automatically select LOD", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( LOD0, "LOD 0", "Force select LOD 0", EUserInterfaceActionType::RadioButton, FInputChord() );
		*/

		/**
		FSourceControlCommands：
		UI_COMMAND(ConnectToSourceControl, "Connect to Revision Control...", "Connect to a revision control system for tracking changes to your content and levels.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ChangeSourceControlSettings, "Change Revision Control Settings...", "Opens a dialog to change revision control settings.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ViewChangelists, "View Changes", "Opens a dialog displaying current changes.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SubmitContent, "Submit Content", "Opens a dialog with check in options for content and levels.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(CheckOutModifiedFiles, "Check Out Modified Files", "Opens a dialog to check out any assets which have been modified.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RevertAll, "Revert All Files", "Opens a dialog to revert any assets which have been modified.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FTextureEditorCommands：
		UI_COMMAND(RedChannel, "Red", "Toggles the red channel", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(GreenChannel, "Green", "Toggles the green channel", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(BlueChannel, "Blue", "Toggles the blue channel", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(AlphaChannel, "Alpha", "Toggles the alpha channel", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(Desaturation, "Desaturation", "Toggles color desaturation", EUserInterfaceActionType::ToggleButton, FInputChord());
		
		UI_COMMAND(CheckeredBackground, "Checkered", "Checkered background pattern behind the texture", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CheckeredBackgroundFill, "Checkered (Fill)", "Checkered background pattern behind the entire viewport", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(FitToViewport, "Scale To Fit", "Scales the texture down to fit within the viewport if needed", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(FillToViewport, "Scale To Fill", "Scales the texture to fill the viewport", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ZoomToNatural, "Scale To 100%", "Resets the zoom level to 100%, displaying the texture at its natural size", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(SolidBackground, "Solid Color", "Solid color background", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(TextureBorder, "Draw Border", "If enabled, a border is drawn around the texture", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(DefaultSampling, "Default Sampling", "Use default texture sampling", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PointSampling, "Nearest-Point Sampling", "Use nearest-point texture sampling", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(CompressNow, "Compress", "Compress the texture", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Reimport, "Reimport", "Reimports the texture from file", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Settings, "Advanced Settings...", "Opens the advanced settings for the texture editor", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FTranslationEditorCommands：
		UI_COMMAND( ChangeSourceFont, "Change Source Font", "Change the Font for the Source Lanugage", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ChangeTranslationTargetFont, "Change Translation Font", "Change the Translation Target Language Font", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SaveTranslations, "Save", "Saves the translations to file", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( PreviewAllTranslationsInEditor, "Preview in Editor", "Preview All Translations in the Editor UI", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ImportLatestFromLocalizationService, "Import from Translation Service", "Download and Import Latest Translations From Localization Service. (Localization Service settings can be modified in the Localization Dashboard)", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( ExportToPortableObjectFormat, "Export to .PO", "Export to Portable Object Format", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ImportFromPortableObjectFormat, "Import from .PO", "Import from Portable Object Format", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenSearchTab, "Search", "Search Source and Translation Strings", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( OpenTranslationPicker, "Translation Picker", "Open the Translation Picker to Modify Editor Translations", EUserInterfaceActionType::Button, FInputChord() )
		*/

		/**
		FTurnkeySupportCommands：
		UI_COMMAND(PackagingSettings, "Packaging Settings...", "Opens the settings for project packaging", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FDesignerCommands：
		UI_COMMAND( LayoutTransform, "Layout Transform Mode", "Adjust widget layout transform", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::W) );
		UI_COMMAND( RenderTransform, "Render Transform Mode", "Adjust widget render transform", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::E) );

		UI_COMMAND( LocationGridSnap, "Grid Snap", "Enables or disables snapping to the grid when dragging objects around", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( RotationGridSnap, "Rotation Snap", "Enables or disables snapping objects to a rotation grid", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleOutlines, "Show Outlines", "Enables or disables showing the dashed outlines", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::G) );
		UI_COMMAND( ToggleRespectLocks, "Respect Locks", "Enables or disables respecting locks placed on widgets.  Normally locked widgets prevent being selected in the designer.", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::L) );
		UI_COMMAND( ToggleLocalizationPreview, "Toggle Localization Preview", "Enables or disables the localization preview for the current preview language (see Editor Settings -> Region & Language).", EUserInterfaceActionType::ToggleButton, FInputChord() );
		*/

		/**
		FUMGEditorCommands：
		UI_COMMAND(CreateNativeBaseClass, "Create Native Base Class", "Create a native base class for this widget, using the current parent as the parent of the native class.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND(ExportAsPNG, "Export as Image", "Export the current widget blueprint as .png format.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SetImageAsThumbnail, "Capture and Set as Thumbnail", "Captures the current state of the widget blueprint and sets it as the thumbnail for this asset.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ClearCustomThumbnail, "Clear Thumbnail", "Removes the image used as thumbnail and enables automatic thumbnail generation.", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(DismissOnCompile_ErrorsAndWarnings, "No Errors or Warnings", "Automatically dismiss compile tab when no errors or warnings occur", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DismissOnCompile_Errors, "No Errors", "Automatically dismiss compile tab when no errors occur", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DismissOnCompile_Warnings, "No Warnings", "Automatically dismiss compile tab when no warnings occur (even if there are errors)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(DismissOnCompile_Never, "Never", "Never automatically dismiss the compile tab", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(CreateOnCompile_ErrorsAndWarnings, "On Errors or Warnings", "Automatically create compile tab when errors or warnings occur", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CreateOnCompile_Errors, "On Errors", "Automatically create compile tab when errors occur", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CreateOnCompile_Warnings, "On Warnings", "Automatically create compile tab when warnings occur (but not errors)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(CreateOnCompile_Never, "Never", "Never automatically create the compile tab", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND(OpenAnimDrawer, "Open Animation Browser Drawer", "Opens the animation drawer from the status bar", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::SpaceBar));
		*/

		/**
		FPlayWorldCommands：
		// SIE
		UI_COMMAND(Simulate, "Simulate", "Start simulating the game", EUserInterfaceActionType::Check, FInputChord(EKeys::S, EModifierKey::Alt));
		
		// PIE
		UI_COMMAND(RepeatLastPlay, "Play", "Launches a game preview session in the same mode as the last game preview session launched from the Game Preview Modes dropdown next to the Play button on the level editor toolbar", EUserInterfaceActionType::Button, FInputChord(EKeys::P, EModifierKey::Alt))
		UI_COMMAND(PlayInViewport, "Selected Viewport", "Play this level in the active level editor viewport", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(PlayInEditorFloating, "New Editor Window (PIE)", "Play this level in a new window", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(PlayInVR, "VR Preview", "Play this level in VR", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(PlayInMobilePreview, "Standalone Game Mobile", "Play this level as a mobile device preview in Mobile mode (runs in its own process)", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(PlayInVulkanPreview, "Standalone Game Vulkan Mobile", "Play this level using mobile Vulkan rendering (runs in its own process)", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(PlayInNewProcess, "Standalone Game", "Play this level in a new window that runs in its own process", EUserInterfaceActionType::Check, FInputChord());
		UI_COMMAND(PlayInCameraLocation, "Current Camera Location", "Spawn the player at the current camera location", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PlayInDefaultPlayerStart, "Default Player Start", "Spawn the player at the map's default player start", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND(PlayInNetworkSettings, "Network Settings...", "Open the settings for the 'Play In' feature", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PlayInSettings, "Advanced Settings...", "Open the settings for the 'Play In' feature", EUserInterfaceActionType::Button, FInputChord());

		// SIE & PIE controls
		UI_COMMAND(StopPlaySession, "Stop", "Stop simulation", EUserInterfaceActionType::Button, FInputChord(EKeys::Escape));
		UI_COMMAND(ResumePlaySession, "Resume", "Resume simulation", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PausePlaySession, "Pause", "Pause simulation", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(GetMouseControl, "Mouse Control", "Get mouse cursor while in PIE", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Shift, EKeys::F1));
		UI_COMMAND(LateJoinSession, "Add Client", "Add another client", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SingleFrameAdvance, "Skip", "Advances a single frame", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(TogglePlayPauseOfPlaySession, "Toggle Play/Pause", "Resume playing if paused, or pause if playing", EUserInterfaceActionType::Button, FInputChord(EKeys::Pause));
		UI_COMMAND(PossessEjectPlayer, "Possess or Eject Player", "Possesses or ejects the player from the camera", EUserInterfaceActionType::Button, FInputChord(EKeys::F8));
		UI_COMMAND(ShowCurrentStatement, "Locate", "Locate the currently active node", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(AbortExecution, "Abort", "Abort the execution", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ContinueExecution, "Continue", "Continue the execution", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt | EModifierKey::Shift, EKeys::F10));
		UI_COMMAND(StepInto, "Step Into", "Step Into the next node to be executed", EUserInterfaceActionType::Button, PLATFORM_MAC ? FInputChord(EModifierKey::Control, EKeys::F11) : FInputChord(EKeys::F11));
		UI_COMMAND(StepOver, "Step Over", "Step to the next node to be executed in the current graph", EUserInterfaceActionType::Button, FInputChord(EKeys::F10));
		UI_COMMAND(StepOut, "Step Out", "Step Out to the next node to be executed in the parent graph", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt | EModifierKey::Shift, EKeys::F11));
		*/

		/**
		FAssetEditorCommonCommands：
		UI_COMMAND( SaveAsset, "Save", "Saves this asset", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::S) );
		UI_COMMAND( SaveAssetAs, "Save As...", "Saves this asset under a different name", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::S) );
		UI_COMMAND( ReimportAsset, "Reimport", "Reimports the asset being edited", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( SwitchToStandaloneEditor, "Switch to Standalone Editor", "Closes the level-centric asset editor and reopens it in 'standalone' mode", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SwitchToWorldCentricEditor, "Switch to World-Centric Editor", "Closes the standalone asset editor and reopens it in 'world-centric' mode, docked within the level editor that it was originally opened in.", EUserInterfaceActionType::Button, FInputChord() );
		*/

		/**
		FGlobalEditorCommonCommands：
		UI_COMMAND(SummonControlTabNavigation, "Tab Navigation", "Summons a list of open assets and tabs, and navigates forwards in it.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Tab));
		UI_COMMAND(SummonControlTabNavigationAlternate, "Tab Navigation", "Summons a list of open assets and tabs, and navigates forward in its.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Command, EKeys::Tab));

		UI_COMMAND(SummonControlTabNavigationBackwards, "Tab Navigation Backwards", "Summons a list of open assets and tabs, and navigates backwards in it.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::Tab));
		UI_COMMAND(SummonControlTabNavigationBackwardsAlternate, "Tab Navigation Backwards", "Summons a list of open assets and tabs, and navigates backwards in it.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Command | EModifierKey::Shift, EKeys::Tab));

		UI_COMMAND(SummonOpenAssetDialog, "Open Asset...", "Summons an asset picker", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::P));
		UI_COMMAND(SummonOpenAssetDialogAlternate, "Open Asset...", "Summons an asset picker", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt | EModifierKey::Shift, EKeys::O));
		UI_COMMAND(FindInContentBrowser, "Browse to Asset", "Browses to the associated asset and selects it in the most recently used Content Browser (summoning one if necessary)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::B));

		UI_COMMAND(OpenConsoleCommandBox, "Open Console Command Box", "Opens an edit box where you can type in a console command", EUserInterfaceActionType::Button, FInputChord(EKeys::Tilde));
		UI_COMMAND(SelectNextConsoleExecutor, "Iterate Console Executor", "Iterates through active Console Executors (Python, Cmd, etc.)", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Tilde));
		
		UI_COMMAND(OpenOutputLogDrawer, "Open Output Log Drawer", "Opens the output log drawer from the active asset editor status bar", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::Tilde));

		UI_COMMAND(OpenDocumentation, "Open Documentation...", "Opens documentation for this tool", EUserInterfaceActionType::Button, FInputChord(EKeys::F1));

		#if PLATFORM_MAC
		// On mac command and ctrl are automatically swapped. Command + Space is spotlight search so we use ctrl+space on mac to avoid the conflict
		UI_COMMAND(OpenContentBrowserDrawer, "Open Content Browser Drawer", "Opens the content browser drawer from the status bar and focuses the search field", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Command, EKeys::SpaceBar));
		#else
		UI_COMMAND(OpenContentBrowserDrawer, "Open Content Browser Drawer", "Opens the content browser drawer from the status bar and focuses the search field", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::SpaceBar));
		#endif
		*/

		/**
		FStandardToolModeCommands：
		UI_COMMAND(IncreaseBrushSize, "Increase Brush Size", "Increases the size of the brush", EUserInterfaceActionType::Button, FInputChord(EKeys::RightBracket));
		UI_COMMAND(DecreaseBrushSize, "Decrease Brush Size", "Decreases the size of the brush", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftBracket));
		UI_COMMAND(ToggleWireframe, "Toggle Wireframe", "Toggle Wireframe overlay on/off", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::W));
		*/

		/**
		FViewportNavigationCommands：
		UI_COMMAND(Forward, "Forward", "Moves the camera Forward", EUserInterfaceActionType::Button, FInputChord(EKeys::W));
		UI_COMMAND(Backward, "Backward", "Moves the camera Backward", EUserInterfaceActionType::Button, FInputChord(EKeys::S));
		UI_COMMAND(Left, "Left", "Moves the camera Left", EUserInterfaceActionType::Button, FInputChord(EKeys::A));
		UI_COMMAND(Right, "Right", "Moves the camera Right", EUserInterfaceActionType::Button, FInputChord(EKeys::D));

		UI_COMMAND(Up, "Up", "Moves the camera Up", EUserInterfaceActionType::Button, FInputChord(EKeys::E));
		UI_COMMAND(Down, "Down", "Moves the camera Down", EUserInterfaceActionType::Button, FInputChord(EKeys::Q));

		UI_COMMAND(FovZoomIn, "FOV Zoom In", "Narrows the camers FOV", EUserInterfaceActionType::Button, FInputChord(EKeys::C));
		UI_COMMAND(FovZoomOut, "FOV Zoom Out", "Widens the camera FOV", EUserInterfaceActionType::Button, FInputChord(EKeys::Z));
		*/

		/**
		FEditorViewportCommands：
		UI_COMMAND( Perspective, "Perspective", "Switches the viewport to perspective view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::G ) );
		UI_COMMAND( Front, "Front", "Switches the viewport to front view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::H ) );
		UI_COMMAND( Back, "Back", "Switches the viewport to back view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt | EModifierKey::Shift, EKeys::H ) );
		UI_COMMAND( Top, "Top", "Switches the viewport to top view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::J ) );
		UI_COMMAND( Bottom, "Bottom", "Switches the viewport to bottom view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt | EModifierKey::Shift, EKeys::J ) );
		UI_COMMAND( Left, "Left", "Switches the viewport to left view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::K ) );
		UI_COMMAND( Right, "Right", "Switches the viewport to right view", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt | EModifierKey::Shift, EKeys::K ) );
		UI_COMMAND( Next, "Next", "Rotate through each view options", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Control | EModifierKey::Shift, EKeys::SpaceBar ) );

		UI_COMMAND(ViewportConfig_OnePane, "Layout One Pane", "Changes the viewport arrangement to one pane", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_TwoPanesH, "Layout Two Panes (horizontal)", "Changes the viewport arrangement to two panes, side-by-side", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_TwoPanesV, "Layout Two Panes (vertical)", "Changes the viewport arrangement to two panes, one above the other", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_ThreePanesLeft, "Layout Three Panes (one left, two right)", "Changes the viewport arrangement to three panes, one on the left, two on the right", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_ThreePanesRight, "Layout Three Panes (one right, two left)", "Changes the viewport arrangement to three panes, one on the right, two on the left", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_ThreePanesTop, "Layout Three Panes (one top, two bottom)", "Changes the viewport arrangement to three panes, one on the top, two on the bottom", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_ThreePanesBottom, "Layout Three Panes (one bottom, two top)", "Changes the viewport arrangement to three panes, one on the bottom, two on the top", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_FourPanesLeft, "Layout Four Panes (one left, three right)", "Changes the viewport arrangement to four panes, one on the left, three on the right", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_FourPanesRight, "Layout Four Panes (one right, three left)", "Changes the viewport arrangement to four panes, one on the right, three on the left", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_FourPanesTop, "Layout Four Panes (one top, three bottom)", "Changes the viewport arrangement to four panes, one on the top, three on the bottom", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_FourPanesBottom, "Layout Four Panes (one bottom, three top)", "Changes the viewport arrangement to four panes, one on the bottom, three on the top", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ViewportConfig_FourPanes2x2, "Layout Four Panes (2x2)", "Changes the viewport arrangement to four panes, in a 2x2 grid", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( WireframeMode, "Brush Wireframe View Mode", "Renders the scene in brush wireframe", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Two ) );
		UI_COMMAND( UnlitMode, "Unlit View Mode", "Renders the scene with no lights", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Three ) );
		UI_COMMAND( LitMode, "Lit View Mode", "Renders the scene with normal lighting", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Four ) );
	#if RHI_RAYTRACING
		UI_COMMAND( PathTracingMode, "PathTracing View Mode", "Renders the scene using a path tracer", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( RayTracingDebugMode, "Ray tracing Debug View Mode", "Renders the scene in ray tracing debug mode", EUserInterfaceActionType::RadioButton, FInputChord());
		FRayTracingDebugVisualizationMenuCommands::Register();
	#endif
		UI_COMMAND( DetailLightingMode, "Detail Lighting View Mode", "Renders the scene with detailed lighting only", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Five ) );
		UI_COMMAND( LightingOnlyMode, "Lighting Only View Mode", "Renders the scene with lights only, no textures", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Six ) );
		UI_COMMAND( LightComplexityMode, "Light Complexity View Mode", "Renders the scene with light complexity visualization", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Seven ) );
		UI_COMMAND( ShaderComplexityMode, "Shader Complexity View Mode", "Renders the scene with shader complexity visualization", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Eight ) );
		UI_COMMAND( QuadOverdrawMode, "Quad Complexity View Mode", "Renders the scene with quad complexity visualization", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( ShaderComplexityWithQuadOverdrawMode, "Shader Complexity & Quads visualization", "Renders the scene with shader complexity and quad overdraw visualization", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( TexStreamAccPrimitiveDistanceMode, "Primitive Distance Accuracy View Mode", "Visualize the accuracy of the primitive distance computed for texture streaming", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( TexStreamAccMeshUVDensityMode, "Mesh UV Densities Accuracy View Mode", "Visualize the accuracy of the mesh UV densities computed for texture streaming", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( TexStreamAccMeshUVDensityAll, "All UV Channels", "Visualize the densities accuracy of all UV channels", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( TexStreamAccMaterialTextureScaleMode, "Material Texture Scales Accuracy View Mode", "Visualize the accuracy of the material texture scales used for texture streaming", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( TexStreamAccMaterialTextureScaleAll, "All Textures", "Visualize the scales accuracy of all textures", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( RequiredTextureResolutionMode, "Required Texture Resolution View Mode", "Visualize the ratio between the currently streamed texture resolution and the resolution wanted by the GPU", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( VirtualTexturePendingMipsMode, "Virtual Texture Pending Mips View Mode", "Visualize the difference between the currently streamed virtual texture level and the level wanted by the GPU", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( StationaryLightOverlapMode, "Stationary Light Overlap View Mode", "Visualizes overlap of stationary lights", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( LightmapDensityMode, "Lightmap Density View Mode", "Renders the scene with lightmap density visualization", EUserInterfaceActionType::RadioButton, FInputChord( EModifierKey::Alt, EKeys::Zero ) );

		UI_COMMAND( GroupLODColorationMode, "Level of Detail Coloration View Mode", "Renders the scene using Level of Detail visualization", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( LODColorationMode, "LOD Coloration View Mode", "Renders the scene using LOD color visualization", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( HLODColorationMode, "HLOD Coloration View Mode", "Renders the scene using HLOD color visualization", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( VisualizeGPUSkinCacheMode, "Skin Cache Visualization View Mode", "Visualizes various aspects of Skin ache", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND( VisualizeBufferMode, "Buffer Visualization View Mode", "Renders a set of selected post process materials, which visualize various intermediate render buffers (material attributes)", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( VisualizeNaniteMode, "Nanite Visualization View Mode", "Visualizes various rendering aspects of Nanite.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( VisualizeLumenMode, "Lumen Visualization View Mode", "Visualizes Lumen debug views.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( VisualizeSubstrateMode, "Substrate Visualization View Mode", "Visualizes Substrate debug views.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( VisualizeGroomMode, "Groom Visualization View Mode", "Visualizes Groom debug views.", EUserInterfaceActionType::RadioButton, FInputChord());
		UI_COMMAND( VisualizeVirtualShadowMapMode, "Virtual Shadow Map Visualization View Mode", "Visualizes various rendering aspects of virtual shadow maps.", EUserInterfaceActionType::RadioButton, FInputChord());

		UI_COMMAND( ReflectionOverrideMode, "Reflections View Mode", "Renders the scene with reflections only", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( CollisionPawn, "Player Collision", "Renders player collision visualization", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( CollisionVisibility, "Visibility Collision", "Renders visibility collision visualization", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( ToggleRealTime, "Realtime", "Toggles real time rendering in this viewport", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control, EKeys::R ) );
		UI_COMMAND( ToggleStats, "Show Stats", "Toggles the ability to show stats in this viewport (enables realtime)", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Shift, EKeys::L ) );
		UI_COMMAND( ToggleFPS, "Show FPS", "Toggles showing frames per second in this viewport (enables realtime)", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control|EModifierKey::Shift, EKeys::H ) );

		UI_COMMAND( ScreenCapture, "Screen Capture", "Take a screenshot of the active viewport.", EUserInterfaceActionType::Button, FInputChord(EKeys::F9) );
		UI_COMMAND( ScreenCaptureForProjectThumbnail, "Update Project Thumbnail", "Take a screenshot of the active viewport for use as the project thumbnail.", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( IncrementPositionGridSize, "Grid Size (Position): Increment", "Increases the position grid size setting by one", EUserInterfaceActionType::Button, FInputChord( EKeys::RightBracket ) );
		UI_COMMAND( DecrementPositionGridSize, "Grid Size (Position): Decrement", "Decreases the position grid size setting by one", EUserInterfaceActionType::Button, FInputChord( EKeys::LeftBracket ) );
		UI_COMMAND( IncrementRotationGridSize, "Grid Size (Rotation): Increment", "Increases the rotation grid size setting by one", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::RightBracket ) );
		UI_COMMAND( DecrementRotationGridSize, "Grid Size (Rotation): Decrement", "Decreases the rotation grid size setting by one", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Shift, EKeys::LeftBracket ) );

		UI_COMMAND(SelectMode, "Select Mode", "Select objects", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Q));
		UI_COMMAND( TranslateMode, "Translate Mode", "Select and translate objects", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::W) );
		UI_COMMAND( RotateMode, "Rotate Mode", "Select and rotate objects", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::E) );
		UI_COMMAND( ScaleMode, "Scale Mode", "Select and scale objects", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::R) );
		UI_COMMAND( TranslateRotateMode, "Combined Translate and Rotate Mode", "Select and translate or rotate objects", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( TranslateRotate2DMode, "2D Mode", "Select and translate or rotate objects in 2D", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( ShrinkTransformWidget, "Shrink Transform Widget", "Shrink the level editor transform widget", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::LeftBracket) );
		UI_COMMAND( ExpandTransformWidget, "Expand Transform Widget", "Expand the level editor transform widget", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Alt, EKeys::RightBracket) );

		UI_COMMAND( RelativeCoordinateSystem_World, "World-relative Transform", "Move and rotate objects relative to the cardinal world axes", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( RelativeCoordinateSystem_Local, "Local-relative Transform", "Move and rotate objects relative to the object's local axes", EUserInterfaceActionType::RadioButton, FInputChord() );

	#if PLATFORM_MAC
		UI_COMMAND( CycleTransformGizmoCoordSystem, "Cycle Transform Coordinate System", "Cycles the transform gizmo coordinate systems between world and local (object) space", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Command, EKeys::Tilde));
	#else
		UI_COMMAND( CycleTransformGizmoCoordSystem, "Cycle Transform Coordinate System", "Cycles the transform gizmo coordinate systems between world and local (object) space", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Tilde));
	#endif
		UI_COMMAND( CycleTransformGizmos, "Cycle Between Translate, Rotate, and Scale", "Cycles the transform gizmos between translate, rotate, and scale", EUserInterfaceActionType::Button, FInputChord(EKeys::SpaceBar) );
		
		UI_COMMAND( FocusAllViewportsToSelection, "Focus Selected Actors in All Viewports", "Moves the camera in front of the selected actors in all open viewports", EUserInterfaceActionType::Button, FInputChord(EKeys::F, EModifierKey::Shift) );
		UI_COMMAND( FocusViewportToSelection, "Focus Selected", "Moves the camera in front of the selection", EUserInterfaceActionType::Button, FInputChord( EKeys::F ) );

		UI_COMMAND( LocationGridSnap, "Grid Snap", "Enables or disables snapping to the grid when dragging objects around", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( RotationGridSnap, "Rotation Snap", "Enables or disables snapping objects to a rotation grid", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( Layer2DSnap, "Layer2D Snap", "Enables or disables snapping objects to a 2D layer", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND( ScaleGridSnap, "Scale Snap", "Enables or disables snapping objects to a scale grid", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( SurfaceSnapping, "Surface Snapping", "If enabled, actors will snap to surfaces in the world when dragging", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND( ToggleAutoExposure, "Auto", "If enabled, enables automatic exposure", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ToggleInGameExposure, "Game Settings", "If enabled, uses game settings", EUserInterfaceActionType::ToggleButton, FInputChord() );

		UI_COMMAND(ToggleOverrideViewportScreenPercentage, "Custom Override", "Overrides the screen percentage of this viewport with custom value", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(OpenEditorPerformanceProjectSettings, "Project Settings...", "Opens the project settings for viewport performance", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(OpenEditorPerformanceEditorPreferences, "Editor Preferences...", "Opens the editor preferences for viewport performance", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(ToggleInViewportContextMenu, "In-Viewport Context Menu", "Shows a contextual menu of key properties and actions for the selected items in the viewport.", EUserInterfaceActionType::ToggleButton, FInputChord(EKeys::Tab));
		*/

		/**
		FLevelCollectionCommands：
		UI_COMMAND( RefreshBrowser,	"Refresh",	"Refreshes opened world", EUserInterfaceActionType::Button, FInputChord(EKeys::F5) );

		//invalid selected level
		UI_COMMAND( FixUpInvalidReference, "Replace Selected Level","Removes the broken level and replaces it with the level browsed to", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemoveInvalidReference, "Remove Selected Level", "Removes the reference to the missing level from the map", EUserInterfaceActionType::Button, FInputChord() );
		
		//levels
		UI_COMMAND( World_MakeLevelCurrent, "Make Current", "Make this Level the Current Level", EUserInterfaceActionType::Button, FInputChord( EKeys::Enter ) );
		UI_COMMAND( World_FindInContentBrowser, "Find in Content Browser", "Find the selected levels in the Content Browser", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_LoadLevel, "Load", "Load selected level into world", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_UnloadLevel, "Unload", "Unload selected level from world", EUserInterfaceActionType::Button, FInputChord(EKeys::Platform_Delete) );
		UI_COMMAND( World_SaveSelectedLevels, "Save", "Saves selected levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_SaveSelectedLevelAs, "Save As...", "Save the selected level as...", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_MigrateSelectedLevels, "Migrate...", "Copies the selected levels and all their dependencies to a different game", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_MergeSelectedLevels, "Merge...", "Merges the selected levels into a new level, removing the original levels from the persistent", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_CreateNewLevel, "Create New...", "Creates a new level, or choose a level template to start from.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_AddExistingLevel, "Add Existing...", "Adds an existing level", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_AddSelectedActorsToNewLevel, "Create New with Selected Actors...", "Adds the actors currently selected in the active viewport to a new Level", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_RemoveSelectedLevels, "Remove Selected", "Removes selected levels from the base streaming level", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( MoveWorldOrigin, "Move World Origin to Level Position", "Moves world origin to level position", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ResetWorldOrigin, "Reset World Origin", "Moves world origin to zero", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ResetLevelOrigin, "Reset Level Position", "Moves level to zero", EUserInterfaceActionType::Button, FInputChord() );
		
		//level selection
		UI_COMMAND( SelectAllLevels, "Select All Levels", "Selects all levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( DeselectAllLevels, "De-select All Levels", "De-selects all levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( InvertLevelSelection, "Invert Level Selection", "Inverts level selection", EUserInterfaceActionType::Button, FInputChord() );

		// Source Control
		UI_COMMAND( SCCCheckOut, "Check Out", "Checks out the selected asset from revision control.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SCCCheckIn, "Check In", "Checks in the selected asset to revision control.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SCCOpenForAdd, "Mark For Add", "Adds the selected asset to revision control.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SCCHistory, "History", "Displays the history of the selected asset in revision control.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SCCRefresh, "Refresh", "Updates the revision control status of the asset.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SCCDiffAgainstDepot, "Diff Against Depot", "Look at differences between your version of the asset and that in revision control.", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SCCConnect, "Connect To Revision Control", "Connect to a revision control system for tracking changes to your content and levels.", EUserInterfaceActionType::Button, FInputChord() );

		// set new streaming method
		UI_COMMAND( SetAddStreamingMethod_Blueprint, "Set Blueprint Streaming Method", "Sets the streaming method for new or added levels to Blueprint streaming", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( SetAddStreamingMethod_AlwaysLoaded, "Set Streaming to Always Loaded", "Sets the streaming method new or added selected levels to be always loaded", EUserInterfaceActionType::RadioButton, FInputChord() );

		// change streaming method
		UI_COMMAND( SetStreamingMethod_Blueprint, "Change Blueprint Streaming Method", "Changes the streaming method for the selected levels to Blueprint streaming", EUserInterfaceActionType::Check, FInputChord() );
		UI_COMMAND( SetStreamingMethod_AlwaysLoaded, "Change Streaming to Always Loaded", "Changes the streaming method for the selected levels to be always loaded", EUserInterfaceActionType::Check, FInputChord() );

		// change lighting scenario
		UI_COMMAND( SetLightingScenario_Enabled, "Make level a Lighting Scenario", "Changes the level to be a Lighting Scenario.  Lighting is built separately for each Lighting Scenario, with all other Scenarios hidden.", EUserInterfaceActionType::Check, FInputChord() );
		UI_COMMAND( SetLightingScenario_Disabled, "Make level not a Lighting Scenario", "Changes the level to not be a Lighting Scenario", EUserInterfaceActionType::Check, FInputChord() );

		//layers
		UI_COMMAND( AssignLevelToLayer, "Assign to layer", "Assign selected levels to current layer", EUserInterfaceActionType::Button, FInputChord() );

		//actors
		UI_COMMAND( AddsActors, "Select Actors", "Adds the Actors in the selected Levels from the viewport's existing selection", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( RemovesActors, "Deselect Actors", "Removes the Actors in the selected Levels from the viewport's existing selection", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND (ConvertLevelToExternalActors, "Convert Level to External Actors", "Enable selected levels to use external actors and convert their actors to external packaging", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ConvertLevelToInternalActors, "Convert Level to Internal Actors", "Disable selected levels to use external actors and convert their actors to internal packaging", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MoveActorsToSelected, "Move Selected Actors to Level", "Moves the selected actors to this level", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( MoveFoliageToSelected, "Move Selected Foliage to Level", "Moves the selected foliage instances to this level. Keeps cross-level references to original bases", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( SelectStreamingVolumes, "Select Streaming Volumes", "Selects the streaming volumes associated with the selected levels", EUserInterfaceActionType::Button, FInputChord() );

		//visibility
		UI_COMMAND( World_ShowSelectedLevels, "Show Selected", "Toggles selected levels to a visible state in the viewports", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_HideSelectedLevels, "Hide Selected", "Toggles selected levels to an invisible state in the viewports", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_ShowOnlySelectedLevels, "Show Only Selected", "Toggles the selected levels to a visible state; toggles all other levels to an invisible state", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_ShowAllButSelectedLevels, "Show All But Selected", "Toggles the selected levels to an invisible state; toggles all other levels to a visible state", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( World_ShowAllLevels, "Show All", "Toggles all levels to a visible state in the viewports", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND( World_HideAllLevels, "Hide All", "Hides all levels to an invisible state in the viewports", EUserInterfaceActionType::Button, FInputChord() );

		//lock
		UI_COMMAND( World_LockSelectedLevels, "Lock Selected", "Locks selected levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_UnlockSelectedLevels, "Unlock Selected", "Unlocks selected levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_LockOnlySelectedLevels, "Lock Only Selected", "Toggles the selected levels to a locked state; toggles all other levels to an unlocked state", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_LockAllButSelectedLevels, "Lock All But Selected", "Toggles the selected levels to an unlocked state; toggles all other levels to a locked state", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_LockAllLevels, "Lock All", "Locks all levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_UnlockAllLevels, "Unlock All", "Unlocks all levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_LockReadOnlyLevels, "Lock Read-Only Levels", "Locks all read-only levels", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( World_UnlockReadOnlyLevels, "Unlock Read-Only Levels", "Unlocks all read-only levels", EUserInterfaceActionType::Button, FInputChord() );
		
		//view
		UI_COMMAND( FitToSelection, "Fit to Selection", "Fits view to selected levels", EUserInterfaceActionType::Button, FInputChord(EKeys::F) );
		UI_COMMAND( ExpandSelectedItems, "Expand Selected", "Expands all children of a selected items", EUserInterfaceActionType::Button, FInputChord() );
		
		// Parent->child
		UI_COMMAND( ClearParentLink, "Clear Parent Link", "Clears parent link for selected items", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( MoveLevelLeft,	"Move Level Left",		"Moves level to the left by 1 unit", EUserInterfaceActionType::Button, FInputChord(EKeys::Left) );
		UI_COMMAND( MoveLevelRight, "Move Level Right",		"Moves level to the right by 1 unit", EUserInterfaceActionType::Button, FInputChord(EKeys::Right) );
		UI_COMMAND( MoveLevelUp,	"Move Level Up",		"Moves level up by 1 unit", EUserInterfaceActionType::Button, FInputChord(EKeys::Up) );
		UI_COMMAND( MoveLevelDown,	"Move Level Down",		"Moves level down by 1 unit", EUserInterfaceActionType::Button, FInputChord(EKeys::Down) );
		
		// Landscape operations
		UI_COMMAND( ImportTiledLandscape, "Import Tiled Landscape...", "Imports landscape from a tiled heightmap files (<name>X<n>_Y<n>.png)", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddLandscapeLevelXNegative,	"-X",	"Add a new adjacent level with landscape proxy", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddLandscapeLevelXPositive,	"+X",	"Add a new adjacent level with landscape proxy", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddLandscapeLevelYNegative,	"-Y",	"Add a new adjacent level with landscape proxy", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( AddLandscapeLevelYPositive,	"+Y",	"Add a new adjacent level with landscape proxy", EUserInterfaceActionType::Button, FInputChord() );
				
		UI_COMMAND( LockTilesLocation, "Lock tiles location", "When enabled all tiles location will be locked, content inside tiles can still be edited", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		SWorldPartitionEditorGrid2D::FEditorCommands：
		UI_COMMAND(CreateRegionFromSelection, "Load Region From Selection", "Load region from selection.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(LoadSelectedRegions, "Load Selected Regions", "Load the selected regions.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(UnloadSelectedRegions, "Unload Selected Regions", "Unload the selected regions.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ConvertSelectedRegionsToActors, "Convert Selected Regions To Actors", "Convert the selected regions to actors.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(MoveCameraHere, "Move Camera Here", "Move the camera to the selected location.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PlayFromHere, "Play From Here", "Play from here.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(LoadFromHere, "Load From Here", "Load from here.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(BugItHere, "Bug It Here", "Log BugItGo command of the selected location to console (also adds it to clipboard).", EUserInterfaceActionType::Button, FInputChord());
		*/
#pragma endregion

#pragma region Source/Developer
		/**
		FAutomationWindowCommands：
		UI_COMMAND( RefreshTests, "Refresh Tests", "Refresh Tests", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( FindWorkers, "Find Workers", "Find Workers", EUserInterfaceActionType::Button, FInputChord() );
		UI_COMMAND( ErrorFilter, "Errors", "Toggle Error Filter", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( WarningFilter, "Warnings", "Toggle Warning Filter", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( DeveloperDirectoryContent, "Dev Content", "Developer Directory Content Filter (when enabled, developer directories are also included)", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( ExcludedTestsFilter, "Excluded Tests", "Toggle Excluded Tests only", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(RunLevelTest, "Run Level Test", "Run Level Test", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(CreateNewPreset, "Create Automation Preset", "Create New Preset", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RemoveCurrentPreset, "Delete", "Remove Current Preset", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(RenameCurrentPreset, "Rename", "Rename Current Preset", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FDeviceDetailsCommands：
		UI_COMMAND(Claim, "Claim", "Claim the device", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Release, "Release", "Release the device", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Remove, "Remove", "Remove the device", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Share, "Share", "Share the device with other users", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(Connect, "Connect", "Connect to the device", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Disconnect, "Disconnect", "Disconnect from the device", EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(PowerOff, "Power Off", "Power off the device", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PowerOffForce, "Power Off (Force)", "Power off the device (forcefully close any running applications)", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(PowerOn, "Power On", "Power on the device", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Reboot, "Reboot", "Reboot the device", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FVisualLoggerCommands：
		UI_COMMAND(StartRecording, "Start", "Start the debugger", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(StopRecording, "Stop", "Step over the current message", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Pause, "Pause", "Stop the debugger", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Resume, "Resume", "Resume", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(FreeCamera, "FreeCamera", "Enable free camera", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(LoadFromVLog, "Load", "Load external vlogs", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SaveToVLog, "Save", "Save selected data to vlog file", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SaveAllToVLog, "SaveAll", "Save all to vlog file", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(ToggleGraphs, "ToggleGraphs", "Toggle graphs visualization on/off", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ResetData, "Clear", "Clear all data", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Refresh, "Refresh", "Refresh UI from memory buffer", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(HideEmpty, "HideEmpty", "Hide logs without text information", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		FProfilerCommands：
		UI_COMMAND( ToggleDataPreview, 	"Data Preview", "Toggles the data preview", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control, EKeys::R ) );
		UI_COMMAND( ToggleDataCapture, "Data Capture", "Toggles the data capture", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control, EKeys::C ) );
		UI_COMMAND( ToggleShowDataGraph, "Show Data Graph", "Toggles showing all data graphs", EUserInterfaceActionType::ToggleButton, FInputChord() );
		UI_COMMAND( OpenEventGraph, "Open Event Graph", "Opens a new event graph", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( ProfilerManager_Save, "Save", "Saves all collected data to file or files", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::S ) );
		UI_COMMAND( StatsProfiler, "Statistics", "Enables the Stats Profiler", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control, EKeys::P ) );
		#if PLATFORM_MAC
		UI_COMMAND( MemoryProfiler, "Memory", "Enables the Memory Profiler", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Command, EKeys::M ) );
		UI_COMMAND( FPSChart, "FPS Chart", "Shows the FPS Chart", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Command, EKeys::H ) );
		#else
		UI_COMMAND( MemoryProfiler, "Memory", "Enables the Memory Profiler", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control, EKeys::M ) );
		UI_COMMAND( FPSChart, "FPS Chart", "Shows the FPS Chart", EUserInterfaceActionType::ToggleButton, FInputChord( EModifierKey::Control, EKeys::H ) );
		#endif

		UI_COMMAND( OpenSettings, "Settings", "Opens the settings for the profiler", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::O ) );

		UI_COMMAND( ProfilerManager_Load, "Load", "Loads profiler data", EUserInterfaceActionType::Button, FInputChord( EModifierKey::Control, EKeys::L ) );
		UI_COMMAND(ProfilerManager_LoadMultiple, "Load Folder", "Loads multiple stats dumps", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::L));
		UI_COMMAND(ProfilerManager_ToggleLivePreview, "Live preview", "Toggles the real time live preview", EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND( DataGraph_ToggleViewMode, "Toggle graph view mode", "Toggles the data graph view mode between time based and index based", EUserInterfaceActionType::Button, FInputChord() );

		UI_COMMAND( DataGraph_ViewMode_SetTimeBased, "Time based", "Sets the data graph view mode to the time based", EUserInterfaceActionType::RadioButton, FInputChord() );
		UI_COMMAND( DataGraph_ViewMode_SetIndexBased, "Index based", "Sets the data graph view mode to the index based", EUserInterfaceActionType::RadioButton, FInputChord() );

		UI_COMMAND( EventGraph_SelectAllFrames, "Select all frames", "Selects all frames in the data graph and displays them in the event graph", EUserInterfaceActionType::Button, FInputChord() );
		*/

		/**
		FProjectLauncherCommands：
		UI_COMMAND(QuickLaunch, "Quick Launch", "Builds, cooks, and launches a build.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control, EKeys::L));
		UI_COMMAND(CreateBuild, "Build", "Creates a build.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control, EKeys::B));
		UI_COMMAND(DeployBuild, "Deploy Build", "Deploys a pre-made build.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control, EKeys::D));
		UI_COMMAND(AdvancedBuild, "Advanced...", "Advanced launcher.", EUserInterfaceActionType::ToggleButton, FInputChord(EModifierKey::Control, EKeys::A));
		UI_COMMAND(CloseSettings, "Back", "Close the launch profile settings editor and go back to the launcher.", EUserInterfaceActionType::Button, FInputChord(EModifierKey::None, EKeys::Escape));
		UI_COMMAND(RenameProfile, "Rename", "Rename the launch profile.", EUserInterfaceActionType::Button, FInputChord());// , FInputChord(EModifierKey::None, EKeys::F2));
		UI_COMMAND(DuplicateProfile, "Duplicate", "Duplicate the launch profile.", EUserInterfaceActionType::Button, FInputChord());//, FInputChord(EModifierKey::Control, EKeys::W));
		UI_COMMAND(DeleteProfile, "Delete", "Delete the launch profile.", EUserInterfaceActionType::Button, FInputChord());//, FInputChord(EModifierKey::Control, EKeys::Delete));
		*/

		/**
		FSessionConsoleCommands：
		UI_COMMAND(Clear, "Clear Log", "Clear the log window", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SessionCopy, "Copy", "Copy the selected log messages to the clipboard", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(SessionSave, "Save Log...", "Save the entire log to a file", EUserInterfaceActionType::ToggleButton, FInputChord());
		*/

		/**
		FContextSwitchesStateCommands：
		
		UI_COMMAND(Command_ShowCoreTracks,
		"CPU Core Tracks",
		"Shows/hides the CPU Core tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EModifierKey::Alt, EKeys::C));

		UI_COMMAND(Command_ShowContextSwitches,
		"Context Switches",
		"Shows/hides the context switches on top of CPU timing tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EModifierKey::Shift, EKeys::C));

		UI_COMMAND(Command_ShowOverlays,
		"Overlays",
		"Extends the visualization of context switches over the CPU timing tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EModifierKey::Shift, EKeys::O));

		UI_COMMAND(Command_ShowExtendedLines,
		"Extended Lines",
		"Shows/hides the extended vertical lines at edges of each context switch event.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EModifierKey::Shift, EKeys::L));

		UI_COMMAND(Command_NavigateToCpuThreadEvent,
		"Go To CPU Thread Track",
		"Selects the context switch event in the corresponding CPU Thread track.",
		EUserInterfaceActionType::Button,
		FInputChord(//EModifierKey::Control, EKeys::Tab));

		UI_COMMAND(Command_DockCpuThreadTrackToBottom,
		"Dock CPU Thread Track To Bottom",
		"Docks the corresponding CPU Thread track to the bottom of the Timing view.",
		EUserInterfaceActionType::Button,
		FInputChord());

		UI_COMMAND(Command_NavigateToCpuCoreEvent,
		"Go To CPU Core Track",
		"Selects the timing event in the corresponding CPU Core track.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control, EKeys::Tab));

		UI_COMMAND(Command_DockCpuCoreTrackToTop,
		"Dock CPU Core Track To Top",
		"Docks the corresponding CPU Core track to the top of the Timing view.",
		EUserInterfaceActionType::Button,
		FInputChord());
		*/

		/**
		FLoadingProfilerCommands：
		UI_COMMAND(ToggleTimingViewVisibility,
		"Timing",
		"Toggles the visibility of the main Timing view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleEventAggregationTreeViewVisibility,
		"Event Aggregation",
		"Toggles the visibility of the Event Aggregation table/tree view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleObjectTypeAggregationTreeViewVisibility,
		"Object Type Aggregation",
		"Toggles the visibility of the Object Type Aggregation table/tree view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(TogglePackageDetailsTreeViewVisibility,
		"Package Details",
		"Toggles the visibility of the Package Details table/tree view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleExportDetailsTreeViewVisibility,
		"Export Details",
		"Toggles the visibility of the Export Details table/tree view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleRequestsTreeViewVisibility,
		"Requests",
		"Toggles the visibility of the Requests table/tree view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());
		*/

		/**
		FMemoryTimingViewCommands：
		UI_COMMAND(ShowHideAllMemoryTracks,
		"Memory Tracks",
		"Shows/hides the Memory tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EModifierKey::Control, EKeys::M));
		*/

		/**
		FMemoryProfilerCommands：
		UI_COMMAND(ToggleTimingViewVisibility,
		"Timing",
		"Toggles the visibility of the main Timing view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleMemInvestigationViewVisibility,
		"Investigation",
		"Toggles the visibility of the Memory Investigation (Alloc Queries) view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleMemTagTreeViewVisibility,
		"LLM Tags",
		"Toggles the visibility of the LLM Tags tree view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleModulesViewVisibility,
		"Modules",
		"Toggles the visibility of the Modules view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());
		*/

		/**
		FNetworkingProfilerCommands：
		UI_COMMAND(TogglePacketViewVisibility,
		"Packets",
		"Toggles the visibility of the Packets view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(TogglePacketContentViewVisibility,
		"Packet Content",
		"Toggles the visibility of the Packet Content view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleNetStatsViewVisibility,
		"Net Stats",
		"Toggles the visibility of the Net Stats view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleNetStatsCountersViewVisibility,
		"Net Stats Counters",
		"Toggles the visibility of the Net Stats view.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());
		*/

		/**
		FTableTreeViewCommands：
		UI_COMMAND(Command_CopyToClipboard,
		"Copy",
		"Copies the selected table rows to clipboard.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control, EKeys::C));

		UI_COMMAND(Command_CopyColumnToClipboard,
		"Copy Value",
		"Copies the value of the hovered cell to clipboard.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::C));

		UI_COMMAND(Command_CopyColumnTooltipToClipboard,
		"Copy Tooltip",
		"Copies the tooltip of the hovered cell to clipboard.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control | EModifierKey::Alt, EKeys::C));

		UI_COMMAND(Command_ExpandSubtree,
		"Expand Subtree",
		"Expand the subtree that starts from the selected group node.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::None, EKeys::E));

		UI_COMMAND(Command_ExpandCriticalPath,
		"Expand Critical Path",
		"Expand the first group child node recursively until a leaf nodes in reached.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::None, EKeys::R));

		UI_COMMAND(Command_CollapseSubtree,
		"Collapse Subtree",
		"Collapse the subtree that starts from the selected group node.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::None, EKeys::C));

		UI_COMMAND(Command_ExportToFile,
		"Export Visible Tree to File...",
		"Exports the tree/table content to a file. It exports only the tree nodes currently expanded in the tree, including leaf nodes.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control, EKeys::E));

		UI_COMMAND(Command_ExportEntireTreeToFile,
		"Export Entire Tree (+ Leaf Nodes) to File...",
		"Exports the entire tree/table content to a file. It exports also the collapsed tree nodes, including the leaf nodes. Filtered out nodes are not exported.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Shift, EKeys::E));

		UI_COMMAND(Command_ExportEntireTreeToFileExceptLeaves,
		"Export Entire Tree (- Leaf Nodes) to File...",
		"Exports the entire tree/table content to a file, but not the leaf nodes. It exports the collapsed tree nodes. Filtered out nodes are not exported.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Alt, EKeys::E));
		*/

		/**
		FTaskTimingStateCommands：
		UI_COMMAND(Command_ShowTaskTransitions,
				   "Show Task Transitions",
				   "Show/hide transitions between the stages of the current task (for a selected cpu timing event.)",
				    EUserInterfaceActionType::ToggleButton,
				    FInputChord(EKeys::T));

		UI_COMMAND(Command_ShowTaskConnections,
				   "Show Task Connections",
				   "Show/hide conections between:\nThe current task's prerequisites completed time and the current task's started time.\nThe current task's completed time and the current task's subsequents started time.\nThe current task's nested tasks added time and their started time.",
				   EUserInterfaceActionType::ToggleButton, FInputChord());

		UI_COMMAND(Command_ShowTaskPrerequisites,
				   "Show Transitions of Prerequisites",
				   "Show/hide stage transitions for the current task's prerequisites.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord(EKeys::P));

		UI_COMMAND(Command_ShowTaskSubsequents,
				   "Show Transitions of Subsequents",
				   "Show/hide stage transitions for the current task's subsequents.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord(EKeys::S));

		UI_COMMAND(Command_ShowParentTasks,
				   "Show Transitions of Parent Tasks",
				   "Show/hide stage transitions for the current task's parent tasks.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord(EKeys::R));

		UI_COMMAND(Command_ShowNestedTasks,
				   "Show Transitions of Nested Tasks",
				   "Show/hide stage transitions for the current task's nested tasks.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord(EKeys::N));

		UI_COMMAND(Command_ShowCriticalPath,
				   "Show Task Critical Path",
				   "Show/hide relations representing the critical path containing the current task.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord());

		UI_COMMAND(Command_ShowTaskTrack,
				   "Show Task Overview Track",
				   "Show/hide the Task Overview Track when a task is selected.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord());

		UI_COMMAND(Command_ShowDetailedTaskTrackInfo,
				   "Show Detailed Info on the Task Overview Track",
				   "Show the current task's prerequisites/nested tasks/subsequents in the Task Overview Track.",
				   EUserInterfaceActionType::ToggleButton,
				   FInputChord());
		*/

		/**
		FTaskTableTreeViewCommands：
		UI_COMMAND(Command_GoToTask, "Go To Task", "Pan and zoom to the task in Timing View.", EUserInterfaceActionType::Button, FInputChord());
		UI_COMMAND(Command_OpenInIDE, "Open in IDE", "Open the source location where the selected task was launched in IDE.", EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FFileActivityTimingViewCommands：
		UI_COMMAND(ShowHideAllIoTracks,
		"File Activity Tracks",
		"Shows/hides the File Activity tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::I));

		UI_COMMAND(ShowHideIoOverviewTrack,
		"I/O Overview Track",
		"Shows/hides the I/O Overview track.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleOnlyErrors,
		"Only Errors (I/O Overview Track)",
		"Shows only the events with errors, in the I/O Overview track.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ShowHideIoActivityTrack,
		"I/O Activity Track",
		"Shows/hides the I/O Activity track.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleBackgroundEvents,
		"Background Events (I/O Activity Track)",
		"Shows/hides background events for file activities, in the I/O Activity track.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::O));
		*/

		/**
		FFrameTimingViewCommands：
		UI_COMMAND(ShowHideAllFrameTracks,
		"Frame Tracks",
		"Shows/hides all Frame tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::R));
		*/

		/**
		FLoadingTimingViewCommands：
		UI_COMMAND(ShowHideAllLoadingTracks,
		"Asset Loading Tracks",
		"Shows/hides the Asset Loading tracks.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::L));
		*/

		/**
		FTimingRegionsViewCommands：
		UI_COMMAND(ShowHideRegionTrack,
		"Timing Regions Track",
		"Shows/hides the Timing Regions track.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::R));
		*/

		/**
		FThreadTimingViewCommands：
		UI_COMMAND(ShowHideAllGpuTracks,
		"GPU Track(s)",
		"Shows/hides the GPU track(s).",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::Y));

		UI_COMMAND(ShowHideAllCpuTracks,
		"CPU Thread Tracks",
		"Shows/hides all CPU tracks (and all CPU thread groups).",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::U));
		*/

		/**
		FLogViewCommands：
				UI_COMMAND(Command_HideSelectedCategory,
			"Hide Category",
			"Hides the selected log category.",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ShowOnlySelectedCategory,
			"Show Only Selected Category",
			"Shows only the selected log category (hides all other log categories).",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ShowAllCategories,
			"Show All Categories",
			"Resets the category filter (shows all log categories).",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_CopySelected,
			"Copy",
			"Copies the selected log (with all its properties) to clipboard.",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control, EKeys::C));

		UI_COMMAND(Command_CopyMessage,
			"Copy Message",
			"Copies the message text of the selected log to clipboard.",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Shift, EKeys::C));

		UI_COMMAND(Command_CopyRange,
			"Copy Range",
			"Copies all the logs in the selected time range (highlighted in blue) to clipboard.",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control | EModifierKey::Shift, EKeys::C));

		UI_COMMAND(Command_CopyAll,
			"Copy All",
			"Copies all the (filtered) logs to clipboard.",
			EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(Command_SaveRange,
			"Save Range As...",
			"Saves all the logs in the selected time range (highlighted in blue) to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::S));

		UI_COMMAND(Command_SaveAll,
			"Save All As...",
			"Saves all the (filtered) logs to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button, FInputChord());

		UI_COMMAND(Command_OpenSource,
			"Open Source",
			"Opens the source file of the selected message in the registered IDE.",
			EUserInterfaceActionType::Button, FInputChord());
		*/

		/**
		FStatsViewCommands：
		UI_COMMAND(Command_CopyToClipboard,
			"Copy To Clipboard",
			"Copies the selection (counters and their aggregated statistics) to clipboard.",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control, EKeys::C));

		UI_COMMAND(Command_Export,
			"Export...",
			"Exports the selection (counters and their aggregated statistics) to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control, EKeys::S));

		UI_COMMAND(Command_ExportValues,
			"Export Values...",
			"Exports the values of the selected counter to a text file (tab-separated values or comma-separated values).\nExports the values only in the selected time region (if any) or the entire session if no time region is selected.",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ExportOps,
			"Export Operations...",
			"Exports the incremental operations/values of the selected counter to a text file (tab-separated values or comma-separated values).\nExports the ops/values only in the selected time region (if any) or the entire session if no time region is selected.",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ExportCounters,
			"Export Counters...",
			"Exports the list of counters to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button,
			FInputChord());
		*/

		/**
		FTimerTreeViewCommands：
		UI_COMMAND(Command_CopyToClipboard,
			"Copy To Clipboard",
			"Copies the selection to clipboard.",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control, EKeys::C));
		*/

		/**
		FTimersViewCommands：
		UI_COMMAND(Command_CopyToClipboard,
			"Copy To Clipboard",
			"Copies the selection (timers and their aggregated statistics) to clipboard.",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control, EKeys::C));

		UI_COMMAND(Command_Export,
			"Export...",
			"Exports the selection (timers and their aggregated statistics) to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button,
			FInputChord(EModifierKey::Control, EKeys::S));

		UI_COMMAND(Command_ExportTimingEventsSelection,
			"Export Timing Events (Selection)...",
			"Exports the timing events to a text file (tab-separated values or comma-separated values).\nOnly exports the timing events of the selected timer(s), for the visible CPU/GPU Thread tracks and in the selected time region (if any).",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ExportTimingEvents,
			"Export Timing Events (All)...",
			"Exports all the timing events (for all CPU/GPU threads) to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ExportThreads,
			"Export Threads...",
			"Exports the list of threads to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_ExportTimers,
			"Export Timers...",
			"Exports the list of timers to a text file (tab-separated values or comma-separated values).",
			EUserInterfaceActionType::Button,
			FInputChord());

		UI_COMMAND(Command_OpenSource,
			"Open Source",
			"Opens the source file of the selected timer in the registered IDE.",
			EUserInterfaceActionType::Button,
			FInputChord());
		*/

		/**
		FInsightsCommands：
		UI_COMMAND(InsightsManager_Load,
		"Load...",
		"Loads profiler data from a trace file.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control, EKeys::L));

		UI_COMMAND(ToggleDebugInfo,
		"Debug",
		"Toggles the display of debug info.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EModifierKey::Control, EKeys::D));

		UI_COMMAND(OpenSettings,
		"Settings",
		"Opens the Unreal Insights settings.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control, EKeys::O));
		*/

		/**
		FTimingProfilerCommands：
		UI_COMMAND(ToggleFramesTrackVisibility, "Frames", "Toggles the visibility of the Frames track.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleTimingViewVisibility, "Timing", "Toggles the visibility of the main Timing view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleTimersViewVisibility, "Timers", "Toggles the visibility of the Timers view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleCallersTreeViewVisibility, "Callers", "Toggles the visibility of the Callers tree view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleCalleesTreeViewVisibility, "Callees", "Toggles the visibility of the Callees tree view.", EUserInterfaceActionType::ToggleButton,FInputChord());
		UI_COMMAND(ToggleStatsCountersViewVisibility, "Counters", "Toggles the visibility of the Counters view.", EUserInterfaceActionType::ToggleButton, FInputChord());
		UI_COMMAND(ToggleLogViewVisibility, "Log", "Toggles the visibility of the Log view.", EUserInterfaceActionType::ToggleButton,FInputChord());
		*/

		/**
		FTimingViewCommands：
		UI_COMMAND(AutoHideEmptyTracks,
		"Auto Hide Empty Tracks",
		"Auto hide empty tracks (ex.: ones without timing events in the current viewport).\nThis option is persistent to the UnrealInsightsSettings.ini file.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::V));

		UI_COMMAND(PanningOnScreenEdges,
		"Allow Panning on Screen Edges",
		"If enabled, the panning is allowed to continue when the mouse cursor reaches the edges of the screen.\nThis option is persistent to the UnrealInsightsSettings.ini file.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord());

		UI_COMMAND(ToggleCompactMode,
		"Compact Mode",
		"Toggle compact mode for supporting tracks.\n(ex.: the timing tracks will be displayed with reduced height)",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::C));

		UI_COMMAND(ShowMainGraphTrack,
		"Graph Track",
		"Shows/hides the main Graph track.",
		EUserInterfaceActionType::ToggleButton,
		FInputChord(EKeys::G));

		UI_COMMAND(QuickFind,
		"Quick Find...",
		"Quick find or filter events in the timing view.",
		EUserInterfaceActionType::Button,
		FInputChord(EModifierKey::Control, EKeys::F));
		*/
#pragma endregion
	}
};
