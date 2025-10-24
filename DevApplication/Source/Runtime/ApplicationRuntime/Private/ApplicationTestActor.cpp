// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ApplicationTestActor.h"

#include "Type/DebugType.h"

void AApplicationTestActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &AApplicationTestActor::TimerTest), 2.f, true);
}

void AApplicationTestActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	TimerHandle.Invalidate();
}

void AApplicationTestActor::TimerTest()
{
#if PLATFORM_ANDROID
	// GenericPRINT(Log, TEXT("Android ID : %s"), *FStaticFunctions_Android::GetAndroidID())
#endif
}

void AApplicationTestActor::TestMessageDialog(FText Message)
{
	FMessageDialog::Open(EAppMsgType::YesNoYesAllNoAllCancel, Message);
}
