#ifndef _LAUNCHER_H
#define _LAUNCHER_H

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "gameplay/gameplayparticle.h"
#include "particles/particlesystem.h"
#include "schemas/level-xml.h"

namespace AT {

    namespace LauncherState {
        enum {
            Waiting,
            Active,
            Empty
        };
        typedef unsigned long Value;
    }

    class Launcher : public sf::Drawable
    {
    private:
        int initialParticles;
        float speed;
        float rate;
        float radius;

        sf::Vector2f initialVelocity;

        sf::Color colorStart;
        sf::Color colorEnd;
        float alpha;

        LauncherState::Value state;
        int launchedParticles;
        float timeStepAccumulator;

        static bool loaded;
        static sf::Image image;
        static sf::Sprite sprite;
    public:
        Launcher(const sf::Vector2f Position, float Rotation, int InitialParticles, float Speed, float Rate, float Radius);
        virtual ~Launcher();

        float GetRadius() const
        { return radius; }

        LauncherState::Value GetState() const
        { return state; }
        bool IsEmpty() const
        { return state == LauncherState::Empty; }
        int GetInitialParticles() const
        { return initialParticles; }

        void SetAlpha(float Alpha)
        {
            alpha = Alpha;
            colorStart.a = colorEnd.a = int(alpha * 255);
        }

        void Activate()
        { state = LauncherState::Active; }

        void Launch(ParticleSystem& particleSystem);
        void Update(float TimeStep, ParticleSystem& particleSystem);

        virtual void Render(sf::RenderTarget& Target) const;
    };
}

#endif
