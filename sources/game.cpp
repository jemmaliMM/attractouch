#include "game.h"

namespace AT {

    Game::Game(sf::RenderWindow& Window, int PortTUIO, int PortOSC, bool SkipMenu, const std::string& FirstLevel)
        :screenManager(Window, this), smokeScreen(NULL), menuScreen(NULL)
    {
        Window.GetDefaultView().SetFromRect(sf::FloatRect(0, 0, Helper::BaseWidth, Helper::BaseHeight));

        OSCMessenger::Instance().Start(PortOSC);
        FingerManager::Instance().Start(PortTUIO);
        FingerSimulator::Instance().Start(PortTUIO, Window.GetWidth(), Window.GetHeight());

        smokeScreen = new SmokeScreen(screenManager);
        smokeScreen->Show();

        if(!SkipMenu) {
            menuScreen = new MenuScreen(screenManager, FirstLevel);
            menuScreen->Show();
        } else {
            (new LoadingScreen(screenManager))->Add((new GameScreen(screenManager))->SetLevel(FirstLevel))->Show();
        }
    }

    Game::~Game()
    {
        OSCMessenger::Instance().End();
        OSCMessenger::Instance().Stop();
        FingerManager::Instance().Stop();
        FingerSimulator::Instance().Stop();

        smokeScreen = NULL;
        menuScreen = NULL;
    }

    void Game::SetState(GameState::Value State)
    {
        gameState = State;

        if(gameState == GameState::Game)
        {
            if(smokeScreen != NULL)
                smokeScreen->ApplyNoise(true);
        }
    }

    void Game::Process(sf::Event& Event)
    {
        FingerSimulator::Instance().Process(Event);

        screenManager.Process(Event);
    }

    void Game::Update(float TimeStep)
    {
        FingerManager::Instance().Update(TimeStep);
        screenManager.Update(TimeStep);
    }

    void Game::Draw()
    {
        screenManager.Draw();
    }

}
