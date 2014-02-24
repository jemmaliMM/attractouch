#ifndef _CONFIG_H
#define _CONFIG_H

#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "schemas/settings-xml.h"
#include "utils/button.h"
#include "utils/helper.h"

namespace AT
{
    class Config
    {
    private:
        enum {
            ID_MODE_LEFT,
            ID_MODE_RIGHT,
            ID_FULLSCREEN,
            ID_OK,
            ID_CANCEL
        };

        std::string fileName;
        Settings *xmlSettings;

        bool exit;
        bool cancelled;

        bool error;
        std::string errorMessage;

        sf::Font font;
        sf::Image splashImage;

        sf::VideoMode selectedVideoMode;
        bool isFullscreen;

        Button buttonModeLeft;
        Button buttonModeRight;
        Button buttonFullscreen;
        Button buttonOK;
        Button buttonCancel;
    public:
        Config(const std::string& fileName);
        ~Config();

        void Load();
        bool Process(const sf::Event& Event);
        static void OnButtonClick(int ID, void *data);
        bool Prompt();

        void Save();

        const sf::VideoMode& GetVideoMode() const
        { return selectedVideoMode; }

        const Settings* Get() const
        { return xmlSettings; }
    };

}

#endif