#include "screens/screenmanager.h"
#include <SFML/System.hpp>

namespace AT {

    ScreenManager::ScreenManager(sf::RenderTarget& Target, Game *Game)
        :target(Target), game(Game)
    {

    }

    ScreenManager::~ScreenManager()
    {
        Clear();
    }

    void ScreenManager::Add(Screen *screen, bool AutoLoad)
    {
        screens.push_back(screen);
    }

    void ScreenManager::Remove(Screen *screen)
    {
        screensToRemove.push_back(screen);
    }

    void ScreenManager::Clear()
    {
        for(Screens::iterator it = screens.begin(); it != screens.end(); ++it) {
            Screen *screen = *it;
            delete screen;
            *it = NULL;
        }
        screens.clear();
    }

    void ScreenManager::Process(sf::Event& Event)
    {
        Screens screensToProcess;

        for(Screens::reverse_iterator it = screens.rbegin(); it != screens.rend(); ++it)
            screensToProcess.push_back(*it);

        while(!screensToProcess.empty()) {
            Screen *screen = screensToProcess.front();
            if(screen->Process(Event))
                break;
            screensToProcess.pop_front();
        }
    }

    void ScreenManager::Update(float TimeStep)
    {
        Screens screensToUpdate;

        for(Screens::reverse_iterator it = screens.rbegin(); it != screens.rend(); ++it)
            screensToUpdate.push_back(*it);

        while(!screensToUpdate.empty()) {
            Screen *screen = screensToUpdate.front();
            if(screen->Update(TimeStep))
                break;
            screensToUpdate.pop_front();
        }
        
        // remove screens
        for(Screens::iterator it = screens.begin(); it != screens.end();) {
            Screen *screen = *it;

            bool removed = false;
            for(Screens::iterator itR = screensToRemove.begin(); itR != screensToRemove.end();) {
                Screen *screenToRemove = *itR;
                if(screen == screenToRemove) {
                    it = screens.erase(it);
                    removed = true;
                    itR = screensToRemove.erase(itR);

                    delete screen;
                } else {
                    ++itR;
                }
            }
            if(!removed)
                ++it;
        }
    }

    void ScreenManager::Draw()
    {
        for(Screens::iterator it = screens.begin(); it != screens.end(); ++it) {
            Screen *screen = *it;
            target.Draw(*screen);
        }
    }

}