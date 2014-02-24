#include "particles/particle.h"

namespace AT {

    Particle::Particle()
        :position(0.0f, 0.0f), previousPosition(0.0f, 0.0f), acceleration(0.0f, 0.0f), velocity(0.0f, 0.0f), damping(1.0f)
    {
        
    }

    Particle::Particle(const Particle& rhs)
        :position(rhs.position), previousPosition(rhs.previousPosition), acceleration(rhs.acceleration), velocity(rhs.velocity), damping(rhs.damping)
    {
        
    }

    Particle& Particle::operator =(const Particle& rhs)
    {
        position = rhs.position;
        previousPosition = rhs.previousPosition;
        acceleration = rhs.acceleration;
        velocity = rhs.velocity;

        damping = rhs.damping;

        return *this;
    }

    Particle::~Particle()
    {
        
    }

    void Particle::SetPosition(float x, float y)
    {
        position.x = x;
        position.y = y;

        previousPosition = position;

        acceleration.x = acceleration.y = velocity.x = velocity.y = 0.0f;
    }

    void Particle::Move(float x, float y)
    {
        position.x += x;
        position.y += y;

        previousPosition.x += x;
        previousPosition.y += y;
    }

    bool Particle::Wrap(int Width, int Height)
    {
        bool wrapped = false;
        if(position.x < 0.0f) {
            Move((float)Width, 0.0f);
            wrapped = true;
        }
        if(position.y < 0.0f) {
            Move(0.0f, (float)Height);
            wrapped = true;
        }
        if(position.x >= Width) {
            Move(-(float)Width, 0.0f);
            wrapped = true;
        }
        if(position.y >= Height) {
            Move(0.0f, -(float)Height);
            wrapped = true;
        }
        return wrapped;
    }

    void Particle::ApplyImpulse(sf::Vector2f Direction)
    {
        //previousPosition.x -= Direction.x;
        //previousPosition.y -= Direction.y;
        position.x += Direction.x;
        position.y += Direction.y;
    }

    void Particle::ApplyForce(sf::Vector2f Direction)
    {
        acceleration.x += Direction.x;
        acceleration.y += Direction.y;
    }

    void Particle::Update(float TimeStep)
    {
        velocity.x = (position.x - previousPosition.x) * damping + acceleration.x * TimeStep * TimeStep;
        velocity.y = (position.y - previousPosition.y) * damping + acceleration.y * TimeStep * TimeStep;

        previousPosition.x = position.x;
        previousPosition.y = position.y;

        position.x += velocity.x;
        position.y += velocity.y;

        acceleration.x = acceleration.y = 0.0f;
    }

}