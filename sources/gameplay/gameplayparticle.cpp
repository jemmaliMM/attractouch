#include "gameplay/gameplayparticle.h"

namespace AT {

    GameplayParticle::GameplayParticle(float ConstantVelocity)
        :constantVelocity(ConstantVelocity), isConstrained(false), isReceived(false), isDead(false)
    {
        timeToDisappear = 2.0f;
        timeReceived = 0.0f;

        timeBeforeDying = 10.0f;
        timeToDie = 4.0f;
        timeDying = 0.0f;
        timeDead = 0.0f;

        colorStart = sf::Color(255, 255, 0);
        colorEnd = sf::Color(94, 0, 0);
        colorDead = sf::Color(128, 128, 128);

        alphaRender = 1.0f;

        SetFingerRatio(0.0f);
    }

    GameplayParticle::~GameplayParticle()
    {
        
    }

    void GameplayParticle::Update(float TimeStep)
    {
        Particle::Update(TimeStep);

        timeDying += TimeStep;
        if(timeDying >= timeBeforeDying) {
            timeDead += TimeStep;
            alphaDead = Helper::Clamp(1.0f - timeDead / timeToDie, 0.0f, 1.0f);

            if(alphaDead <= 0.0f) {
                isDead = true;
            }
        } else {
            alphaDead = 1.0f;
        }

        if(isReceived && !isDead) {
            timeReceived += TimeStep;
            alphaReceived = Helper::Clamp(1.0f - timeReceived / timeToDisappear, 0.0f, 1.0f);

            if(alphaReceived <= 0.0f) {
                isDead = true;
            }
        } else {
            alphaReceived = 1.0f;
        }

        alphaRender = alphaReceived * (0.1f + 0.9f * alphaDead);

        colorStart.a = colorEnd.a = (sf::Uint8)(alphaRender * 255);
        colorRender = Helper::Blend(colorStart, colorEnd, ratioFinger);
        colorRender = Helper::Blend(colorRender, colorDead, 1.0f - alphaDead);

        /* maintain stable velocity */ if(false) {
            float velocityMagnitude = Helper::Magnitude(velocity);
            sf::Vector2f velocityNormalized = velocity;
            Helper::Normalize(velocityNormalized);

            velocityMagnitude += (constantVelocity - velocityMagnitude) * 0.1f;
            SetVelocity(velocityNormalized * velocityMagnitude);
        }
    }
}