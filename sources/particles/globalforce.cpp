#include "particles/globalforce.h"

namespace AT {

    GlobalForce::GlobalForce(bool Active)
        :Force(Active), direction(0.0f, 0.0f)
    {
        
    }

    GlobalForce::GlobalForce(float x, float y, bool Active)
        :Force(Active), direction(x, y)
    {

    }

    GlobalForce::GlobalForce(const sf::Vector2f& Direction, bool Active)
        :Force(Active), direction(Direction)
    {

    }

    void GlobalForce::Apply(Particle *particle)
    {
        particle->ApplyForce(direction);
    }
}