#ifndef _TRAJECTORY_CONSTRAINT_H
#define _TRAJECTORY_CONSTRAINT_H

#include <SFML/Graphics.hpp>

#include "multitouch/oscmessenger.h"
#include "particles/constraint.h"
#include "gameplay/gameplayparticle.h"
#include "utils/helper.h"
#include "utils/constants.h"

namespace AT {

    class TrajectoryConstraint : public Constraint
    {
    private:
        // spring properties
        float stiffness;

        enum State {
            Approaching,
            Turning,
            Finished
        };
        State state;

        sf::Vector2f center;
        GameplayParticle& particle;
        float radius;

        // used in Turning state
        float distanceToMaintain;
        float angleAtStartOfTurn;
        sf::Vector2f normalAtStartOfTurn;
        float angleToTravel;
    public:
        TrajectoryConstraint(const sf::Vector2f& Center, GameplayParticle& Particle, float Radius, bool Active = true);
        virtual ~TrajectoryConstraint();

        bool IsFinished() const
        { return state == Finished; }
        GameplayParticle& GetParticle()
        { return particle; }
        const GameplayParticle& GetParticle() const
        { return particle; }
        const sf::Vector2f& GetCenter() const
        { return center; }
        float GetRadius() const
        { return radius; }

        virtual void Update(float TimeStep);
    };
}

#endif