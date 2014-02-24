#include "gameplay/launcher.h"

namespace AT {

    bool Launcher::loaded = false;
    sf::Image Launcher::image;
    sf::Sprite Launcher::sprite;

    Launcher::Launcher(const sf::Vector2f Position, float Rotation, int InitialParticles, float Speed, float Rate, float Radius)
        :sf::Drawable(Position, sf::Vector2f(1, 1), Rotation), initialParticles(InitialParticles), speed(Speed), rate(Rate), radius(Radius), state(LauncherState::Waiting), launchedParticles(0), timeStepAccumulator(1.0f / rate)
    {
        initialVelocity = sf::Vector2f(cos(GetRotation()), -sin(GetRotation())) * speed;
        colorStart = sf::Color(35, 104, 26);
        colorEnd = sf::Color(102, 102, 102);
        alpha = 1.0f;

        if(!loaded) {
            if(!image.LoadFromFile("content/sprites/launcher.png"))
                throw std::exception("Can't load launcher sprite");
            sprite.SetImage(image);
            sprite.SetBlendMode(sf::Blend::Add);
            sprite.SetCenter(image.GetWidth() / 2.0f, image.GetHeight() / 2.0f);

            loaded = true;
        }
    }

    Launcher::~Launcher()
    {

    }

    void Launcher::Launch(ParticleSystem& particleSystem)
    {
        GameplayParticle *particle = new GameplayParticle(speed);
        particle->SetPosition(GetPosition());
        particle->SetVelocity(initialVelocity);

        particleSystem.Add(particle);

        ++launchedParticles;
    }

    void Launcher::Update(float TimeStep, ParticleSystem& particleSystem)
    {
        if(initialParticles > 0 && launchedParticles >= initialParticles) {
            state = LauncherState::Empty;
        }
        if(state == LauncherState::Active) {
            timeStepAccumulator += TimeStep;
            if(timeStepAccumulator >= (1.0f / rate)) {
                Launch(particleSystem);
                timeStepAccumulator -= 1.0f / rate;
            }
        }
    }

    void Launcher::Render(sf::RenderTarget& Target) const
    {
        float particleRatio = Helper::Clamp((float)launchedParticles / initialParticles, 0.0f, 1.0f);

        if(initialParticles <= 0)
            particleRatio = 0.0f;

        sprite.SetColor(Helper::Blend(colorStart, colorEnd, particleRatio));
        Target.Draw(sprite);
    }
}