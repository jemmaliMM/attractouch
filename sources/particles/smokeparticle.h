#ifndef _SMOKE_PARTICLE_H
#define _SMOKE_PARTICLE_H

#include "particles/particle.h"
#include "utils/helper.h"
#include <cmath>

namespace AT {

    class SmokeParticle : public Particle
    {
    protected:
        float fadeInDelay;
        float fadeOutDelay;

        float lifeExpectancy;
        float age;

        float wrappingBorder;

        sf::Color colorRender;

        float alphaOriginal;
        float alphaRender;

        float scaleOriginal;
        float scaleRender;

        float angle;
    public:
        SmokeParticle();
        virtual ~SmokeParticle();

        void Init(int Width, int Height);

        const sf::Color& GetColor() const
        { return colorRender; }
        float GetAlpha() const
        { return alphaRender; }
        float GetScale() const
        { return scaleRender; }
        float GetAngle() const
        { return angle; }

        virtual void Update(float TimeStep, int Width, int Height);
    };
}

#endif
