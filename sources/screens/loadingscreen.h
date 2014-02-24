#ifndef _LOADING_SCREEN_H
#define _LOADING_SCREEN_H

#include <deque>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils/helper.h"
#include "screens/screenmanager.h"
#include "screens/screen.h"

namespace AT {

    class LoadingScreen : public Screen
    {
    protected:
        typedef std::deque<Screen*> Screens;
        Screens screens;

        sf::Font loadingFont;
    public:
        LoadingScreen(ScreenManager& ScreenManager);
        virtual ~LoadingScreen();

        virtual void Load(sf::RenderTarget& Target);

        virtual void OnStateChange(ScreenState::Value OldState);

        virtual bool Process(sf::Event& event);
        virtual bool Update(float TimeStep);
        virtual void Draw(sf::RenderTarget& Target);

        virtual LoadingScreen* Add(Screen *screen);
    };

}

#endif
