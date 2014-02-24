#ifndef _SCREEN_H
#define _SCREEN_H

#include <SFML/Graphics.hpp>

#include "screens/screenmanager.h"

namespace AT {

    namespace ScreenState {
        enum {
            ToAdd,
            TransitionOn,
            Active,
            TransitionOff,
            ToRemove
        };
        typedef unsigned long Value;
    }

    class ScreenManager;

    class Screen : public sf::Drawable
    {
    protected:
        ScreenManager& manager;
        
        ScreenState::Value state;

        float transitionOnTime;
        float transitionOffTime;
        float transitionPosition;
        float transitionAlpha;

        void SetState(ScreenState::Value State);
        void UpdateTransition(float TimeStep);
    public:
        Screen(ScreenManager& ScreenManager);
        virtual ~Screen();

        void Show(bool AutoLoad = true);
        void Exit();

        virtual void Load(sf::RenderTarget& Target) = 0;

        virtual bool Process(sf::Event& Event) = 0;
        virtual bool Update(float TimeStep);
        virtual void Draw(sf::RenderTarget& Target) = 0;

        virtual void Render(sf::RenderTarget& Target) const;

        virtual void OnStateChange(ScreenState::Value OldState) {}

        friend class ScreenManager;
    };

}

#endif
