#ifndef _GAMEPLAY_PARTICLE_H
#define _GAMEPLAY_PARTICLE_H

#include <iostream>

#include "utils/helper.h"
#include "particles/particle.h"

namespace AT {

    class GameplayParticle : public Particle
    {
    protected:
        float constantVelocity;
        bool isConstrained;
        bool isReceived;
        bool isDead;

        float timeToDisappear;
        float timeReceived;
        float alphaReceived;

        float timeBeforeDying;
        float timeDying;
        float timeToDie;
        float timeDead;
        float alphaDead;

        float ratioFinger;

        sf::Color colorStart;
        sf::Color colorEnd;
        sf::Color colorDead;

        sf::Color colorRender;

        float alphaRender;
    public:
        GameplayParticle(float ConstantVelocity);
        virtual ~GameplayParticle();

        float GetConstantVelocity() const
        { return constantVelocity; }

        bool IsConstrained() const
        { return isConstrained; }
        void SetConstrained(bool Value)
        {
            isConstrained = Value;
            timeDying = timeDead = 0.0f;
        }

        bool IsReceived() const
        { return isReceived; }
        void SetReceived(bool Value)
        { isReceived = Value; }

        bool IsDead() const
        { return isDead; }

        const sf::Color& GetColor() const
        { return colorRender; }
        void SetFingerRatio(float Ratio)
        { ratioFinger = Ratio; }

        float GetAlpha() const
        { return alphaRender; }

        virtual void Update(float TimeStep);
    };
}

#endif