#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

class UCameraHandle;
class ACameraPointBase;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera);

struct CAMERASYSTEM_API FCameraSystemDelegates
{
	/* Call When Copy Editor Viewport Camera To Camera Point */
	DECLARE_MULTICAST_DELEGATE_OneParam(FCameraPointDelegate, ACameraPointBase*)
	static FCameraPointDelegate OnCopyViewportCamera;

	/* Call When Pilot/UnPilot Camera Point */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCameraPointPilotStateChanged, ACameraPointBase*, bool)
	static FOnCameraPointPilotStateChanged OnCameraPointPilotStateChanged;

	/* Call Before Switch Camera Begin */
	static FCameraPointDelegate PreSwitchCamera;

	/* Call After Switch Camera Begin */
	static FCameraPointDelegate PostSwitchCamera;

	/* Call When Switch Camera Finish */
	DECLARE_MULTICAST_DELEGATE_OneParam(FCameraHandleDelegate, UCameraHandle*)
	static FCameraHandleDelegate OnSwitchCameraFinish;
};
