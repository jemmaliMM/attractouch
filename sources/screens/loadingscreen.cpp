#include "screens/loadingscreen.h"

namespace AT {
    LoadingScreen::LoadingScreen(ScreenManager& ScreenManager)
        :Screen(ScreenManager)
    {
        transitionOnTime = 1.0f;
        transitionOffTime = 1.0f;
    }

    LoadingScreen::~LoadingScreen()
    {
        
    }

    void LoadingScreen::Load(sf::RenderTarget& Target)
    {
        //if(!loadingFont.LoadFromFile("content/fonts/mido.otf", 32))
            //throw std::exception("Can't load loading font");
    }

    void LoadingScreen::OnStateChange(ScreenState::Value OldState)
    {
        if((OldState == ScreenState::TransitionOn || OldState == ScreenState::ToAdd) && state == ScreenState::Active) {
            for(Screens::iterator it = screens.begin(); it != screens.end(); ++it) {
                Screen *screen = *it;
                screen->Load(manager.GetTarget());
            }
            Exit();
        }
        if(state == ScreenState::ToRemove) {
            for(Screens::iterator it = screens.begin(); it != screens.end(); ++it) {
                Screen *screen = *it;
                screen->Show(false);
            }
        }
    }

    bool LoadingScreen::Process(sf::Event& event)
    {
        return true;
    }

    bool LoadingScreen::Update(float TimeStep)
    {
        Screen::Update(TimeStep);
        return false;
    }

    void LoadingScreen::Draw(sf::RenderTarget& Target)
    {
        /*static sf::String loadingString("Loading...", loadingFont, 32);

        sf::FloatRect rect = loadingString.GetRect();
        loadingString.SetPosition(Helper::BaseWidth / 2 - rect.GetWidth() / 2, Helper::BaseHeight / 2 - rect.GetHeight() / 2);
        Target.Draw(loadingString);*/
    }

    LoadingScreen* LoadingScreen::Add(Screen *screen)
    {
        screens.push_back(screen);
        return this;
    }
}