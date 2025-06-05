#include "Debug/DebugType.h"

DEFINE_LOG_CATEGORY(DefaultLog);
DEFINE_LOG_CATEGORY(ObjectLog);
DEFINE_LOG_CATEGORY(ManagerLog);
DEFINE_LOG_CATEGORY(ProcedureLog);
DEFINE_LOG_CATEGORY(UILog);
DEFINE_LOG_CATEGORY(CameraLog);
DEFINE_LOG_CATEGORY(WorldLog);
DEFINE_LOG_CATEGORY(PropertyLog);
DEFINE_LOG_CATEGORY(EventLog);
DEFINE_LOG_CATEGORY(MovieSceneLog);
DEFINE_LOG_CATEGORY(TerrainLog);
DEFINE_LOG_CATEGORY(NetworkLog);
DEFINE_LOG_CATEGORY(JsonLog);

extern FColor DErrorColor = FColor::Red;
extern FColor DWarningColor = FColor::Yellow;
extern FColor DMessageColor = FColor::Green;
extern float DPrintDuration = 20.f;
extern float DNotifyFadeInDuration = 0.5f;
extern float DNotifyFadeOutDuration = 0.5f;
extern float DNotifyDuration = 10.f;
