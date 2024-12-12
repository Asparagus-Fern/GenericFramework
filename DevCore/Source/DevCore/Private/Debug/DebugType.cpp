#include "Debug/DebugType.h"

DEFINE_LOG_CATEGORY(DLogDefault);
DEFINE_LOG_CATEGORY(DLogManager);
DEFINE_LOG_CATEGORY(DLogProcedure);
DEFINE_LOG_CATEGORY(DLogUI);
DEFINE_LOG_CATEGORY(DLogCamera);
DEFINE_LOG_CATEGORY(DLogWorld);
DEFINE_LOG_CATEGORY(DLogProperty);
DEFINE_LOG_CATEGORY(DLogMovieScene);

extern FColor DErrorColor = FColor::Red;
extern FColor DWarningColor = FColor::Yellow;
extern FColor DMessageColor = FColor::Green;
extern float DPrintDuration = 10.f;
extern float DNotifyFadeInDuration = 0.5f;
extern float DNotifyFadeOutDuration = 0.5f;
extern float DNotifyDuration = 10.f;
