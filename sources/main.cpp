
#include <memory>
#include <sstream>
#include <iostream>
#include <exception>

#include <SFML/Graphics.hpp>

#include "game.h"
#include "utils/config.h"
#include "utils/argparser.h"
#include "utils/constants.h"

int main(int argc, char **argv)
{
    AT::ArgParser::Instance().Parse(argc, argv);

    AT::Config config("content/settings.xml");
    if(!config.Prompt())
        return 0;

    // Prepare video mode
    sf::VideoMode VideoMode = config.GetVideoMode();
    if(!VideoMode.IsValid())
        throw std::exception("Invalid video mode");

    // Create the window of the application
    sf::RenderWindow App(
        VideoMode,
        "AttracTouch",
        sf::Style::Close | (config.Get()->fullscreen() ? sf::Style::Fullscreen : 0)
    );
    App.PreserveOpenGLStates(true);

    // Load the text font
    sf::Font BitmapFont;
    if (!BitmapFont.LoadFromFile("content/fonts/droidsansmono.ttf", 10))
        throw std::exception("Can't load font");

    // Initialize the FPS text
    sf::String FPSText("", BitmapFont);
    FPSText.SetSize(10.0f);
    FPSText.Move(10.0f, 10.0f);
    FPSText.SetColor(sf::Color::White);
    
    // FPS Helpers
    bool showFPS = false;
    int frameCount = 0;
    std::stringstream ss;

    // Update Helpers
    float TimeStep = 0.01f;
    float TimeAccumulator = 0.0f;

    // Clocks for the game
    sf::Clock ClockFPS;
    sf::Clock ClockUpdate;

    // Game logic
    std::string firstLevel = AT::ArgParser::Instance().Level();
    AT::Game Game(App, config.Get()->portTUIO(), config.Get()->portOSC(), !AT::ArgParser::Instance().Level().empty(), firstLevel);

    while (App.IsOpened())
    {
        // Compute FPS
        ++frameCount;
        if(ClockFPS.GetElapsedTime() >= 1.0f) {
            ss.str("");
            ss << "FPS: " << frameCount;
            FPSText.SetText(ss.str());

            frameCount = 0;
            ClockFPS.Reset();
        }

        // Update loop
        float FrameTime = ClockUpdate.GetElapsedTime();
        ClockUpdate.Reset();
        TimeAccumulator += FrameTime;
        while(TimeAccumulator >= TimeStep) {
            Game.Update(TimeStep);
            TimeAccumulator -= TimeStep;
        }

        // Handle events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Window closed or escape key pressed : exit
            if ((Event.Type == sf::Event::Closed) ||
               ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Q)))
            {
                App.Close();
                break;
            }
            // Show FPS
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F))
            {
                showFPS = !showFPS;
            }
            Game.Process(Event);
        }

        // Clear the window
        App.Clear();

        // Draw game
        Game.Draw();

        // Display FPS
        if(showFPS)
            App.Draw(FPSText);

        // Display things on screen
        App.Display();
    }

    return 0;
}
