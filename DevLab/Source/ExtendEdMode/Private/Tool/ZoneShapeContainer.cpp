// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Tool/ZoneShapeContainer.h"

#include "ZoneShapeComponent.h"


AZoneShapeContainer::AZoneShapeContainer()
{
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	ZoneShapeComponent = CreateDefaultSubobject<UZoneShapeComponent>(TEXT("ZoneShapeComponent"));
	
	RootComponent = ZoneShapeComponent;
	ZoneShapeComponent->SetupAttachment(SceneComponent);

	SetHidden(true);
	SetCanBeDamaged(false);
	PrimaryActorTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	bIsSpatiallyLoaded = false;
#endif
}
