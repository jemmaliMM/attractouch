#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <SFML/Graphics.hpp>

namespace AT {

    class Particle
    {
    protected:
        sf::Vector2f position;
        sf::Vector2f previousPosition;
        sf::Vector2f acceleration;
        sf::Vector2f velocity;

        float damping;
    public:
        Particle();
        Particle(const Particle& rhs);
        Particle& operator=(const Particle& rhs);
        virtual ~Particle();

        const sf::Vector2f& GetPosition() const
        { return position; }
        void SetPosition(float x, float y);
        void SetPosition(const sf::Vector2f& Position)
        { SetPosition(Position.x, Position.y); }

        void Move(float x, float y);
        virtual bool Wrap(int Width, int Height);

        const sf::Vector2f& GetVelocity() const
        { return velocity; }
        const void SetVelocity(float x, float y)
        {
            previousPosition.x = position.x - x;
            previousPosition.y = position.y - y;
            velocity.x = x;
            velocity.y = y;
        }
        const void SetVelocity(const sf::Vector2f& Velocity)
        { SetVelocity(Velocity.x, Velocity.y); }

        void ApplyImpulse(sf::Vector2f Direction);
        void ApplyForce(sf::Vector2f Direction);

        virtual void Update(float TimeStep);
    };

}

#endif
