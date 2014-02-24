#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include <iostream>
#include <vector>

#include "multitouch/oscmessenger.h"
#include "multitouch/fingermanager.h"
#include "screens/screen.h"
#include "screens/smokescreen.h"
#include "screens/menuscreen.h"
#include "screens/creditsscreen.h"
#include "utils/helper.h"
#include "utils/fluidfield.h"
#include "utils/constants.h"
#include "gameplay/launcher.h"
#include "gameplay/receiver.h"
#include "gameplay/wall.h"
#include "gameplay/trajectoryconstraint.h"
#include "gameplay/flow.h"
#include "particles/particlesystem.h"
#include "schemas/level-xml.h"
#include "game.h"

namespace AT {

    class GameScreen : public Screen
    {
    public:
        typedef std::vector<Launcher*> Launchers;
        typedef std::vector<Wall*> Walls;
    private:
        std::string levelName;
        int levelPreviousParticles;
        std::string nextLevel;
        sf::Vector2f levelNextStart;
        sf::Vector2f levelPreviousStart;

        Launcher *mainLauncher;
        Launchers optionalLaunchers;
        //Receiver *receiver;
        Receiver receiver;
        Walls walls;
        Flow flow;

        ParticleSystem particleSystem;

        sf::Image fingerImage;
        sf::Sprite fingerSprite;
        sf::Image particleImage;
        sf::Sprite particleSprite;

        bool isUpdating;
        bool isStepping;
        bool debug;

        void Clear();

        void LoadLevel();
        void NextLevel();

        static bool IsFingerOK(const FingerData& FingerData, void *Data);
    public:
        GameScreen(ScreenManager& ScreenManager);
        virtual ~GameScreen();

        virtual void Load(sf::RenderTarget& Target);

        virtual void OnStateChange(ScreenState::Value OldState);

        virtual bool Process(sf::Event& Event);
        virtual bool Update(float TimeStep);
        virtual void Draw(sf::RenderTarget& Target);

        GameScreen* SetLevel(const std::string& Name, int PreviousParticles = 0)
        { levelName = Name; levelPreviousParticles = PreviousParticles; return this; }
    };

}

#endif
