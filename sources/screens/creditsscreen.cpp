#include "screens/creditsscreen.h"

namespace AT {

    CreditsScreen::CreditsScreen(ScreenManager &ScreenManager)
        :VideoScreen(ScreenManager, "content/videos/credits.flv")
    {
        transitionOnTime = 1.0f;
        transitionOffTime = 1.0f;

        videoScale = 2.0f;

        SetBlendMode(sf::Blend::Add);
    }

    CreditsScreen::~CreditsScreen()
    {

    }

    bool CreditsScreen::IsFingerOK(const FingerData& FingerData, void *Data)
    {
        CreditsScreen& creditsScreen = *static_cast<CreditsScreen*>(Data);

        if(creditsScreen.state != ScreenState::Active)
            return false;

        if(FingerManager::Instance().NFingers() >= 5) {
            creditsScreen.Exit();
        }

        return true;
    }

    void CreditsScreen::OnStateChange(ScreenState::Value OldState)
    {
        if(state == ScreenState::Active) {
            OSCMessenger::Instance().Credits();
            FingerManager::Instance().SetIsFingerOK(IsFingerOK, this);
            SetVideoState(VideoState::Playing);
            if(manager.GetGame().HasSmokeScreen()) {
                manager.GetGame().GetSmokeScreen().ApplyNoise(false);
            }
        }
        if(state == ScreenState::ToRemove) {
            (new LoadingScreen(manager))->Add(new MenuScreen(manager))->Show();
        }
    }

    bool CreditsScreen::Process(sf::Event& Event)
    {
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space)) {
            Exit();
        }
        return false;
    }

    void CreditsScreen::OnVideoStateChange(VideoState::Value OldState)
    {
        if(videoState == VideoState::Stopped) {
            Exit();
        }
    }
}