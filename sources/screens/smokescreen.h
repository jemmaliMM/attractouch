#ifndef _SMOKE_SCREEN_H
#define _SMOKE_SCREEN_H

#include "screens/screen.h"
#include "utils/vectorfield.h"
#include "utils/fluidfield.h"
#include "utils/vortexfield.h"
#include "utils/constants.h"
#include "particles/particlesystem.h"
#include "particles/smokeparticle.h"
#include "particles/vortexparticle.h"
#include "multitouch/fingermanager.h"
#include "external/simplex.h"

namespace AT {

    class SmokeScreen : public Screen
    {
    private:
        int width, height;

        bool visible;

        bool applyNoise;
        float noiseZ;
        float noiseTimeStep;

        FluidField fluidField;
        VortexField vortexField;

        ParticleSystem particleSystem;
        sf::Image particleImage;
        sf::Sprite particleSprite;

        ParticleSystem vortexSystem;
        sf::Image vortexBackgroundImage;
        sf::Sprite vortexBackgroundSprite;
        sf::Image vortexParticleImage;
        sf::Sprite vortexParticleSprite;

        bool debug;
        bool showGrid;
        bool showVortex;
    public:
        SmokeScreen(ScreenManager& ScreenManager);
        virtual ~SmokeScreen();

        void ApplyNoise(bool Enabled);
        bool IsNoiseApplied() const
        { return applyNoise; }

        FluidField& GetFluidField()
        { return fluidField; }
        VortexField& GetVortexField()
        { return vortexField; }
        
        virtual void Load(sf::RenderTarget& Target);
        
        virtual bool Process(sf::Event& Event);
        virtual bool Update(float TimeStep);
        virtual void Draw(sf::RenderTarget& Target);
    };

}

#endif
