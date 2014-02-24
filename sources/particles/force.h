#ifndef _FORCE_H
#define _FORCE_H

#include "particles/particle.h"

namespace AT {

    class Force
    {
    protected:
        bool active;

        Force(const Force& rhs) {}
        Force& operator=(const Force& rhs) { return *this; }
    public:
        Force(bool Active = true)
            :active(Active)
        {
            
        }
        virtual ~Force() {}
        
        virtual void Activate()
        { active = true; }
        virtual void Deactivate()
        { active = false; }
        virtual void SetActive(bool Active)
        { active = Active; }

        virtual void Apply(Particle *particle) = 0;
    };
}

#endif
