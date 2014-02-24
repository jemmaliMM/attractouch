#ifndef _TUTORIAL_SCREEN_H
#define _TUTORIAL_SCREEN_H

#include "multitouch/fingermanager.h"
#include "screens/videoscreen.h"
#include "screens/gamescreen.h"

namespace AT {

    class TutorialScreen : public VideoScreen
    {
    protected:
        std::string firstLevel;
        static bool IsFingerOK(const FingerData& FingerData, void *Data);
    public:
        TutorialScreen(ScreenManager& ScreenManager, const std::string& FirstLevel);
        virtual ~TutorialScreen();

        virtual void OnStateChange(ScreenState::Value OldState);

        virtual bool Process(sf::Event& Event);

        virtual void OnVideoStateChange(VideoState::Value OldState);
    };

}

#endif