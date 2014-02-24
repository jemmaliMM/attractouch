#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include "particles/particle.h"

namespace AT {

    class Constraint
    {
    protected:
        bool active;

        Constraint(const Constraint& rhs) {}
        Constraint& operator=(const Constraint& rhs) { return *this; }
    public:
        Constraint(bool Active = true)
            :active(Active)
        {
            
        }
        virtual ~Constraint() {}
        
        virtual bool IsActive()
        { return active; }
        virtual void Activate()
        { active = true; }
        virtual void Deactivate()
        { active = false; }
        virtual void SetActive(bool Active)
        { active = Active; }

        virtual void Update(float TimeStep) = 0;
    };
}

#endif
