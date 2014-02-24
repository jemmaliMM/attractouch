#ifndef _MENU_SCREEN_H
#define _MENU_SCREEN_H

#include <sstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "utils/helper.h"
#include "gameplay/launcher.h"
#include "screens/screen.h"
#include "screens/screenmanager.h"
#include "screens/loadingscreen.h"
#include "screens/gamescreen.h"
#include "screens/videoscreen.h"
#include "screens/tutorialscreen.h"

namespace AT {

    class MenuScreen : public VideoScreen
    {
    protected:
        float transitionStartTime;

        Launcher launcher;
        float launcherTimer;

        std::string firstLevel;
        static bool IsFingerOK(const FingerData& FingerData, void *Data);
    public:
        MenuScreen(ScreenManager& ScreenManager, const std::string& FirstLevel = "");
        virtual ~MenuScreen();

        virtual void Load(sf::RenderTarget& Target);

        virtual void OnStateChange(ScreenState::Value OldState);

        virtual bool Process(sf::Event& Event);
        virtual bool Update(float TimeStep);

        virtual void Draw(sf::RenderTarget& Target);

        virtual void OnVideoStateChange(VideoState::Value OldState);
    };

}

#endif
