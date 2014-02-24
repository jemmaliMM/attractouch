#include "screens/smokescreen.h"

namespace AT {

    SmokeScreen::SmokeScreen(ScreenManager& ScreenManager)
        :Screen(ScreenManager)
    {
        transitionOnTime = 0.0f;
        transitionOffTime = 0.0f;

        SetPosition(25.0f, 25.0f);

        visible = true;

        showGrid = false;
        showVortex = true;
        debug = DEBUG_INITIAL;

        width = 1;
        height = 1;

        applyNoise = false;
        noiseZ = 0.0f;
        noiseTimeStep = 0.25f;
    }

    SmokeScreen::~SmokeScreen()
    {

    }

    void SmokeScreen::ApplyNoise(bool Enabled)
    {
        applyNoise = Enabled;
        visible = Enabled;
    }

    void SmokeScreen::Load(sf::RenderTarget& Target)
    {
        glAccum(GL_LOAD, 0.0f);

        width = Helper::BaseWidth;
        height = Helper::BaseHeight;

        float aspectRatio = float(width) / height;
        int gridWidth = 40;
        int gridHeight = int(float(gridWidth) / aspectRatio);

        fluidField.SetSize(width - 50, height - 50);
        fluidField.SetGridSize(gridWidth, gridHeight);
        fluidField.InitRandom();

        vortexField.SetSize(fluidField.GetWidth(), fluidField.GetHeight());
        vortexField.SetGridSize(gridWidth, gridHeight);

        // smoke particles
#ifdef DEBUG
        for(int i = 0; i < 10; ++i) {
#else
        for(int i = 0; i < 1000; ++i) {
#endif
            SmokeParticle *particle = new SmokeParticle();
            particle->Init(fluidField.GetWidth(), fluidField.GetHeight());
            particleSystem.Add(particle);
        }

        // vortex particles
#ifdef DEBUG
        for(int i = 0; i < 10; ++i) {
#else
        for(int i = 0; i < 1000; ++i) {
#endif
            VortexParticle *particle = new VortexParticle();
            particle->Init(vortexField.GetWidth(), vortexField.GetHeight());
            vortexSystem.Add(particle);
        }

        if(!particleImage.LoadFromFile("content/sprites/smoke.png"))
            throw std::exception("Can't load smoke sprite");

        particleSprite.SetImage(particleImage);
        particleSprite.SetCenter(particleImage.GetWidth() / 2.0f, particleImage.GetHeight() / 2.0f);

        if(!vortexBackgroundImage.LoadFromFile("content/sprites/vortex-background.png"))
            throw std::exception("Can't load vortex background sprite");

        vortexBackgroundSprite.SetImage(vortexBackgroundImage);
        vortexBackgroundSprite.SetCenter(vortexBackgroundImage.GetWidth() / 2, vortexBackgroundImage.GetHeight() / 2);
    }

    bool SmokeScreen::Process(sf::Event& Event)
    {
        if(debug && (Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::G)) {
            showGrid = !showGrid;
        }
        if(debug && (Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::V)) {
            showVortex = !showVortex;
        }
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D)) {
            debug = !debug;
        }
        return false;
    }

    bool SmokeScreen::Update(float TimeStep)
    {
        static float noiseAccum = noiseTimeStep;

        Screen::Update(TimeStep);

        const Fingers& fingers = FingerManager::Instance().GetFingers();
        for(Fingers::const_iterator it = fingers.begin(); it != fingers.end(); ++it) {
            const FingerData& data = *it;
            if(data.finger == 0)
                continue;

            float screenX = (float)data.ScreenX(width) - GetPosition().x;
            float screenY = (float)data.ScreenY(height) - GetPosition().y;
            fluidField.AddVelocity(screenX, screenY, data.finger->getXSpeed() * 10.0f, data.finger->getYSpeed() * 10.0f);
            vortexField.AddVortex(screenX, screenY, Constants::Instance().FingerRadius(), 0.2f, 0.1f);
        }

        if (applyNoise) {
            noiseAccum += TimeStep;
            if(noiseAccum >= noiseTimeStep) {
                for(int y = 0; y < fluidField.GetGridHeight(); ++y) {
                    for(int x = 0; x < fluidField.GetGridWidth(); ++x) {
                        fluidField.StoreDensity(x, y, simplexScaledNoise(3.0f, 1.0f, 1.0f, -0.5f, 1.0f, (float)x / fluidField.GetGridWidth(), (float)y / fluidField.GetGridHeight(), noiseZ));
                    }
                }
                noiseAccum -= noiseTimeStep;
            }

            noiseZ += 0.05f * TimeStep;

            for(int y = 0; y < fluidField.GetGridHeight(); ++y) {
                for(int x = 0; x < fluidField.GetGridWidth(); ++x) {
                    fluidField.RestoreDensity(x, y);
                }
            }
        }

        fluidField.Update(0.05f);
        vortexField.Update(TimeStep, 1.0f);

        for(Particles::iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end(); ++it) {
            SmokeParticle& particle = *static_cast<SmokeParticle*>(*it);

            sf::Vector2f fFluid = fluidField.Interpolate(particle.GetPosition().x, particle.GetPosition().y);
            fFluid *= 2000.0f;
            particle.ApplyForce(fFluid);

            particle.Update(TimeStep, fluidField.GetWidth(), fluidField.GetHeight());
            particle.Wrap(fluidField.GetWidth(), fluidField.GetHeight());
        }
        /*for(Particles::iterator it = vortexSystem.GetParticles().begin(); it != vortexSystem.GetParticles().end(); ++it) {
            VortexParticle& particle = *static_cast<VortexParticle*>(*it);

            sf::Vector2f fVortex = vortexField.Interpolate(particle.GetPosition().x, particle.GetPosition().y);

            float vortexForce = sqrt(fVortex.x * fVortex.x + fVortex.y * fVortex.y) * 0.1f;
            particle.SetAlphaVortex(vortexForce);

            fVortex *= 10.0f;
            fVortex.x += sf::Randomizer::Random(-0.1f, +0.1f);
            fVortex.y += sf::Randomizer::Random(-0.1f, +0.1f);
            particle.ApplyForce(fVortex);

            particle.Update(TimeStep, vortexField.GetWidth(), vortexField.GetHeight());
        }*/
        for(Particles::iterator it = vortexSystem.GetParticles().begin(); it != vortexSystem.GetParticles().end(); ++it) {
            VortexParticle& particle = *static_cast<VortexParticle*>(*it);

            particle.SetAlphaVortex(0.0f);

            sf::Vector2f nearestVortex;
            float minimumDistance = -1.0f;
            if(FingerManager::Instance().NFingers() > 0) {
                for(Fingers::const_iterator it = fingers.begin(); it != fingers.end(); ++it) {
                    const FingerData& data = *it;
                    if(data.finger == 0)
                        continue;

                    sf::Vector2f fingerPosition(
                        (float)data.ScreenSmoothX(width) - GetPosition().x,
                        (float)data.ScreenSmoothY(height) - GetPosition().y
                    );

                    float distance = Helper::Distance(fingerPosition, particle.GetPosition());

                    if(minimumDistance < 0.0f || distance < minimumDistance) {
                        minimumDistance = distance;
                        nearestVortex = fingerPosition;
                    }
                }
                if(!particle.HasVortex() && minimumDistance <= Constants::Instance().FingerRadius()) {
                    particle.SetVortex(nearestVortex);

                    sf::Vector2f initialVortexVelocity = Helper::Normal(particle.GetVortex() - particle.GetPosition());
                    Helper::Normalize(initialVortexVelocity);
                    initialVortexVelocity *= 1.0f;
                    particle.SetVelocity(initialVortexVelocity);
                }
            }
            if(particle.HasVortex() && (minimumDistance < 0.0f || minimumDistance > Constants::Instance().FingerRadius())) {
                particle.UnsetVortex();
                particle.SetVelocity(particle.GetVelocity().x * sf::Randomizer::Random(-1.0f, 1.0f), particle.GetVelocity().y * sf::Randomizer::Random(-1.0f, 1.0f));
            }
            
            /* apply vortex force */
            if(particle.HasVortex()) {
                sf::Vector2f delta = particle.GetVortex() - particle.GetPosition();
                float distance = Helper::Magnitude(delta);
                float distanceRatio = Helper::Clamp(distance / Constants::Instance().FingerRadius(), 0.0f, 1.0f);

                particle.SetAlphaVortex(1.0f - distanceRatio);

                float stiffness = 0.25f;
                float coeff = stiffness * (distance - particle.GetVortexDistance()) / distance;
                particle.ApplyImpulse(delta * coeff);

                sf::Vector2f vortexForce = Helper::Normal(delta);
                Helper::Normalize(vortexForce);
                vortexForce *= 25.0f;
                particle.ApplyForce(vortexForce);
            }

            particle.Update(TimeStep, vortexField.GetWidth(), vortexField.GetHeight());
        }

        return false;
    }

    void SmokeScreen::Draw(sf::RenderTarget& Target)
    {
        if(debug) {
            float d;
            float cx = fluidField.GetCellWidth();
            float cy = fluidField.GetCellHeight();

            glBegin(GL_QUADS);
                for(int y = 1; y <= fluidField.GetGridHeight(); ++y) {
                    for(int x = 1; x <= fluidField.GetGridWidth(); ++x) {
                        float ox = (x - 1) * fluidField.GetCellWidth();
                        float oy = (y - 1) * fluidField.GetCellHeight();

                        d = fluidField.GetDensity(x, y);

                        if(!fluidField.GetMap(x, y))
                            glColor3f(d, d, d);
                        else
                            glColor3f(d * 0.5f + 0.5f, 0.0f, 0.0f);
                        glVertex2f(ox, oy);
                        glVertex2f(ox + cx, oy);
                        glVertex2f(ox + cx, oy + cy);
                        glVertex2f(ox, oy + cy);
                    }
                }
            glEnd();
        }

        if(debug) {
            glBegin(GL_POINTS);
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        // draw smoke particles
        for(Particles::const_iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end(); ++it) {
            const SmokeParticle& particle = *static_cast<SmokeParticle*>(*it);
            
            if(!debug) {
                particleSprite.SetPosition(particle.GetPosition());

                float d = fluidField.GetDensity(particle.GetPosition().x, particle.GetPosition().y);
                if(d < 0.0f)
                    d = 0.0f;
                if(d > 1.0f)
                    d = 1.0f;
                int c = int(d * 255);
                particleSprite.SetColor(sf::Color(c, c, c, particle.GetColor().a));

                particleSprite.SetRotation(Helper::ToDegrees(particle.GetAngle()));
                particleSprite.SetScale(particle.GetScale(), particle.GetScale());
                if(c >= 5 && particle.GetColor().a >= 5)
                    Target.Draw(particleSprite);
            } else {
                glVertex2f(particle.GetPosition().x, particle.GetPosition().y);
            }
        }
        if(debug) {
            glEnd();
        }
        // draw vortices background
        if(!debug) {
            const Fingers& fingers = FingerManager::Instance().GetFingers();
            for(Fingers::const_iterator it = fingers.begin(); it != fingers.end(); ++it) {
                const FingerData& data = *it;

                float alpha = 0.0f;
                if(data.finger == 0) {
                    float fadeOutDelay = 1.0f;
                    float removeDelay = (TUIO::TuioTime::getSessionTime().getTotalMilliseconds() - data.removeTime.getTotalMilliseconds()) / 1000.0f;
                    alpha = 1.0f - Helper::Clamp(removeDelay / fadeOutDelay, 0.0f, 1.0f);
                } else {
                    float fadeInDelay = 1.0f;
                    float addDelay = (TUIO::TuioTime::getSessionTime().getTotalMilliseconds() - data.addTime.getTotalMilliseconds()) / 1000.0f;
                    alpha = Helper::Clamp(addDelay / fadeInDelay, 0.0f, 1.0f);
                }

                float screenX = (float)(data.x * Helper::BaseWidth) - GetPosition().x;
                float screenY = (float)(data.y * Helper::BaseHeight) - GetPosition().y;

                vortexBackgroundSprite.SetPosition(sf::Vector2f(screenX, screenY));
                vortexBackgroundSprite.SetColor(sf::Color(255, 255, 255, int(alpha * 255)));
                Target.Draw(vortexBackgroundSprite);
            }
        }
        if(debug) {
            glBegin(GL_POINTS);
            glColor3f(0.0f, 0.0f, 1.0f);
        }
        // draw vortices particles
        for(Particles::iterator it = vortexSystem.GetParticles().begin(); it != vortexSystem.GetParticles().end(); ++it) {
            VortexParticle& particle = *static_cast<VortexParticle*>(*it);

            if(!debug) {
                /*vortexParticleSprite.SetPosition(particle.GetPosition());
                vortexParticleSprite.SetRotation(ToDegrees(particle.GetAngle()));
                vortexParticleSprite.SetScale(particle.GetScale(), particle.GetScale());
                vortexParticleSprite.SetColor(sf::Color(255, 255, 255, int(particle.GetAlpha() * 255)));

                Target.Draw(vortexParticleSprite);*/
                particle.Render(Target);
            } else {
                glVertex2f(particle.GetPosition().x, particle.GetPosition().y);
            }
        }
        if(debug) {
            glEnd();
        }

        if(debug && showGrid) {
            glBegin(GL_LINES);

            glColor3f(0.0f, 0.0f, 1.0f);
            for(int y = 0; y < fluidField.GetGridHeight(); ++y) {
                for(int x = 0; x < fluidField.GetGridWidth(); ++x) {
                    float ox = (x + 0.5f) * fluidField.GetCellWidth();
                    float oy = (y + 0.5f) * fluidField.GetCellHeight();
                    glVertex2f(ox, oy);

                    sf::Vector2f v = fluidField.GetVector(x, y);
                    v *= 100.0f;
                    ox += v.x;
                    oy += v.y;
                    glVertex2f(ox, oy);
                }
            }

            glEnd();
        }

        if(debug && showVortex) {
            glBegin(GL_LINES);

            glColor3f(0.0f, 1.0f, 0.0f);
            for(int y = 0; y <= vortexField.GetGridHeight(); ++y) {
                for(int x = 0; x <= vortexField.GetGridWidth(); ++x) {
                    float ox = x * vortexField.GetCellWidth();
                    float oy = y * vortexField.GetCellHeight();

                    glVertex2f(ox, oy);

                    sf::Vector2f v = vortexField.GetVector(x, y);
                    v *= 1.0f;
                    ox += v.x;
                    oy += v.y;
                    glVertex2f(ox, oy);
                }
            }

            glEnd();
        }
    }

}