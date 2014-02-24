#include "screens/screen.h"
#include "screens/screenmanager.h"

namespace AT {

    Screen::Screen(ScreenManager& ScreenManager)
        :manager(ScreenManager), state(ScreenState::ToAdd), transitionOnTime(0.0f), transitionOffTime(0.0f), transitionPosition(0.0f), transitionAlpha(0.0f)
    {
        
    }

    Screen::~Screen()
    {

    }

    void Screen::SetState(ScreenState::Value State)
    {
        ScreenState::Value OldState = state;
        state = State;
        OnStateChange(OldState);

        if(state == ScreenState::ToRemove) {
            manager.Remove(this);
        }
    }

    bool Screen::Update(float TimeStep)
    {
        if (state == ScreenState::TransitionOn || state == ScreenState::TransitionOff)
            transitionPosition += TimeStep;
        
        if(state == ScreenState::TransitionOn && transitionOnTime > 0.0f) {
            transitionAlpha = transitionPosition / transitionOnTime;
            if(transitionPosition >= transitionOnTime)
                SetState(ScreenState::Active);
        }
        if(state == ScreenState::TransitionOff && transitionOffTime > 0.0f) {
            transitionAlpha = 1.0f - transitionPosition / transitionOffTime;
            if(transitionPosition >= transitionOffTime) {
                SetState(ScreenState::ToRemove);
            }
        }
        if(transitionAlpha < 0.0f)
            transitionAlpha = 0.0f;
        if(transitionAlpha > 1.0f)
            transitionAlpha = 1.0f;

        return false;
    }

    void Screen::Show(bool AutoLoad)
    {
        if(state == ScreenState::ToAdd) {
            manager.Add(this);
            if(AutoLoad)
                Load(manager.GetTarget());
        }

        if(transitionOnTime <= 0.0f) {
            transitionAlpha = 1.0f;
            SetState(ScreenState::Active);
            return;
        }
        SetState(ScreenState::TransitionOn);
        transitionPosition = transitionAlpha * transitionOnTime;
    }

    void Screen::Exit()
    {
        if(transitionOffTime <= 0.0f) {
            transitionAlpha = 1.0f;
            SetState(ScreenState::Active);
            return;
        }
        SetState(ScreenState::TransitionOff);
        transitionPosition = (1.0f - transitionAlpha) * transitionOffTime;
    }

    void Screen::Render(sf::RenderTarget& Target) const
    {
        // dirty trick but works
        const_cast<Screen*>(this)->Draw(Target);
    }

}