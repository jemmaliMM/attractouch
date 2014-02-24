#ifndef _GLOBAL_FORCE_H
#define _GLOBAL_FORCE_H

#include "particles/force.h"

namespace AT {

    class GlobalForce : public Force
    {
    protected:
        sf::Vector2f direction;
    public:
        GlobalForce(bool Active = true);
        GlobalForce(float x, float y, bool Active = true);
        GlobalForce(const sf::Vector2f& Direction, bool Active = true);
        virtual ~GlobalForce() {}

        void SetDirection(float x, float y)
        { direction.x = x; direction.y = y; }
        void SetDirection(const sf::Vector2f& Direction)
        { direction = Direction; }
        virtual void Apply(Particle *particle);
    };
}

#endif
