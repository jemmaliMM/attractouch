#ifndef _SCREEN_MANAGER_H
#define _SCREEN_MANAGER_H

#include <deque>

//#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "screens/screen.h"

namespace AT {

    class Screen;
    class Game;

    class ScreenManager
    {
    protected:
        sf::Mutex mutex;

        typedef std::deque<Screen*> Screens;
        Screens screens;
        Screens screensToRemove;

        sf::RenderTarget& target;

        Game *game;
    public:
        ScreenManager(sf::RenderTarget& Target, Game *game);
        ~ScreenManager();

        Game& GetGame() const
        { return *game; }

        void Add(Screen *screen, bool AutoLoad = true);
        void Remove(Screen *screen);
        void Clear();

        void Process(sf::Event& Event);
        void Update(float TimeStep);
        void Draw();
        
        const Screens& GetScreens()
        { return screens; }
        sf::RenderTarget& GetTarget()
        { return target; }
    };

}

#endif
