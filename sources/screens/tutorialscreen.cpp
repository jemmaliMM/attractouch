#include "screens/tutorialscreen.h"

namespace AT {

    TutorialScreen::TutorialScreen(ScreenManager &ScreenManager, const std::string &FirstLevel)
        :VideoScreen(ScreenManager, "content/videos/tutorial.flv"), firstLevel(FirstLevel)
    {
        transitionOnTime = 1.0f;
        transitionOffTime = 1.0f;

        videoScale = 2.0f;

        SetBlendMode(sf::Blend::Add);
    }

    TutorialScreen::~TutorialScreen()
    {

    }

    bool TutorialScreen::IsFingerOK(const FingerData& FingerData, void *Data)
    {
        TutorialScreen& tutorialScreen = *static_cast<TutorialScreen*>(Data);

        if(tutorialScreen.state != ScreenState::Active)
            return false;

        if(FingerManager::Instance().NFingers() >= 5) {
            tutorialScreen.Exit();
        }

        return true;
    }

    void TutorialScreen::OnStateChange(ScreenState::Value OldState)
    {
        if(state == ScreenState::Active) {
            FingerManager::Instance().SetIsFingerOK(IsFingerOK, this);
            SetVideoState(VideoState::Playing);
            if(manager.GetGame().HasSmokeScreen()) {
                manager.GetGame().GetSmokeScreen().ApplyNoise(false);
            }
        }
        if(state == ScreenState::ToRemove) {
            (new LoadingScreen(manager))->Add((new GameScreen(manager))->SetLevel(firstLevel))->Show();
        }
    }

    bool TutorialScreen::Process(sf::Event& Event)
    {
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space)) {
            Exit();
        }
        return false;
    }

    void TutorialScreen::OnVideoStateChange(VideoState::Value OldState)
    {
        if(videoState == VideoState::Stopped) {
            std::cout << "Start Game!" << std::endl;
            Exit();
        }
    }
}