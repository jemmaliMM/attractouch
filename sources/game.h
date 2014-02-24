#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>

#include "multitouch/oscmessenger.h"
#include "multitouch/fingermanager.h"
#include "multitouch/fingersimulator.h"
#include "screens/screenmanager.h"
#include "screens/menuscreen.h"
#include "screens/gamescreen.h"
#include "screens/smokescreen.h"
#include "screens/videoscreen.h"
#include "utils/helper.h"

namespace AT {

    class SmokeScreen;
    class MenuScreen;

    namespace GameState {
        enum {
            Menu,
            Game,
            Credits
        };
        typedef unsigned long Value;
    }

    class Game
    {
    protected:
        ScreenManager screenManager;

        SmokeScreen *smokeScreen;
        MenuScreen *menuScreen;

        GameState::Value gameState;

        std::string firstLevel;
    public:
        Game(sf::RenderWindow& Window, int PortTUIO, int PortOSC, bool SkipMenu, const std::string& FirstLevel);
        ~Game();

        GameState::Value GetState() const
        { return gameState; }
        void SetState(GameState::Value State);

        bool HasSmokeScreen() const
        { return smokeScreen != NULL; }
        SmokeScreen& GetSmokeScreen() const
        { return *smokeScreen; }

        void Process(sf::Event& Event);
        void Update(float TimeStep);
        void Draw();
    };

}

#endif
