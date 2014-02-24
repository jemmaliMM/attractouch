#include "utils/config.h"

namespace AT {

    Config::Config(const std::string& fileName)
        :fileName(fileName), xmlSettings(NULL), exit(false), cancelled(false), error(false), errorMessage()
    {
        try {
            xmlSettings = settings(fileName).release();
        } catch(xml_schema::Exception& ex) {
            std::stringstream ss;
            ss << ex << std::endl;

            error = true;
            errorMessage = ss.str();
        }

        // recover from error by loading default values
        if(error) {
            error = false;

            xmlSettings = new Settings(
                Settings::widthDefaultValue(),
                Settings::heightDefaultValue(),
                Settings::fullscreenDefaultValue(),
                Settings::portTUIODefaultValue(),
                Settings::portOSCDefaultValue()
            );
        }

        // there is no more error, load settings
        if(!error) {
            selectedVideoMode.Width = xmlSettings->width();
            selectedVideoMode.Height = xmlSettings->height();
            selectedVideoMode.BitsPerPixel = 32; // always 32 bits
            isFullscreen = xmlSettings->fullscreen();
        }

        Load();
    }

    Config::~Config()
    {
        delete xmlSettings;
    }

    void Config::Load()
    {
        // Load the text font
        if (!font.LoadFromFile("content/fonts/mido.otf", 18))
            throw std::exception("Can't load font");

        // Load the splash screen
        if (!splashImage.LoadFromFile("content/splash/splash.png"))
            throw std::exception("Can't load splash");

        // Load buttons
        buttonModeLeft.Initialise("content/splash/arrow-left.png", "content/splash/arrow-left-hover.png");
        buttonModeLeft.SetID(ID_MODE_LEFT);
        buttonModeLeft.SetOnClick(&OnButtonClick, this);
        buttonModeLeft.SetPosition(120, 452);
        buttonModeRight.Initialise("content/splash/arrow-right.png", "content/splash/arrow-right-hover.png");
        buttonModeRight.SetID(ID_MODE_RIGHT);
        buttonModeRight.SetOnClick(&OnButtonClick, this);
        buttonModeRight.SetPosition(240, 452);
        buttonFullscreen.Initialise("content/splash/arrow-turn.png", "content/splash/arrow-turn-hover.png");
        buttonFullscreen.SetID(ID_FULLSCREEN);
        buttonFullscreen.SetOnClick(&OnButtonClick, this);
        buttonFullscreen.SetPosition(430, 452);
        buttonOK.Initialise("content/splash/button-ok.png", "content/splash/button-ok-hover.png");
        buttonOK.SetID(ID_OK);
        buttonOK.SetOnClick(&OnButtonClick, this);
        buttonOK.SetPosition(480, 449);
        buttonCancel.Initialise("content/splash/button-cancel.png", "content/splash/button-cancel-hover.png");
        buttonCancel.SetID(ID_CANCEL);
        buttonCancel.SetOnClick(&OnButtonClick, this);
        buttonCancel.SetPosition(535, 449);
    }
    
    // return true to continue
    bool Config::Process(const sf::Event& Event)
    {
        // Window closed or escape key pressed : exit
        if ((Event.Type == sf::Event::Closed) ||
            ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
        {
            cancelled = true;
            return false;
        }

        // Accept settings
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
        {
            return false;
        }

        buttonModeLeft.Process(Event);
        buttonModeRight.Process(Event);
        buttonFullscreen.Process(Event);
        buttonOK.Process(Event);
        buttonCancel.Process(Event);

        return true;
    }

    

    void Config::OnButtonClick(int ID, void *Data)
    {
        Config& config = *static_cast<Config*>(Data);
        switch(ID) {
            case ID_MODE_LEFT:
                config.selectedVideoMode = Helper::VideoModeOffset(config.selectedVideoMode, +1);
                break;
            case ID_MODE_RIGHT:
                config.selectedVideoMode = Helper::VideoModeOffset(config.selectedVideoMode, -1);
                break;
            case ID_FULLSCREEN:
                config.isFullscreen = !config.isFullscreen;
                break;
            case ID_OK:
                config.exit = true;
                config.cancelled = false;
                break;
            case ID_CANCEL:
                config.exit = true;
                config.cancelled = true;
                break;
        }
        std::cout << " New video mode: " << config.selectedVideoMode.Width << " x " << config.selectedVideoMode.Height << " (" << config.selectedVideoMode.BitsPerPixel << " bits)" << std::endl;
    }

    bool Config::Prompt()
    {
        static sf::String String("", font, 18.0f);
        static sf::Sprite Splash(splashImage);

        // Prepare video mode
        sf::VideoMode VideoMode(640, 480, 32);
        if(!VideoMode.IsValid())
            throw std::exception("Invalid video mode");

        // Create the window of the application
        sf::RenderWindow App(
            VideoMode,
            "AttracTouch - configuration",
            sf::Style::None
        );

        std::stringstream ss;
        sf::FloatRect tempRect;

        while (App.IsOpened())
        {
            // Handle events
            sf::Event Event;
            while (App.GetEvent(Event))
            {
                if(!Process(Event)) {
                    exit = true;
                }
            }
            if(exit)
                App.Close();

            // Clear the window
            App.Clear();

            App.Draw(Splash);

            // Resolution text
            String.SetText("Resolution");
            String.SetColor(sf::Color(102, 102, 102));
            String.SetCenter(0.0f, 0.0f);
            String.SetPosition(13.0f, VideoMode.Height - 34.0f);
            App.Draw(String);

            // Resolution
            ss.str("");
            ss << selectedVideoMode.Width << " x " << selectedVideoMode.Height;
            String.SetText(ss.str());
            tempRect = String.GetRect();
            String.SetColor(sf::Color::White);
            String.SetCenter(tempRect.GetWidth() * 0.5f, 0.0f);
            String.SetPosition(186.0f, VideoMode.Height - 34.0f);
            App.Draw(String);

            // Resolution button left
            App.Draw(buttonModeLeft);
            App.Draw(buttonModeRight);
            App.Draw(buttonFullscreen);
            App.Draw(buttonOK);
            App.Draw(buttonCancel);

            // Fullscreen text
            String.SetText("Fullscreen?");
            String.SetColor(sf::Color(102, 102, 102));
            String.SetCenter(0.0f, 0.0f);
            String.SetPosition(280.0f, VideoMode.Height - 34.0f);
            App.Draw(String);

            // Fullscreen
            String.SetText(isFullscreen ? "Yes" : "No");
            String.SetColor(sf::Color::White);
            String.SetCenter(0.0f, 0.0f);
            String.SetPosition(390.0f, VideoMode.Height - 34.0f);
            App.Draw(String);

            // Display things on screen
            App.Display();
        }

        if(!cancelled) {
            Save(); // Save settings into original XML file
        }

        return !cancelled;
    }

    void Config::Save()
    {
        xmlSettings->width(selectedVideoMode.Width);
        xmlSettings->height(selectedVideoMode.Height);
        xmlSettings->fullscreen(isFullscreen);

        std::ofstream f(fileName.c_str());
        xml_schema::NamespaceInfomap map;
        map[""].schema = "settings.xsd";
        settings(f, *xmlSettings, map, "UTF-8");
    }

}