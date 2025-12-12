#include "UMG/GenericLoadingScreen.h"

#include "WidgetType.h"
#include "MVVM/GenericLoadingScreenViewModel.h"

void UGenericLoadingScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bFinishLoad)
	{
		if (LoadPercentage != TargetLoadPercentage)
		{
			LoadPercentage = FMath::Clamp(FMath::Lerp(LoadPercentage, TargetLoadPercentage, InDeltaTime), 0.f, TargetLoadPercentage);
		}

		if (GetIsFinished())
		{
			bFinishLoad = true;
			OnLoadFinished();
			OnLoadFinishedEvent.Broadcast();
		}
	}
}

void UGenericLoadingScreen::SetLoadCount(int32 InLoadCount)
{
	LoadCount = InLoadCount;
	OnTargetPercentageChanged(0.f);
}

void UGenericLoadingScreen::NotifyLoadOnceFinish()
{
	CurrentLoadCount++;
	TargetLoadPercentage = FMath::Clamp((float)CurrentLoadCount / (float)LoadCount, 0.f, 1.f);
	OnTargetPercentageChanged(TargetLoadPercentage);
}

UGenericLoadingScreenViewModel* UGenericLoadingScreen::GetLoadingScreenViewModel() const
{
	return LoadingScreenViewModel;
}

bool UGenericLoadingScreen::GetIsFinished() const
{
	return FMath::IsNearlyEqual(LoadPercentage, 1.f, 0.01f) && CurrentLoadCount == LoadCount;
}

void UGenericLoadingScreen::SetLoadingScreenViewModel_Implementation(UGenericLoadingScreenViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(LoadingScreenViewModel)
	LoadingScreenViewModel = InViewModel;
}

void UGenericLoadingScreen::OnTargetPercentageChanged_Implementation(float Percentage)
{
}

void UGenericLoadingScreen::OnLoadFinished_Implementation()
{
}
