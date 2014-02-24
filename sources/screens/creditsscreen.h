#ifndef _CREDITS_SCREEN_H
#define _CREDITS_SCREEN_H

#include "multitouch/fingermanager.h"
#include "screens/videoscreen.h"
#include "screens/gamescreen.h"

namespace AT {

    class CreditsScreen : public VideoScreen
    {
    protected:
        static bool IsFingerOK(const FingerData& FingerData, void *Data);
    public:
        CreditsScreen(ScreenManager& ScreenManager);
        virtual ~CreditsScreen();

        virtual void OnStateChange(ScreenState::Value OldState);

        virtual bool Process(sf::Event& Event);

        virtual void OnVideoStateChange(VideoState::Value OldState);
    };

}

#endif