#include "gameplay/wall.h"

namespace AT {

    bool WallForeground::loaded = false;
    sf::Image WallForeground::imageFill;
    sf::Sprite WallForeground::spriteFill;

    WallForeground::WallForeground(const sf::Vector2f& Position, float Width, float Height)
        :sf::Drawable(Position, sf::Vector2f(1, 1), 0.0f), width(Width), height(Height), alpha(0.0f)
    {
        if(!loaded) {
            if(!imageFill.LoadFromFile("content/sprites/wall-fill.png"))
                throw std::exception("Can't load wall fill sprite");
            spriteFill.SetImage(imageFill);
            //spriteFill.SetBlendMode(sf::Blend::Add);
            spriteFill.SetCenter(0.0f, 0.0f);
            spriteFill.SetColor(sf::Color(255, 255, 255));
        }
    }

    WallForeground::~WallForeground()
    {

    }

    void WallForeground::Render(sf::RenderTarget& Target) const
    {
        // fill
        spriteFill.SetScale(sf::Vector2f(width, height));
        spriteFill.SetPosition(0.0f, 0.0f);
        spriteFill.SetColor(sf::Color(255, 255, 255, int(alpha * 255)));
        Target.Draw(spriteFill);
    }

    bool WallBackground::loaded = false;
    sf::Image WallBackground::imageBorderH;
    sf::Sprite WallBackground::spriteBorderH;
    sf::Image WallBackground::imageBorderV;
    sf::Sprite WallBackground::spriteBorderV;
    sf::Image WallBackground::imageCorner;
    sf::Sprite WallBackground::spriteCorner;

    WallBackground::WallBackground(const sf::Vector2f& Position, float Width, float Height)
        :sf::Drawable(Position, sf::Vector2f(1, 1), 0.0f), width(Width), height(Height), alpha(0.0f)
    {
        if(!loaded) {
            if(!imageBorderH.LoadFromFile("content/sprites/wall-border-h.png"))
                throw std::exception("Can't load wall horizontal border sprite");
            spriteBorderH.SetImage(imageBorderH);
            spriteBorderH.SetBlendMode(sf::Blend::Add);
            spriteBorderH.SetCenter(0.0f, 0.0f);
            //spriteBorderH.SetColor(sf::Color(0, 204, 255));

            if(!imageBorderV.LoadFromFile("content/sprites/wall-border-v.png"))
                throw std::exception("Can't load wall vertical border sprite");
            spriteBorderV.SetImage(imageBorderV);
            spriteBorderV.SetBlendMode(sf::Blend::Add);
            spriteBorderV.SetCenter(0.0f, 0.0f);
            //spriteBorderV.SetColor(sf::Color(0, 204, 255));

            if(!imageCorner.LoadFromFile("content/sprites/wall-corner.png"))
                throw std::exception("Can't load wall corner sprite");
            spriteCorner.SetImage(imageCorner);
            spriteCorner.SetBlendMode(sf::Blend::Add);
            spriteCorner.SetCenter(0.0f, 0.0f);
            //spriteCorner.SetColor(sf::Color(0, 204, 255));

            loaded = true;
        }
    }

    WallBackground::~WallBackground()
    {

    }

    void WallBackground::Render(sf::RenderTarget& Target) const
    {
        spriteCorner.SetColor(sf::Color(255, 255, 255, int(alpha * 255)));
        spriteBorderH.SetColor(sf::Color(255, 255, 255, int(alpha * 255)));
        spriteBorderV.SetColor(sf::Color(255, 255, 255, int(alpha * 255)));

        // top left corner
        spriteCorner.SetRotation(180.0f);
        spriteCorner.SetPosition(0.0f, 0.0f);
        Target.Draw(spriteCorner);

        // top right corner
        spriteCorner.SetRotation(90.0f);
        spriteCorner.SetPosition(width, 0.0f);
        Target.Draw(spriteCorner);

        // bottom right corner
        spriteCorner.SetRotation(0.0f);
        spriteCorner.SetPosition(width, height);
        Target.Draw(spriteCorner);

        // bottom left corner
        spriteCorner.SetRotation(-90.0f);
        spriteCorner.SetPosition(0.0f, height);
        Target.Draw(spriteCorner);

        // top border
        spriteBorderH.SetRotation(180.0f);
        spriteBorderH.SetScale(sf::Vector2f(width, 1.0f));
        spriteBorderH.SetPosition(width, 0.0f);
        Target.Draw(spriteBorderH);

        // right border
        spriteBorderV.SetRotation(0.0f);
        spriteBorderV.SetScale(sf::Vector2f(1.0f, height));
        spriteBorderV.SetPosition(width, 0.0f);
        Target.Draw(spriteBorderV);

        // bottom border
        spriteBorderH.SetRotation(0.0f);
        spriteBorderH.SetScale(sf::Vector2f(width, 1.0f));
        spriteBorderH.SetPosition(0.0f, height);
        Target.Draw(spriteBorderH);

        // left border
        spriteBorderV.SetRotation(180.0f);
        spriteBorderV.SetScale(sf::Vector2f(1.0f, height));
        spriteBorderV.SetPosition(0.0f, height);
        Target.Draw(spriteBorderV);
    }

    Wall::Wall(const sf::Vector2f& Position, float Width, float Height)
        :x(Position.x), y(Position.y), width(Width), height(Height), x1(Position.x), y1(Position.y), x2(Position.x + Width), y2(Position.y + Height), foreground(Position, Width, Height), background(Position, Width, Height)
    {
        
    }

    Wall::~Wall()
    {

    }

    bool Wall::IsInside(const sf::Vector2f& Point) const
    {
        return !(Point.x < x1 || Point.y < y1 || Point.x > x2 || Point.y > y2);
    }

    bool Wall::Intersect(const sf::Vector2f& Point, Intersection& Result) const
    {
        Result.X = Point.x;
        Result.Y = Point.y;

        if(IsInside(Point)) {
            // top
            Result.NormalX = 0.0f;
            Result.NormalY = -1.0f;
            Result.ReverseX = 1.0f;
            Result.ReverseY = -1.0f;
            Result.Distance = abs(y1 - Point.y);

            // right
            if(abs(x2 - Point.x) < Result.Distance) {
                Result.NormalX = 1.0f;
                Result.NormalY = 0.0f;
                Result.ReverseX = -1.0f;
                Result.ReverseY = 1.0f;
                Result.Distance = abs(x2 - Point.x);
            }
            // bottom
            if(abs(y2 - Point.y) < Result.Distance) {
                Result.NormalX = 0.0f;
                Result.NormalY = 1.0f;
                Result.ReverseX = 1.0f;
                Result.ReverseY = -1.0f;
                Result.Distance = abs(y2 - Point.y);
            }
            // left
            if(abs(x1 - Point.x) < Result.Distance) {
                Result.NormalX = -1.0f;
                Result.NormalY = 0.0f;
                Result.ReverseX = -1.0f;
                Result.ReverseY = 1.0f;
                Result.Distance = abs(x1 - Point.x);
            }

            return true;
        }

        return false;
    }

    void Wall::RenderForeground(sf::RenderTarget& Target, float Alpha)
    {
        foreground.SetAlpha(Alpha);
        Target.Draw(foreground);
    }

    void Wall::RenderBackground(sf::RenderTarget& Target, float Alpha)
    {
        background.SetAlpha(Alpha);
        Target.Draw(background);
    }
}