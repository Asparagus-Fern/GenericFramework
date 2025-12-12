// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericWindowWrapper.h"

#include "GenericWindowContent.h"
#include "GenericWindowType.h"
#include "GenericWindowViewModel.h"
#include "Blueprint/UserWidget.h"

// #include "Interfaces/IMainFrameModule.h"

UGenericWindowWrapper::UGenericWindowWrapper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WindowContentClass = LoadClass<UGenericWindowContent>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/GenericWidget/UMG/WBP_WindowContent_Empty.WBP_WindowContent_Empty_C'"));
}

bool UGenericWindowWrapper::Initialize(UGenericWindowViewModel* InViewModel)
{
	if (!InViewModel)
	{
		GenericLOG(GenericLogWindow, Error, TEXT("InViewModel Is InValid"))
		return false;
	}

	if (!IsValid(GetOwnerPlayer()))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Must Provide a Valid Player As Outer"))
		return false;
	}

	Window = InViewModel->GetWindow();

	if (!Window.IsValid())
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Must Provide a Valid Window From Window View Model"))
		return false;
	}

	SetWindowViewModel(InViewModel);

	return true;
}

void UGenericWindowWrapper::Deinitialize()
{
	if (Window.IsValid())
	{
		Window->GetOnWindowClosedEvent().RemoveAll(this);
		CloseWindow();
	}

	Window.Reset();
	WindowContent.Reset();
}

APlayerController* UGenericWindowWrapper::GetOwnerPlayer() const
{
	return Cast<APlayerController>(GetOuter());
}

void UGenericWindowWrapper::OpenWindow()
{
	if (FSlateApplication::Get().CanDisplayWindows() && Window.IsValid() && !Window->IsVisible())
	{
		Window->GetOnWindowClosedEvent().AddUObject(this, &UGenericWindowWrapper::HandleOnWindowClosed);

		if (WindowContent.IsValid())
		{
			Window->SetContent(WindowContent.ToSharedRef());
		}

		if (WindowViewModel->IsModalWindow)
		{
			// IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
			// TSharedPtr<SWindow> ParentWindow = MainFrame.GetParentWindow();
			// if (ParentWindow.IsValid())
			// {
			// 	FSlateApplication::Get().AddModalWindow(Window.ToSharedRef(), ParentWindow);
			// 	OnWindowOpened.Broadcast();
			// }
		}
		else
		{
			FSlateApplication::Get().AddWindow(Window.ToSharedRef());
			OnWindowOpened.Broadcast();
		}
	}
}

void UGenericWindowWrapper::CloseWindow()
{
	Window->SetContent(SNullWidget::NullWidget);

	if (Window.IsValid())
	{
		FSlateApplication::Get().RequestDestroyWindow(Window.ToSharedRef());
	}
}

UGenericWindowViewModel* UGenericWindowWrapper::GetWindowViewModel() const
{
	return WindowViewModel;
}

void UGenericWindowWrapper::SetWindowViewModel(UGenericWindowViewModel* InWindowViewModel)
{
	UNREGISTER_MVVM_PROPERTY(WindowViewModel)
	WindowViewModel = InWindowViewModel;

	if (WindowViewModel)
	{
	}
}

UGenericWindowContent* UGenericWindowWrapper::GetWindowContentObject()
{
	return WindowContentObject;
}

void UGenericWindowWrapper::SetWindowContentObjectByClass(TSubclassOf<UUserWidget> InWidgetClass)
{
	if (!InWidgetClass)
	{
		GenericLOG(GenericLogWindow, Error, TEXT("InWidgetClass Is InValid"))
		return;
	}

	UUserWidget* NewWidget = CreateWidget(GetOwnerPlayer(), InWidgetClass);
	SetWindowContentObject(NewWidget);
}

void UGenericWindowWrapper::SetWindowContentObject(UUserWidget* InWidget)
{
	if (IsValid(InWidget))
	{
		if (WindowContentObject)
		{
			WindowContentObject->SetWindowWrapper(nullptr);
		}

		if (UGenericWindowContent* GenericWindowContent = Cast<UGenericWindowContent>(InWidget))
		{
			WindowContentObject = GenericWindowContent;
		}
		else
		{
			WindowContentObject = CreateWidget<UGenericWindowContent>(GetOwnerPlayer(), WindowContentClass);
			WindowContentObject->AddChild(InWidget);
		}

		WindowContentObject->SetWindowWrapper(this);
		SetWindowContent(WindowContentObject->TakeWidget());
	}
}

TSharedPtr<SWidget> UGenericWindowWrapper::GetWindowContent()
{
	return WindowContent;
}

void UGenericWindowWrapper::SetWindowContent(TSharedPtr<SWidget> InWindowContent)
{
	if (WindowContent != InWindowContent)
	{
		WindowContent.Reset();
	}

	WindowContent = InWindowContent.IsValid() ? InWindowContent : SNullWidget::NullWidget;;

	if (Window.IsValid())
	{
		Window->SetContent(WindowContent.ToSharedRef());
	}
}

void UGenericWindowWrapper::HandleOnWindowClosed(const TSharedRef<SWindow>& InWindow)
{
	Window.Reset();
	Window = WindowViewModel->GetWindow();
	OnWindowClosed.Broadcast();
}
