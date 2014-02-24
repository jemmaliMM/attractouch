#ifndef _VORTEX_PARTICLE_H
#define _VORTEX_PARTICLE_H

#include <deque>

#include "utils/helper.h"
#include "utils/constants.h"
#include "multitouch/fingermanager.h"
#include "particles/particle.h"

namespace AT {

    class VortexParticle : public Particle
    {
    public:
        struct TrailData
        {
            float time;
            sf::Vector2f position;
            float alpha;
            float scale;
        };

        typedef std::deque<TrailData> Trail;
    protected:
        static bool loaded;
        static sf::Image image;
        static sf::Sprite sprite;

        float fadeInDelay;
        float fadeOutDelay;
        float diffuseDelay;

        float lifeExpectancy;
        float age;

        bool diffuseStarted;
        float diffuseTimer;

        float scaleDiffuse;
        float scaleRender;

        float alphaRender;
        float alphaVortexTarget;
        float alphaVortex;
        float angle;

        bool vortexSet;
        sf::Vector2f vortex;
        float vortexDistance;

        int trailMaximumLength;
        Trail trail;
        float trailLength;

        float totalTime;
    public:
        VortexParticle();
        virtual ~VortexParticle();

        float GetScale() const
        { return scaleRender; }
        float GetAlpha() const
        { return alphaRender; }
        void SetAlphaVortex(float Alpha)
        { alphaVortexTarget = Helper::Clamp(Alpha, 0.0f, 1.0f); }
        float GetAngle() const
        { return angle; }

        bool HasVortex() const
        { return vortexSet; }
        sf::Vector2f GetVortex() const
        { return vortex; }
        float GetVortexDistance() const
        { return vortexDistance; }
        void SetVortex(const sf::Vector2f& Vortex)
        {
            vortexSet = true;
            vortex = Vortex;
            vortexDistance = Helper::Max(1.0f, Helper::Distance(Vortex, GetPosition()));
        }
        void UnsetVortex()
        {
            vortexSet = false;
            diffuseStarted = true;
        }

        void Init(int Width, int Height);
        void Update(float TimeStep, int Width, int Height);
        void Render(sf::RenderTarget& Target);
    };
}

#endif