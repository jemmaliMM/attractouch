#ifndef _VORTEX_FIELD_H
#define _VORTEX_FIELD_H

#include "utils/helper.h"
#include "utils/vectorfield.h"

namespace AT {

    class VortexField : public VectorField
    {
    private:

    public:
        VortexField();
        virtual ~VortexField();

        void AddVortex(float X, float Y, float Radius, float Strength, float Swirl = 0.0f);
        void Update(float TimeStep, float Rate);
    };
}

#endif