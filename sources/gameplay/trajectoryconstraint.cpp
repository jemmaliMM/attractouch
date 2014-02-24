#include "gameplay/trajectoryconstraint.h"

namespace AT {

    TrajectoryConstraint::TrajectoryConstraint(const sf::Vector2f& Center, GameplayParticle& Particle, float Radius, bool Active)
        :Constraint(Active), stiffness(0.025f), state(Approaching), center(Center), radius(Radius), particle(Particle)
    {
        // the particle should not be attracted if it is going away from the center
        bool goingAway = Helper::Dot(Center - particle.GetPosition(), particle.GetVelocity()) < 0.0f;

        bool previousConstrained = particle.IsConstrained();
        particle.SetConstrained(!goingAway);
        if(goingAway) {
            state = Finished;
        } else {
            if(!previousConstrained)
                OSCMessenger::Instance().ParticleAttracted();
        }
    }

    TrajectoryConstraint::~TrajectoryConstraint()
    {
        
    }

    void TrajectoryConstraint::Update(float TimeStep)
    {
        sf::Vector2f toCenter = center - particle.GetPosition();
        float angleSide = Helper::Degrees(Helper::Angle(particle.GetVelocity(), toCenter));

        sf::Vector2f velocityNormal = Helper::Normal(particle.GetVelocity());
        Helper::Normalize(velocityNormal);

        if(angleSide < 0.0f) {
            velocityNormal *= -1.0f;
        }

        float angleNormal = Helper::Degrees(Helper::Angle(sf::Vector2f(1, 0), velocityNormal));

        //sf::Vector2f projected = Helper::Project(center, velocityNormal, particle.GetPosition());

        if(state == Approaching) {
            if(abs(angleSide) >= 90.0f) { // just passed the center, or already on the other side

                //distanceToMaintain = Helper::Distance(center, projected);
                distanceToMaintain = Helper::Distance(center, particle.GetPosition());
                angleAtStartOfTurn = angleNormal;
                normalAtStartOfTurn = velocityNormal;

                float distanceRatio = distanceToMaintain / radius;

                angleToTravel = 0.0f;
                if(distanceRatio < 0.3) {
                    angleToTravel = 135.0f;
                    distanceToMaintain = Constants::Instance().FingerRadius() * 0.15f;
                } else if(distanceRatio < 0.6) {
                    angleToTravel = 90.0f;
                    distanceToMaintain = Constants::Instance().FingerRadius() * 0.45f;
                } else {
                    angleToTravel = 45.0f;
                    distanceToMaintain = Constants::Instance().FingerRadius() * 0.75f;
                }

                state = Turning;
            }
        }
        else if(state == Turning) {

            /* apply spring to maintain particle within distance */ {
                sf::Vector2f delta = center - particle.GetPosition();
                float distance = Helper::Distance(center, particle.GetPosition());

                float coeff = stiffness * (distance - distanceToMaintain) / distance;
                particle.ApplyImpulse(delta * coeff);
            }

            /* check if the particle did the whole turn */ if(true) {
                float angleTravelled = abs(Helper::Degrees(Helper::Angle(normalAtStartOfTurn, toCenter)));

                if(angleTravelled >= angleToTravel) {
                    sf::Vector2f normalExit = Helper::RotateCW(normalAtStartOfTurn, (angleSide < 0.0f ? -1.0f : +1.0f) * Helper::Radians(angleToTravel));
                    Helper::Normalize(normalExit);

                    sf::Vector2f directionExit = Helper::Normal(normalExit) * (angleSide < 0.0f ? +1.0f : -1.0f);

                    particle.SetPosition(center + normalExit * -distanceToMaintain);
                    particle.SetVelocity(directionExit * particle.GetConstantVelocity());
                    state = Finished;
                }
            }
        }
        else if(state == Finished) {
            float distance = Helper::Distance(center, particle.GetPosition());
            if(distance > radius)
                particle.SetConstrained(false);
        }
    }
}