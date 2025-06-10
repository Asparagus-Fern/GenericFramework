#include "Debug/DebugType.h"

/* ==================== Gameplay ==================== */
DEFINE_LOG_CATEGORY(GenericLogDefault);
DEFINE_LOG_CATEGORY(GenericLogManager);
DEFINE_LOG_CATEGORY(GenericLogProcedure);
DEFINE_LOG_CATEGORY(GenericLogUI);
DEFINE_LOG_CATEGORY(GenericLogCamera);
DEFINE_LOG_CATEGORY(GenericLogWorld);
DEFINE_LOG_CATEGORY(GenericLogProperty);
DEFINE_LOG_CATEGORY(GenericLogEvent);
DEFINE_LOG_CATEGORY(GenericLogMovieScene);

/* ==================== Misc ==================== */
DEFINE_LOG_CATEGORY(GenericLogExtraProc);

/* ==================== Communication ==================== */
DEFINE_LOG_CATEGORY(GenericLogJson);
DEFINE_LOG_CATEGORY(GenericLogHttp);
DEFINE_LOG_CATEGORY(GenericLogWebSocket);

extern FColor DErrorColor = FColor::Red;
extern FColor DWarningColor = FColor::Yellow;
extern FColor DMessageColor = FColor::Green;
extern float DPrintDuration = 20.f;
extern float DNotifyFadeInDuration = 0.5f;
extern float DNotifyFadeOutDuration = 0.5f;
extern float DNotifyDuration = 10.f;
