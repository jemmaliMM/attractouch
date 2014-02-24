#include "screens/gamescreen.h"

namespace AT {

    GameScreen::GameScreen(ScreenManager& ScreenManager)
        :Screen(ScreenManager), levelName(""), levelPreviousParticles(0)/*, xmlLevel(NULL)*/, mainLauncher(NULL)//, receiver(NULL)
    {
        transitionOnTime = 3.0f;
        transitionOffTime = 3.0f;

        isUpdating = false;
        isStepping = false;
        debug = DEBUG_INITIAL;

        FingerManager::Instance().SetIsFingerOK(IsFingerOK, this);
    }

    GameScreen::~GameScreen()
    {
        Clear();
    }

    bool GameScreen::IsFingerOK(const FingerData& FingerData, void *Data)
    {
        GameScreen& gameScreen = *static_cast<GameScreen*>(Data);

        if(gameScreen.state != ScreenState::Active)
            return false;

        if(FingerManager::Instance().NFingers() >= 10)
            return false;

        sf::Vector2f fingerPosition(FingerData.ScreenX(Helper::BaseWidth), FingerData.ScreenY(Helper::BaseHeight));

        for(Walls::iterator it = gameScreen.walls.begin(); it != gameScreen.walls.end(); ++it) {
            Wall& wall = *static_cast<Wall*>(*it);

            if(wall.IsInside(fingerPosition)) {
                OSCMessenger::Instance().NotTonight(); // finger refused
                return false;
            }
        }

        /* activate main launcher */
        if(gameScreen.mainLauncher != NULL) {
            Launcher& mainLauncher = *static_cast<Launcher*>(gameScreen.mainLauncher);

            float distance = Helper::Distance(mainLauncher.GetPosition(), fingerPosition);
            if(distance < 40.0f) {
                if(mainLauncher.GetState() == LauncherState::Waiting) {
                    OSCMessenger::Instance().LauncherActivated(mainLauncher.GetInitialParticles());
                    mainLauncher.Activate();
                    return false;
                } else {
                    OSCMessenger::Instance().NotTonight(); // finger refused
                    return false;
                }
            }
        }

        return true;
    }

    void GameScreen::Load(sf::RenderTarget& Target)
    {
        if(!fingerImage.LoadFromFile("content/sprites/finger.png"))
            throw std::exception("Can't load finger sprite");
        fingerSprite.SetImage(fingerImage);
        fingerSprite.SetCenter(fingerImage.GetWidth() / 2, fingerImage.GetHeight() / 2);

        if(!particleImage.LoadFromFile("content/sprites/particle.png"))
            throw std::exception("Can't load particle sprite");
        particleSprite.SetImage(particleImage);
        particleSprite.SetBlendMode(sf::Blend::Add);
        particleSprite.SetColor(sf::Color(255, 255, 0));
        particleSprite.SetCenter(particleImage.GetWidth() / 2.0f, particleImage.GetHeight() / 2.0f);

        LoadLevel();
    }

    void GameScreen::OnStateChange(ScreenState::Value OldState)
    {
        if(state == ScreenState::Active) {
            isUpdating = true;
        }
        if(state == ScreenState::TransitionOn) {
            if(manager.GetGame().HasSmokeScreen()) {
                manager.GetGame().GetSmokeScreen().ApplyNoise(true);
            }
        }
        if(state == ScreenState::TransitionOff) {
            isUpdating = false;
            if(!nextLevel.empty()) {
                OSCMessenger::Instance().ChangeLevel();
                //GameScreen *gameScreen = (new GameScreen(manager))->SetLevel(xmlLevel->nextLevel().get(), receiver->GetReceivedParticles());
                GameScreen *gameScreen = (new GameScreen(manager))->SetLevel(nextLevel, receiver.GetReceivedParticles());
                //gameScreen->levelPreviousStart = receiver->GetPosition();
                gameScreen->levelPreviousStart = receiver.GetPosition();
                gameScreen->Show();
            }
        }
        if(state == ScreenState::ToRemove) {
            if(nextLevel.empty())
                //(new LoadingScreen(manager))->Add(new MenuScreen(manager))->Show();
                (new LoadingScreen(manager))->Add(new CreditsScreen(manager))->Show();
        }
    }

    bool GameScreen::Process(sf::Event& Event)
    {
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space)) {
            isUpdating = !isUpdating;
        }
        if(!isStepping && (Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S)) {
            isStepping = true;
            isUpdating = true;
        }
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D)) {
            debug = !debug;
        }
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::R)) {
            LoadLevel();
        }
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::N)) {
            NextLevel();
        }
        if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::C)) {
            
        }

        return false;
    }

    bool GameScreen::Update(float TimeStep)
    {
        Screen::Update(TimeStep);

        if(!isUpdating)
            return false;

        if(mainLauncher != NULL)
            mainLauncher->Update(TimeStep, particleSystem);

        for(Launchers::iterator it = optionalLaunchers.begin(); it != optionalLaunchers.end(); ++it) {
            (*it)->Update(TimeStep, particleSystem);
        }

        // apply forces for flow
        if(manager.GetGame().HasSmokeScreen()) {
            SmokeScreen& smokeScreen = manager.GetGame().GetSmokeScreen();

            for(Flow::Velocities::const_iterator it = flow.GetVelocities().begin(); it != flow.GetVelocities().end(); ++it) {
                const Flow::Velocity& v = *it;
                smokeScreen.GetFluidField().AddVelocity(v.x, v.y, v.u * 0.005f, v.y * 0.005f);
            }
        }

        /* attract particles in range */ {
            const Fingers& fingers = FingerManager::Instance().GetFingers();
            for(Fingers::const_iterator it = fingers.begin(); it != fingers.end(); ++it) {
                const FingerData& data = *it;
                if(data.finger == 0)
                    continue;

                sf::Vector2f fingerPosition(
                    data.ScreenSmoothX(Helper::BaseWidth),
                    data.ScreenSmoothY(Helper::BaseHeight)
                );

                // find particles inside the influence of the finger
                for(Particles::iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end(); ++it) {
                    GameplayParticle& particle = *static_cast<GameplayParticle*>(*it);

                    float distance = Helper::Distance(fingerPosition, particle.GetPosition());
                    if(distance < Constants::Instance().FingerRadius()) {
                        if(!particle.IsConstrained() && !particle.IsReceived()) {
                            particleSystem.Add(new TrajectoryConstraint(fingerPosition, particle, Constants::Instance().FingerRadius()));
                        }
                    }
                }
            }
        }

        // collisions with walls
        for(Particles::iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end(); ++it) {
            GameplayParticle& particle = *static_cast<GameplayParticle*>(*it);

            for(Walls::iterator it = walls.begin(); it != walls.end(); ++it) {
                Wall& wall = *static_cast<Wall*>(*it);

                Wall::Intersection result;
                if(wall.Intersect(particle.GetPosition(), result)) {
                    OSCMessenger::Instance().ParticleCollided();

                    sf::Vector2f velocity = particle.GetVelocity();
                    if(particle.IsConstrained())
                        particle.SetConstrained(false);
                    particle.SetVelocity(sf::Vector2f(velocity.x * result.ReverseX, velocity.y * result.ReverseY));
                }
            }
        }

        receiver.Update(TimeStep, particleSystem);

        particleSystem.Update(TimeStep);

        if(isStepping) {
            isUpdating = false;
            isStepping = false;
        }

        // find finished constraints
        for(Constraints::iterator it = particleSystem.GetConstraints().begin(); it != particleSystem.GetConstraints().end();) {
            TrajectoryConstraint& constraint = *static_cast<TrajectoryConstraint*>(*it);

            float ratio = Helper::Clamp(Helper::Distance(constraint.GetCenter(), constraint.GetParticle().GetPosition()) / constraint.GetRadius(), 0.0f, 1.0f);
            constraint.GetParticle().SetFingerRatio(1.0f - ratio);

            if(!constraint.GetParticle().IsConstrained() || constraint.GetParticle().IsDead() || constraint.GetParticle().IsReceived()) {
                it = particleSystem.GetConstraints().erase(it);
            } else {
                ++it;
            }
        }

        // find lost or dead particles and remove them
        for(Particles::iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end();) {
            GameplayParticle& particle = *static_cast<GameplayParticle*>(*it);

            sf::Vector2f position = particle.GetPosition();
            if(((position.x < 0.0f || position.y < 0.0f || position.x > Helper::BaseWidth || position.y > Helper::BaseHeight) && !particle.IsReceived()) || particle.IsDead()) {
                it = particleSystem.GetParticles().erase(it);
                OSCMessenger::Instance().ParticleLost();
            } else {
                ++it;
            }
        }

        // check for end of game
        if(mainLauncher->IsEmpty() && particleSystem.GetParticles().size() == 0) {
            NextLevel();
        }

        return false;
    }

    void GameScreen::Draw(sf::RenderTarget& Target)
    {
        float alphaFirstPart = 0.0f;
        if(transitionAlpha < 0.5f)
            alphaFirstPart = transitionAlpha / 0.5f;
        else
            alphaFirstPart = 1.0f;

        float alphaSecondPart = 0.0f;
        if(transitionAlpha >= 0.5f)
            alphaSecondPart = (transitionAlpha - 0.5f) / 0.5f;
        else
            alphaSecondPart = 0.0f;

        sf::Vector2f delta(0.0f, 0.0f);
        if(state == ScreenState::TransitionOn) {
            delta = levelPreviousStart - mainLauncher->GetPosition();
            if(manager.GetGame().HasSmokeScreen()) {
                SmokeScreen& smokeScreen = manager.GetGame().GetSmokeScreen();

                sf::Vector2f velocityOrigin = mainLauncher->GetPosition() + delta * (1.0f - transitionAlpha);
                velocityOrigin -= smokeScreen.GetPosition();

                sf::Vector2f velocity = -delta;
                Helper::Normalize(velocity);
                velocity *= 50.0f;

                smokeScreen.GetFluidField().AddVelocity(velocityOrigin.x, velocityOrigin.y, velocity.x, velocity.y);
            }
        } else {
            //delta = levelNextStart - receiver->GetPosition();
            delta = levelNextStart - receiver.GetPosition();
        }
        SetPosition(delta * Helper::Ease(1.0f - transitionAlpha));

        for(Walls::iterator it = walls.begin(); it != walls.end(); ++it) {
            (*it)->RenderBackground(Target, alphaSecondPart);
        }
        for(Walls::iterator it = walls.begin(); it != walls.end(); ++it) {
            (*it)->RenderForeground(Target, alphaSecondPart);
        }

        for(Particles::iterator it = particleSystem.GetParticles().begin(); it != particleSystem.GetParticles().end(); ++it) {
            GameplayParticle& particle = *static_cast<GameplayParticle*>(*it);

            particleSprite.SetPosition(particle.GetPosition());
            particleSprite.SetColor(particle.GetColor());
            Target.Draw(particleSprite);
        }

        if(mainLauncher != NULL) {
            mainLauncher->SetAlpha(alphaFirstPart);
            Target.Draw(*mainLauncher);
        }

        for(Launchers::iterator it = optionalLaunchers.begin(); it != optionalLaunchers.end(); ++it) {
            mainLauncher->SetAlpha(alphaFirstPart);
            Target.Draw(**it);
        }

        /*if(receiver != NULL) {
            receiver->SetAlpha(alphaFirstPart);
            Target.Draw(*receiver);
        }*/
        receiver.SetAlpha(alphaFirstPart);
        Target.Draw(receiver);

        /* fingers feedback */
        if(state == ScreenState::Active) {
            const Fingers& fingers = FingerManager::Instance().GetFingers();
            for(Fingers::const_iterator it = fingers.begin(); it != fingers.end(); ++it) {
                const FingerData& data = *it;
                if(data.finger == 0)
                    continue;

                fingerSprite.SetPosition(data.ScreenSmoothX(Helper::BaseWidth), data.ScreenSmoothY(Helper::BaseHeight));
                Target.Draw(fingerSprite);
            }
        }

        if(debug) {
            particleSprite.SetColor(sf::Color::White);
            for(Constraints::iterator it = particleSystem.GetConstraints().begin(); it != particleSystem.GetConstraints().end(); ++it) {
                TrajectoryConstraint& constraint = *static_cast<TrajectoryConstraint*>(*it);

                particleSprite.SetPosition(constraint.GetCenter());
                Target.Draw(particleSprite);
            }
        }
    }

    void GameScreen::Clear()
    {
        particleSystem.Clear();

        //delete xmlLevel;
        //xmlLevel = NULL;
        //xmlLevel.reset();

        delete mainLauncher;
        mainLauncher = NULL;

        for(Launchers::iterator it = optionalLaunchers.begin(); it != optionalLaunchers.end(); ++it) {
            delete *it;
            *it = NULL;
        }
        optionalLaunchers.clear();

        //delete receiver;
        //receiver = NULL;

        for(Walls::iterator it = walls.begin(); it != walls.end(); ++it) {
            delete *it;
            *it = NULL;
        }
        walls.clear();

        flow.Clear();
    }

    void GameScreen::LoadLevel()
    {
        Clear();

        std::cout << "Loading level " << levelName << "...";
        std::auto_ptr<AT::XML::LevelType> xmlLevel = Helper::GetLevel(levelName);
        std::cout << "done!" << std::endl;

        OSCMessenger::Instance().LauncherRate(xmlLevel->rate());

        XML::LauncherType& xmlMainLauncher = xmlLevel->mainLauncher();

        int nParticles = Helper::Max(levelPreviousParticles, xmlMainLauncher.initialParticles());
        mainLauncher = new Launcher(sf::Vector2f(xmlMainLauncher.position().x(), xmlMainLauncher.position().y()), Helper::ToRadians(xmlMainLauncher.direction()), nParticles, xmlMainLauncher.speed(), xmlLevel->rate(), xmlMainLauncher.radius());

        levelNextStart = mainLauncher->GetPosition();
        if(levelName == Constants::Instance().FirstLevel()) {
            OSCMessenger::Instance().FirstLevel();
            levelPreviousStart = mainLauncher->GetPosition();
        }

        nextLevel = xmlLevel->nextLevel().present() ? xmlLevel->nextLevel().get() : "";

        XML::LaunchersType::LauncherSequence& xmlLaunchers = xmlLevel->optionalLaunchers().launcher();
        for(XML::LaunchersType::LauncherSequence::iterator it = xmlLaunchers.begin(); it != xmlLaunchers.end(); ++it) {
            optionalLaunchers.push_back(new Launcher(sf::Vector2f(it->position().x(), it->position().y()), Helper::ToRadians(it->direction()), it->initialParticles(), it->speed(), xmlLevel->rate(), it->radius()));
        }

        //receiver = new Receiver(sf::Vector2f(xmlLevel->receiver().position().x(), xmlLevel->receiver().position().y()), mainLauncher->GetInitialParticles(), xmlLevel->receiver().radius());
        receiver = Receiver(sf::Vector2f(xmlLevel->receiver().position().x(), xmlLevel->receiver().position().y()), mainLauncher->GetInitialParticles(), xmlLevel->receiver().radius());

        XML::WallsType::WallSequence& xmlWalls = xmlLevel->walls().wall();
        for(XML::WallsType::WallSequence::iterator it = xmlWalls.begin(); it != xmlWalls.end(); ++it) {
            walls.push_back(new Wall(sf::Vector2f(it->x(), it->y()), it->width(), it->height()));
        }

        XML::FlowType::VelocitySequence& xmlFlow = xmlLevel->flow().velocity();
        for(XML::FlowType::VelocitySequence::iterator it = xmlFlow.begin(); it != xmlFlow.end(); ++it) {

            float directionAngle = Helper::ToRadians(it->direction());
            sf::Vector2f direction = sf::Vector2f(cos(directionAngle), -sin(directionAngle));
            direction *= it->strength();

            std::cout << "direction: " << direction.x << "," << direction.y << std::endl;

            Flow::Velocity v = { it->position().x(), it->position().y(), direction.x, direction.y };
            flow.Add(v);
        }

        // place walls inside the smoke
        if(manager.GetGame().HasSmokeScreen()) {
            SmokeScreen& smokeScreen = manager.GetGame().GetSmokeScreen();
            //sf::Vector2f smokePosition = smokeScreen.GetPosition();
            sf::Vector2f smokePosition(0.0f, 0.0f);
            FluidField& fluidField = smokeScreen.GetFluidField();

            fluidField.ClearMap();

            for(Walls::iterator it = walls.begin(); it != walls.end(); ++it) {
                Wall& wall = *static_cast<Wall*>(*it);

                int cx1 = floor((wall.GetX1() - smokePosition.x) / fluidField.GetCellWidth());
                int cy1 = floor((wall.GetY1() - smokePosition.y) / fluidField.GetCellWidth());
                int cx2 = floor((wall.GetX2() - smokePosition.x) / fluidField.GetCellWidth());
                int cy2 = floor((wall.GetY2() - smokePosition.y) / fluidField.GetCellWidth());

                cx1 = Helper::Max(cx1, 0);
                cy1 = Helper::Max(cy1, 0);
                cx2 = Helper::Min(cx2, fluidField.GetGridWidth());
                cy2 = Helper::Min(cy2, fluidField.GetGridHeight());

                for(int x = cx1; x <= cx2; ++x) {
                    for(int y = cy1; y <= cy2; ++y) {
                        fluidField.SetMap(x, y, true);
                    }
                }
            }
        }
    }

    void GameScreen::NextLevel()
    {
        /* load next level */
        if(!nextLevel.empty()) {
            std::auto_ptr<AT::XML::LevelType> xmlNextLevel = Helper::GetLevel(nextLevel);
            levelNextStart = sf::Vector2f(
                xmlNextLevel->mainLauncher().position().x(),
                xmlNextLevel->mainLauncher().position().y()
            );
        } else {
            //levelNextStart = receiver->GetPosition();
            levelNextStart = receiver.GetPosition();
        }
        Exit();
    }
}