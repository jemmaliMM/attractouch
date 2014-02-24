#include "particles/particlesystem.h"

namespace AT {

    ParticleSystem::ParticleSystem()
    {

    }

    ParticleSystem::ParticleSystem(const ParticleSystem& rhs)
    {
        CopyFrom(rhs);
    }

    ParticleSystem& ParticleSystem::operator =(const ParticleSystem& rhs)
    {
        Clear();
        CopyFrom(rhs);

        return *this;
    }

    ParticleSystem::~ParticleSystem()
    {
        Clear();
    }

    void ParticleSystem::CopyFrom(const ParticleSystem& rhs)
    {
        for(Particles::const_iterator it = rhs.particles.begin(); it != rhs.particles.end(); ++it) {
            const Particle& particle = **it;
            particles.push_back(new Particle(particle));
        }
    }

    void ParticleSystem::Add(Particle *particle)
    {
        particles.push_back(particle);
    }

    void ParticleSystem::Remove(Particle *particle)
    {
        for(Particles::iterator it = particles.begin(); it != particles.end(); ++it) {
            if(particle == *it) {
                particles.erase(it);
                break;
            }
        }
        delete particle;
    }

    void ParticleSystem::Add(Constraint *constraint)
    {
        constraints.push_back(constraint);
    }

    void ParticleSystem::Remove(Constraint *constraint)
    {
        for(Constraints::iterator it = constraints.begin(); it != constraints.end(); ++it) {
            if(constraint == *it) {
                constraints.erase(it);
                break;
            }
        }
        delete constraint;
    }

    void ParticleSystem::Clear()
    {
        for(Particles::iterator it = particles.begin(); it != particles.end(); ++it)
            delete *it;
        particles.clear();

        for(Constraints::iterator it = constraints.begin(); it != constraints.end(); ++it)
            delete *it;
        constraints.clear();
    }

    void ParticleSystem::Update(float TimeStep)
    {
        for(Particles::iterator it = particles.begin(); it != particles.end(); ++it)
            (*it)->Update(TimeStep);

        for(Constraints::iterator it = constraints.begin(); it != constraints.end(); ++it) {
            if((*it)->IsActive())
                (*it)->Update(TimeStep);
        }
    }
}