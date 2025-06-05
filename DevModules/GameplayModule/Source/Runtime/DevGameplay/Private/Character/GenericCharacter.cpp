// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Character/GenericCharacter.h"

#include "AIController.h"
#include "GameFramework/GameplayCameraComponent.h"
#include "core/CameraAsset.h"
#include "Core/CameraVariableAssets.h"
#include "Core/CameraVariableCollection.h"
#include "GameFramework/CameraRigParameterInterop.h"

AGenericCharacter::AGenericCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GameplayCamera = CreateDefaultSubobject<UGameplayCameraComponent>("GameplayCamera");
	GameplayCamera->SetupAttachment(GetRootComponent());
	GameplayCamera->bAutoActivate = true;
	GameplayCamera->AutoActivateForPlayer = EAutoReceiveInput::Type::Player0;

	if (UCameraAsset* GeneraicCameraAsset = LoadObject<UCameraAsset>(nullptr,TEXT("/Script/GameplayCameras.CameraAsset'/CameraModule/BCD_Generic.BCD_Generic'")))
	{
		GameplayCamera->Camera = GeneraicCameraAsset;
	}

	InputMovementComponent = CreateDefaultSubobject<UPawnInputMovementComponent>("InputMovementComponent");
}

void AGenericCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

/* ==================== IPawnInterface ==================== */

bool AGenericCharacter::IsPlayer()
{
	return IsValid(Cast<APlayerController>(GetController()));
}

bool AGenericCharacter::IsAI()
{
	return IsValid(Cast<AAIController>(GetController()));
}

APlayerController* AGenericCharacter::GetPlayerController()
{
	return Cast<APlayerController>(GetController());
}

AAIController* AGenericCharacter::GetAIController()
{
	return Cast<AAIController>(GetController());
}

/* ==================== IPawnInputMovementInterface ==================== */

void AGenericCharacter::AddLocation_Implementation(FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddLocation(InputMovementComponent, InValue);
}

void AGenericCharacter::AddRotation_Implementation(FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddRotation(InputMovementComponent, InValue);
}

void AGenericCharacter::AddZoom_Implementation(float InValue)
{
	const FBlueprintCameraVariableTable Table = GameplayCamera->GetInitialVariableTable();
	if (Table.IsValid())
	{
		if (InputMovementComponent->GetActiveCameraRig() == ECameraRig::ThirdPerson)
		{
			if (UCameraVariableCollection* GeneraicCameraCollection = LoadObject<UCameraVariableCollection>(nullptr,TEXT("/Script/GameplayCameras.CameraVariableCollection'/CameraModule/CVC_ThirdPerson.CVC_ThirdPerson'")))
			{
				for (auto& Variable : GeneraicCameraCollection->Variables)
				{
					if (const UVector3dCameraVariable* Vector3dCameraVariable = Cast<UVector3dCameraVariable>(Variable))
					{
						if (Vector3dCameraVariable->GetDisplayName() == "BoomOffset")
						{
							FVector BoomOffset = FVector(GetZoom(), 0.f, 0.f);
							BoomOffset = FVector(BoomOffset.X + BoomOffset.X * InValue * -0.1 * GetZoomSpeedRate(), 0.f, 0.f);

							// Table.GetVariableTable()->SetValue(Vector3dCameraVariable->GetVariableID(), Vector3dCameraVariable->GetVariableType(), reinterpret_cast<const uint8*>(&BoomOffset));

							Table.GetVariableTable()->SetValue(Vector3dCameraVariable, BoomOffset, true);
						}
					}
				}
			}
		}
	}
}

void AGenericCharacter::SetLocation_Implementation(FVector InValue)
{
	IPawnInputMovementInterface::Execute_SetLocation(InputMovementComponent, InValue);
}

void AGenericCharacter::SetRotation_Implementation(FRotator InValue)
{
	IPawnInputMovementInterface::Execute_SetRotation(InputMovementComponent, InValue);
}

void AGenericCharacter::SetZoom_Implementation(float InValue)
{
	if (InValue < 0)
	{
		return;
	}

	const FBlueprintCameraVariableTable Table = GameplayCamera->GetInitialVariableTable();
	if (Table.IsValid())
	{
		if (InputMovementComponent->GetActiveCameraRig() == ECameraRig::ThirdPerson)
		{
			FVector BoomOffset(InValue * -1, 0.f, 0.f);

			if (UCameraVariableCollection* GeneraicCameraCollection = LoadObject<UCameraVariableCollection>(nullptr,TEXT("/Script/GameplayCameras.CameraVariableCollection'/CameraModule/CVC_ThirdPerson.CVC_ThirdPerson'")))
			{
				for (auto& Variable : GeneraicCameraCollection->Variables)
				{
					if (const UVector3dCameraVariable* Vector3dCameraVariable = Cast<UVector3dCameraVariable>(Variable))
					{
						if (Vector3dCameraVariable->GetDisplayName() == "BoomOffset")
						{
							Table.GetVariableTable()->SetValue(Vector3dCameraVariable->GetVariableID(), Vector3dCameraVariable->GetVariableType(), reinterpret_cast<const uint8*>(&BoomOffset));
						}
					}
				}
			}
		}
	}
}

FVector AGenericCharacter::GetLocation()
{
	return InputMovementComponent->GetLocation();
}

FRotator AGenericCharacter::GetRotation()
{
	return InputMovementComponent->GetRotation();
}

float AGenericCharacter::GetZoom()
{
	const FBlueprintCameraVariableTable Table = GameplayCamera->GetInitialVariableTable();
	if (Table.IsValid())
	{
		FVector BoomOffset;

		if (InputMovementComponent->GetActiveCameraRig() == ECameraRig::ThirdPerson)
		{
			if (UCameraVariableCollection* GeneraicCameraCollection = LoadObject<UCameraVariableCollection>(nullptr,TEXT("/Script/GameplayCameras.CameraVariableCollection'/CameraModule/CVC_ThirdPerson.CVC_ThirdPerson'")))
			{
				for (auto& Variable : GeneraicCameraCollection->Variables)
				{
					if (const UVector3dCameraVariable* Vector3dCameraVariable = Cast<UVector3dCameraVariable>(Variable))
					{
						if (Vector3dCameraVariable->GetDisplayName() == "BoomOffset")
						{
							BoomOffset = Table.GetVariableTable()->GetValue<FVector3d>(Vector3dCameraVariable->GetVariableID());
							return BoomOffset.X;
						}
					}
				}
			}
		}
	}

	return IPawnInputMovementInterface::GetZoom();
}

float AGenericCharacter::GetMovementSpeedRate()
{
	return InputMovementComponent->GetMovementSpeedRate();
}

float AGenericCharacter::GetRotationSpeedRate()
{
	return InputMovementComponent->GetRotationSpeedRate();
}

float AGenericCharacter::GetZoomSpeedRate()
{
	return InputMovementComponent->GetZoomSpeedRate();
}
