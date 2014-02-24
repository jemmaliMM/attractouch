#ifndef _BUTTON_H
#define _BUTTON_H

#include <exception>

#include <SFML/Graphics.hpp>

namespace AT {

    class Button : public sf::Drawable
    {
    public:
        typedef void (*OnClickCallback)(int ID, void *Data);
    private:
        sf::Image imageNormal, imageHover;
        sf::Sprite spriteNormal, spriteHover;

        OnClickCallback onClick;
        void *onClickData;

        bool hover;

        int id;
    public:
        Button(const std::string& FileNormal = "", const std::string& FileHover = "", const sf::Vector2f& Position = sf::Vector2f(0, 0), const sf::Vector2f& Scale = sf::Vector2f(1, 1), float Rotation = 0.f, const sf::Color& Col = sf::Color(255, 255, 255, 255));
        ~Button();

        void Initialise(const std::string& FileNormal, const std::string& FileHover = "");

        bool IsOver(int x, int y);

        void SetOnClick(OnClickCallback OnClick, void *Data = NULL)
        { onClick = OnClick; onClickData = Data; }

        int GetID() const
        { return id; }
        void SetID(int ID)
        { id = ID; }

        void Process(const sf::Event& Event);

        virtual void Render(sf::RenderTarget& Target) const;
    };
}

#endif