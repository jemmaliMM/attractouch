#ifndef _WALL_H
#define _WALL_H

#include <SFML/Graphics.hpp>

#include "utils/helper.h"

namespace AT {

    class WallForeground : public sf::Drawable
    {
    private:
        float width, height;
        float alpha;

        static bool loaded;
        static sf::Image imageFill;
        static sf::Sprite spriteFill;
    public:
        WallForeground(const sf::Vector2f& Position, float Width, float Height);
        virtual ~WallForeground();

        void SetAlpha(float Alpha)
        { alpha = Alpha; }

        virtual void Render(sf::RenderTarget& Target) const;
    };

    class WallBackground : public sf::Drawable
    {
    private:
        float width, height;
        float alpha;

        static bool loaded;
        static sf::Image imageBorderH;
        static sf::Sprite spriteBorderH;
        static sf::Image imageBorderV;
        static sf::Sprite spriteBorderV;
        static sf::Image imageCorner;
        static sf::Sprite spriteCorner;
    public:
        WallBackground(const sf::Vector2f& Position, float Width, float Height);
        virtual ~WallBackground();

        void SetAlpha(float Alpha)
        { alpha = Alpha; }

        virtual void Render(sf::RenderTarget& Target) const;
    };

    class Wall
    {
    public:
        struct Intersection
        {
            float X, Y;
            float NormalX, NormalY;
            float ReverseX, ReverseY;
            float Distance;
        };
    private:
        float x, y, width, height;
        float x1, y1, x2, y2;

        WallForeground foreground;
        WallBackground background;
    public:
        Wall(const sf::Vector2f& Position, float Width, float Height);
        virtual ~Wall();

        float GetX() const
        { return x; }
        float GetY() const
        { return y; }
        float GetWidth() const
        { return width; }
        float GetHeight() const
        { return height; }

        float GetX1() const
        { return x1; }
        float GetY1() const
        { return y1; }
        float GetX2() const
        { return x2; }
        float GetY2() const
        { return y2; }

        bool IsInside(const sf::Vector2f& Point) const;
        bool Intersect(const sf::Vector2f& Point, Intersection& Result) const;

        void RenderForeground(sf::RenderTarget& Target, float Alpha);
        void RenderBackground(sf::RenderTarget& Target, float Alpha);
    };
}

#endif
