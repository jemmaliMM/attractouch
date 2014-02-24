#include "particles/smokeparticle.h"

namespace AT {

    SmokeParticle::SmokeParticle()
        :fadeInDelay(1.0f), fadeOutDelay(1.0f)
    {

    }

    SmokeParticle::~SmokeParticle()
    {

    }
    
    void SmokeParticle::Init(int Width, int Height)
    {
        SetPosition(
            sf::Randomizer::Random(0.0f, (float)Width - 1.0f),
            sf::Randomizer::Random(0.0f, (float)Height - 1.0f)
        );

        wrappingBorder = 25.0f;

        /* Random color, grayscale */ {
            bool white = sf::Randomizer::Random(0.0f, 1.0f) > 0.4f;
            colorRender = white ? sf::Color::White : sf::Color::Black;
            if(white)
                scaleOriginal = sf::Randomizer::Random(3.0f, 8.0f);
            else
                scaleOriginal = sf::Randomizer::Random(6.0f, 10.0f);
            scaleOriginal *= 1.5f;
        }

        lifeExpectancy = sf::Randomizer::Random(2.0f, 5.0f);
        age = 0.0f;

        alphaOriginal = sf::Randomizer::Random(0.2f, 0.7f);
        alphaRender = 0.0f;

        angle = sf::Randomizer::Random(0.0f, TWO_PI);
    }

    void SmokeParticle::Update(float TimeStep, int Width, int Height)
    {
        Particle::Update(TimeStep);

        age += TimeStep;
        if(age >= lifeExpectancy)
            Init(Width, Height);

        float alphaFade = 1.0f;
        if(age <= fadeInDelay)
            alphaFade = age / fadeInDelay;
        if(age >= (lifeExpectancy - fadeOutDelay))
            alphaFade = (lifeExpectancy - age) / fadeOutDelay;

        float alphaWrap = 1.0f;
        if(position.x < wrappingBorder)
            alphaWrap *= position.x / wrappingBorder;
        if(position.y < wrappingBorder)
            alphaWrap *= position.y / wrappingBorder;
        if(position.x > (Width - wrappingBorder))
            alphaWrap *= abs(position.x - Width) / wrappingBorder;
        if(position.y > (Height - wrappingBorder))
            alphaWrap *= abs(position.y - Height) / wrappingBorder;

        alphaRender = alphaFade * alphaWrap * alphaOriginal;

        if(alphaRender < 0.0f)
            alphaRender = 0.0f;
        if(alphaRender > 1.0f)
            alphaRender = 1.0f;

        colorRender.a = sf::Uint8(alphaRender * 255);

        scaleRender = scaleOriginal;

        float newAngle = atan2(velocity.x, velocity.y);
        angle += (newAngle - angle) * 1.0f * TimeStep;
    }
}