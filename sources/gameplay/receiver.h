#ifndef _RECEIVER_H
#define _RECEIVER_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils/helper.h"
#include "multitouch/oscmessenger.h"
#include "particles/particlesystem.h"
#include "gameplay/gameplayparticle.h"

namespace AT {

    class Receiver : public sf::Drawable
    {
    protected:
        int maximumParticles;
        int receivedParticles;

        float radius;

        sf::Color colorStart;
        sf::Color colorEnd;
        float alpha;

        static bool loaded;
        static sf::Image image;
        static sf::Sprite sprite;
    public:
        Receiver(const sf::Vector2f Position = sf::Vector2f(0.0f, 0.0f), int MaximumParticles = 0, float Radius = 0.0f);
        virtual ~Receiver();

        int GetMaximumParticles() const
        { return maximumParticles; }
        void SetMaximumParticles(int MaximumParticles)
        { maximumParticles = MaximumParticles; }

        int GetReceivedParticles() const
        { return receivedParticles; }

        void SetAlpha(float Alpha)
        {
            alpha = Alpha;
            colorStart.a = colorEnd.a = int(alpha * 255);
        }

        void Update(float TimeStep, ParticleSystem& particleSystem);

        virtual void Render(sf::RenderTarget& Target) const;
    };
}

#endif
