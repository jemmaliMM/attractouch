#include "screens/menuscreen.h"

namespace AT {

    MenuScreen::MenuScreen(ScreenManager& ScreenManager, const std::string& FirstLevel)
        :VideoScreen(ScreenManager, "content/videos/intro.flv"), firstLevel(FirstLevel), launcher(sf::Vector2f(951.0f, 611.0f), 0.0f, 0, 0.0f, 0.0f, 100.0f)
    {
        transitionOnTime = 0.0f; // set to duration after loading
        transitionOffTime = 1.0f;

        transitionStartTime = 2.0f;

        videoScale = 2.0f;

        SetBlendMode(sf::Blend::Add);

        launcherTimer = 0.0f;
        if(firstLevel.empty()) {
            firstLevel = Constants::Instance().FirstLevel();
        }
    }

    MenuScreen::~MenuScreen()
    {

    }

    bool MenuScreen::IsFingerOK(const FingerData& FingerData, void *Data)
    {
        MenuScreen& menuScreen = *static_cast<MenuScreen*>(Data);

        if(menuScreen.state != ScreenState::Active)
            return false;

        if(FingerManager::Instance().NFingers() >= 1)
            return false;

        sf::Vector2f fingerPosition(FingerData.ScreenX(Helper::BaseWidth), FingerData.ScreenY(Helper::BaseHeight));

        float distance = Helper::Distance(menuScreen.launcher.GetPosition(), fingerPosition);
        if(distance > menuScreen.launcher.GetRadius())
            return false;

        menuScreen.Exit();

        return true;
    }

    void MenuScreen::Load(sf::RenderTarget& Target)
    {
        VideoScreen::Load(Target);
        transitionOnTime = duration + transitionStartTime;
    }

    void MenuScreen::OnStateChange(ScreenState::Value OldState)
    {
        if(state == ScreenState::ToRemove) {
            //(new LoadingScreen(manager))->Add((new GameScreen(manager))->SetLevel(firstLevel))->Show();
            (new LoadingScreen(manager))->Add(new TutorialScreen(manager, firstLevel))->Show();
        }
        if(state == ScreenState::Active) {
            OSCMessenger::Instance().Menu();
            FingerManager::Instance().SetIsFingerOK(IsFingerOK, this);
            if(manager.GetGame().HasSmokeScreen()) {
                manager.GetGame().GetSmokeScreen().ApplyNoise(true);
            }
        }
        if(state == ScreenState::TransitionOn) {
            SetVideoState(VideoState::Playing);
            OSCMessenger::Instance().Intro();
            if(manager.GetGame().HasSmokeScreen()) {
                manager.GetGame().GetSmokeScreen().ApplyNoise(false);
            }
        }
    }

    bool MenuScreen::Process(sf::Event& Event)
    {
        return true;
    }

    bool MenuScreen::Update(float TimeStep)
    {
        VideoScreen::Update(TimeStep);

        if(state == ScreenState::Active) {
            launcherTimer += TimeStep;
        }
        if(state == ScreenState::TransitionOn) {
            if(manager.GetGame().HasSmokeScreen()) {
                FluidField& fluidField = manager.GetGame().GetSmokeScreen().GetFluidField();
                for(int i = 0; i < fluidField.GetGridWidth(); ++i) {
                    float x = fluidField.GetCellWidth() * (i + 0.5f);
                    fluidField.AddDensity(x, fluidField.GetHeight() - fluidField.GetCellHeight() * 0.5f, transitionAlpha * 10.0f);
                    fluidField.AddVelocity(x, fluidField.GetHeight() - fluidField.GetCellHeight() * 0.5f, 0.0f, -1.0f);
                    fluidField.AddDensity(x, fluidField.GetCellHeight() * 0.5f, transitionAlpha * 10.0f);
                    fluidField.AddVelocity(x, fluidField.GetCellHeight() * 0.5f, 0.0f, 1.0f);
                }
            }
        }

        return false;
    }

    void MenuScreen::Draw(sf::RenderTarget& Target)
    {
        VideoScreen::Draw(Target);

        float launcherPulse = (sin(launcherTimer * 10.0f) + 1.0f) * 0.5f;
        launcher.SetScale(1.0f + launcherPulse * 0.5f, 1.0f + launcherPulse * 0.5f);

        if(transitionPosition > duration) {
            float alpha = (transitionPosition - duration) / transitionStartTime;
            launcher.SetAlpha(alpha);
            Target.Draw(launcher);
            videoAlpha = 1.0f - alpha;
        }
        if(state == ScreenState::TransitionOff) {
            launcher.SetAlpha(transitionAlpha);
            Target.Draw(launcher);
        }
    }

    void MenuScreen::OnVideoStateChange(VideoState::Value OldState)
    {
        if(videoState == VideoState::Playing) {
            std::cout << "Play!" << std::endl;
        }
        if(videoState == VideoState::Stopped) {
            std::cout << "Stop!" << std::endl;
        }
    }

}