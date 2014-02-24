#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include <deque>

#include "particles/particle.h"
#include "particles/constraint.h"

namespace AT {

    typedef std::deque<Particle*> Particles;
    typedef std::deque<Constraint*> Constraints;

    class ParticleSystem
    {
    protected:
        Particles particles;
        Constraints constraints;

        void CopyFrom(const ParticleSystem& rhs);
    public:
        ParticleSystem();
        ParticleSystem(const ParticleSystem& rhs);
        ParticleSystem& operator=(const ParticleSystem& rhs);
        ~ParticleSystem();

        void Add(Particle *particle);
        void Remove(Particle *particle);
        void Add(Constraint *constraint);
        void Remove(Constraint *constraint);
        void Clear();
        void Update(float TimeStep);

        Particles& GetParticles()
        { return particles; }
        const Particles& GetParticles() const
        { return particles; }

        Constraints& GetConstraints()
        { return constraints; }
        const Constraints& GetConstraints() const
        { return constraints; }
    };

}

#endif
