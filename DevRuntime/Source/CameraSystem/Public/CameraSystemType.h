#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

class ACameraPointBase;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera);

struct CAMERASYSTEM_API FCameraSystemDelegates
{
	/* Call When Copy Editor Viewport Camera To Camera Point */
	DECLARE_MULTICAST_DELEGATE_OneParam(FCameraPointMulticastDelegate, ACameraPointBase*)
	static FCameraPointMulticastDelegate OnCopyViewportCamera;

	/* Call When Pilot/UnPilot Camera Point */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCameraPointPilotStateChanged, ACameraPointBase*, bool)
	static FOnCameraPointPilotStateChanged OnCameraPointPilotStateChanged;

	/* Call Before Switch Camera Begin */
	static FCameraPointMulticastDelegate PreSwitchCamera;

	/* Call After Switch Camera Begin */
	static FCameraPointMulticastDelegate PostSwitchCamera;

	/* Call When Switch Camera Finish */
	static FSimpleMulticastDelegate OnSwitchCameraFinish;
};
