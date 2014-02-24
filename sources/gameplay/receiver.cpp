#include "gameplay/receiver.h"

namespace AT {

    bool Receiver::loaded = false;
    sf::Image Receiver::image;
    sf::Sprite Receiver::sprite;

    Receiver::Receiver(const sf::Vector2f Position, int MaximumParticles, float Radius)
        :sf::Drawable(Position, sf::Vector2f(1, 1), 0.0f), maximumParticles(Helper::Max(1, MaximumParticles)), receivedParticles(0), radius(Radius)
    {
        colorStart = sf::Color(151, 151, 151);
        colorEnd = sf::Color(255, 255, 0);
        alpha = 0.0f;

        if(!loaded) {
            if(!image.LoadFromFile("content/sprites/receiver.png"))
                throw std::exception("Can't load receiver sprite");
            sprite.SetImage(image);
            sprite.SetBlendMode(sf::Blend::Add);
            sprite.SetCenter(image.GetWidth() / 2.0f, image.GetHeight() / 2.0f);
            sprite.SetColor(sf::Color(255, 255, 0));

            loaded = true;
        }
    }

    Receiver::~Receiver()
    {

    }

    void Receiver::Update(float TimeStep, ParticleSystem& particleSystem)
    {
        for(Particles::iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end();) {
            GameplayParticle& particle = *static_cast<GameplayParticle*>(*it);

            bool removed = false;
            if(particle.IsReceived()) {
                sf::Vector2f delta = GetPosition() - particle.GetPosition();
                float distance = Helper::Distance(GetPosition(), particle.GetPosition());

                /*if(particle.IsDead()) {
                    removed = true;
                    it = particleSystem.GetParticles().erase(it);
                }*/

                float stiffness = 0.01f;
                particle.ApplyImpulse(delta * stiffness);
                particle.ApplyImpulse(sf::Vector2f(sf::Randomizer::Random(-1.0f, +1.0f), sf::Randomizer::Random(-1.0f, +1.0f)) * distance * 0.01f);
            } else {
                float distance = Helper::Distance(GetPosition(), particle.GetPosition());
                if(distance < radius) {
                    particle.SetReceived(true);
                    ++receivedParticles;
                    OSCMessenger::Instance().ParticleReceived();

                    float particleRatio = Helper::Clamp(receivedParticles / (float)maximumParticles, 0.0f, 1.0f);
                    std::cout << "received:" << receivedParticles << " max:" << maximumParticles << " ratio:" << particleRatio << std::endl;
                }
            }
            if(!removed)
                ++it;
        }
    }

    void Receiver::Render(sf::RenderTarget& Target) const
    {
        float particleRatio = Helper::Clamp((float)receivedParticles / maximumParticles, 0.0f, 1.0f);

        sprite.SetColor(Helper::Blend(colorStart, colorEnd, particleRatio));
        Target.Draw(sprite);
    }
}