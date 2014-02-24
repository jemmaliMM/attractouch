#include "utils/vortexfield.h"

namespace AT {

    VortexField::VortexField()
        :VectorField()
    {
        
    }

    VortexField::~VortexField()
    {

    }

    void VortexField::AddVortex(float X, float Y, float Radius, float Strength, float Swirl)
    {
        int cx1 = floor((X - Radius) / cellWidth);
        int cy1 = floor((Y - Radius) / cellHeight);
        int cx2 = ceil((X + Radius) / cellWidth);
        int cy2 = ceil((Y + Radius) / cellHeight);

        for(int y = cy1; y <= cy2; ++y) {
            for(int x = cx1; x <= cx2; ++x) {
                float dx = X - (x * cellWidth);
                float dy = Y - (y * cellHeight);
                float d = sqrt(dx * dx + dy * dy);

                if(d > Radius)
                    continue;

                float dS = Helper::Ease(1.0f - (d / Radius));

                dx /= d > 0.0f ? d : 0.00001f;
                dy /= d > 0.0f ? d : 0.00001f;

                float nx = -dy;
                float ny = dx;

                sf::Vector2f& v = GetVector(x, y);
                v.x += dx * dS * Strength + nx * dS * Swirl;
                v.y += dy * dS * Strength + ny * dS * Swirl;
            }
        }
    }

    void VortexField::Update(float TimeStep, float Rate)
    {
        for(int i = 0; i < gridWidth * gridHeight; ++i) {
            sf::Vector2f& v = vectors[i];
            v.x += -v.x * Rate * TimeStep;
            v.y += -v.y * Rate * TimeStep;
        }
    }

}