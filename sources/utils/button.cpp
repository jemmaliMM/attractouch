#include "utils/button.h"

namespace AT {

    Button::Button(const std::string& FileNormal, const std::string& FileHover, const sf::Vector2f& Position, const sf::Vector2f& Scale, float Rotation, const sf::Color& Col)
        :sf::Drawable(Position, Scale, Rotation, Col), onClick(NULL), onClickData(NULL), hover(false)
    {
        Initialise(FileNormal, FileHover);
    }

    Button::~Button()
    {
        
    }

    void Button::Initialise(const std::string& FileNormal, const std::string& FileHover)
    {
        if(!FileNormal.empty()) {
            if(!imageNormal.LoadFromFile(FileNormal))
                std::exception("Can't load button normal image");
            spriteNormal.SetImage(imageNormal);
        }

        if(!FileHover.empty()) {
            if(!imageHover.LoadFromFile(FileHover))
                throw std::exception("Can't load button hover image");
            spriteHover.SetImage(imageHover);
        }
    }

    bool Button::IsOver(int x, int y)
    {
        sf::FloatRect bounds;

        bounds.Left = GetPosition().x - GetCenter().x;
        bounds.Top = GetPosition().y - GetCenter().y;
        bounds.Right = bounds.Left + imageNormal.GetWidth();
        bounds.Bottom = bounds.Top + imageNormal.GetHeight();

        return bounds.Contains((float)x, (float)y);
    }

    void Button::Process(const sf::Event &Event)
    {
        if(Event.Type == sf::Event::MouseMoved) {
            hover = IsOver(Event.MouseMove.X, Event.MouseMove.Y);
        }
        if(Event.Type == sf::Event::MouseButtonReleased && Event.MouseButton.Button == sf::Mouse::Left && hover) {
            if(onClick != NULL)
                onClick(id, onClickData);
        }
    }

    void Button::Render(sf::RenderTarget& Target) const
    {
        sf::Sprite& sprite = const_cast<sf::Sprite&>(hover ? (spriteHover.GetImage() == NULL ? spriteNormal : spriteHover) : spriteNormal);

        /*sprite.SetPosition(GetPosition());
        sprite.SetCenter(GetCenter());
        sprite.SetScale(GetScale());
        sprite.SetRotation(GetRotation());
        sprite.SetColor(GetColor());*/

        Target.Draw(sprite);
    }
}