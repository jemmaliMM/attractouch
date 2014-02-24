#include "particles/vortexparticle.h"

namespace AT {

    bool VortexParticle::loaded = false;
    sf::Image VortexParticle::image;
    sf::Sprite VortexParticle::sprite;

    VortexParticle::VortexParticle()
        :fadeInDelay(1.0f), fadeOutDelay(1.0f), diffuseDelay(0.5f), vortexSet(false), trailMaximumLength(10), totalTime(0.0f)
    {
        if(!loaded) {
            if(!image.LoadFromFile("content/sprites/vortex-particle.png"))
                throw std::exception("Can't load vortex background sprite");

            sprite.SetImage(image);
            sprite.SetBlendMode(sf::Blend::Add);
            sprite.SetCenter(image.GetWidth() / 2.0f, image.GetHeight() / 2.0f);

            loaded = true;
        }
    }

    VortexParticle::~VortexParticle()
    {

    }

    void VortexParticle::Init(int Width, int Height)
    {
        sf::Vector2f randomPosition(
            sf::Randomizer::Random(0.0f, (float)Width - 1.0f),
            sf::Randomizer::Random(0.0f, (float)Height - 1.0f)
        );

        SetPosition(randomPosition);

        lifeExpectancy = sf::Randomizer::Random(1.0f, 3.0f);
        age = 0.0f;

        diffuseStarted = false;
        diffuseTimer = diffuseDelay;

        scaleDiffuse = 1.0f;
        scaleRender = sf::Randomizer::Random(1.0f, 1.0f);

        alphaRender = 0.0f;
        alphaVortexTarget = 0.0f;
        alphaVortex = 0.0f;

        angle = sf::Randomizer::Random(0.0f, TWO_PI);

        vortexSet = false;

        //trail.clear();
        //trailLength = 0.0f;
    }

    void VortexParticle::Update(float TimeStep, int Width, int Height)
    {
        Particle::Update(TimeStep);

        age += TimeStep;
        if(age >= lifeExpectancy)
            Init(Width, Height);

        if(diffuseStarted) {
            diffuseTimer -= TimeStep;
            diffuseTimer = Helper::Clamp(diffuseTimer, 0.0f, diffuseDelay);
        }
        scaleDiffuse = 1.0f - diffuseTimer / diffuseDelay;
        scaleRender = 3.0f + scaleDiffuse * 3.0f;

        float alphaFade = 1.0f;
        if(age <= fadeInDelay)
            alphaFade = age / fadeInDelay;
        if(age >= (lifeExpectancy - fadeOutDelay))
            alphaFade = (lifeExpectancy - age) / fadeOutDelay;

        alphaVortex += (alphaVortexTarget - alphaVortex) * 1.0f * TimeStep;
        alphaRender = (0.1f + 0.9f * (vortexDistance / Constants::Instance().FingerRadius())) * alphaFade * alphaVortex * (1.0f - scaleDiffuse);

        angle = atan2(velocity.x, velocity.y);

        totalTime += TimeStep;
        if(trail.size() == 0 || (totalTime - trail.front().time) >= 0.07f) {
            TrailData data = { totalTime, GetPosition(), alphaRender, scaleRender };
            trail.push_front(data);
        }
        while(trail.size() > trailMaximumLength) {
            trail.pop_back();
        }
    }

    void VortexParticle::Render(sf::RenderTarget& Target)
    {
        sprite.SetScale(GetScale(), GetScale());

        int n = trail.size();
        int nMax = trail.size();
        float trailRatio = 1.0f;
        for(Trail::iterator it = trail.begin(); it != trail.end(); ++it) {
            TrailData data = *it;

            trailRatio = (float)n / nMax;

            float trailScale = (0.5f + 0.5f * trailRatio) * data.scale;

            sprite.SetPosition(data.position);
            sprite.SetColor(sf::Color(255, 255, 255, int(data.alpha * trailRatio * 255)));
            if(sprite.GetColor().a > 0.01f)
                Target.Draw(sprite);

            --n;
        }

        sprite.SetPosition(GetPosition());
        sprite.SetColor(sf::Color(255, 255, 255, int(GetAlpha() * 255)));
        Target.Draw(sprite);
    }
}