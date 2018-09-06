#include "pch.h"

#include "App.h"
#include "MainPage.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace winrtapp2;
using namespace winrtapp2::implementation;

App::App() {
  InitializeComponent();
  Suspending({ this, &App::OnSuspending });

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
  UnhandledException([this](IInspectable const&, UnhandledExceptionEventArgs const& e)
  {
    if (IsDebuggerPresent())
    {
      auto errorMessage = e.Message();
      __debugbreak();
    }
  });
#endif
}

void App::OnLaunched(LaunchActivatedEventArgs const& e) {
  Frame rootFrame{ nullptr };
  auto content = Window::Current().Content();
  if (content)
  {
    rootFrame = content.try_as<Frame>();
  }

  // Do not repeat app initialization when the Window already has content,
  // just ensure that the window is active
  if (rootFrame == nullptr)
  {
    // Create a Frame to act as the navigation context and associate it with
    // a SuspensionManager key
    rootFrame = Frame();

    rootFrame.NavigationFailed({ this, &App::OnNavigationFailed });

    if (e.PreviousExecutionState() == ApplicationExecutionState::Terminated)
    {
      // Restore the saved session state only when appropriate, scheduling the
      // final launch steps after the restore is complete
    }

    if (e.PrelaunchActivated() == false)
    {
      if (rootFrame.Content() == nullptr)
      {
        // When the navigation stack isn't restored navigate to the first page,
        // configuring the new page by passing required information as a navigation
        // parameter
        rootFrame.Navigate(xaml_typename<winrtapp2::MainPage>(), box_value(e.Arguments()));
      }
      // Place the frame in the current Window
      Window::Current().Content(rootFrame);
      // Ensure the current window is active
      Window::Current().Activate();
    }
  }
  else
  {
    if (e.PrelaunchActivated() == false)
    {
      if (rootFrame.Content() == nullptr)
      {
        // When the navigation stack isn't restored navigate to the first page,
        // configuring the new page by passing required information as a navigation
        // parameter
        rootFrame.Navigate(xaml_typename<winrtapp2::MainPage>(), box_value(e.Arguments()));
      }
      // Ensure the current window is active
      Window::Current().Activate();
    }
  }
}

void App::OnSuspending([[maybe_unused]] IInspectable const& sender, [[maybe_unused]] SuspendingEventArgs const& e) {
  // TODO: Save application state and stop any background activity
}

void App::OnNavigationFailed(IInspectable const&, NavigationFailedEventArgs const& e) {
  throw hresult_error(E_FAIL, hstring(L"Failed to load Page ") + e.SourcePageType().Name);
}
