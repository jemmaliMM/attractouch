#ifndef _H_HELPER
#define _H_HELPER

#include <iostream>
#include <sstream>
#include <cmath>

#ifdef WIN32
#include <windows.h>
#endif

#include <SFML/Graphics.hpp>

#include "schemas/level-xml.h"

const float PI = 3.1415926f;
const float HALF_PI = PI * 0.5f;
const float QUARTER_PI = PI * 0.25f;
const float TWO_PI = PI * 2.0f;
const bool DEBUG_INITIAL = false;

class Helper
{
public:
    static const int BaseWidth = 1280;
    static const int BaseHeight = 1024;

    static std::auto_ptr<AT::XML::LevelType> GetLevel(const std::string& LevelName);

    static float ToDegrees(float Radians)
    { return Radians * 57.2957795f; }

    static float ToRadians(float Degrees)
    { return Degrees / 57.2957795f; }

    static int FindVideoModeIndex(sf::VideoMode modeToFind);
    static sf::VideoMode VideoModeOffset(sf::VideoMode mode, int offset, unsigned int bpp = 32);

    static float InvSqrt(float x);

    static float Ease(float x);
    static float Min(float a, float b);
    static float Max(float a, float b);
    static float Clamp(float v, float min, float max);

    static void Message(const std::string& Text);

    static sf::Color Blend(const sf::Color& A, const sf::Color& B, float Factor);

    static inline float Degrees(float Radians)
    { return Radians * 180.0f / PI; }
    static inline float Radians(float Degrees)
    { return Degrees * PI / 180.0f; }

    static float Magnitude(const sf::Vector2f& V);
    static void Normalize(sf::Vector2f& V);
    static sf::Vector2f Normal(const sf::Vector2f& V);
    static float Distance(const sf::Vector2f& A, const sf::Vector2f& B);
    static float Dot(const sf::Vector2f& A, const sf::Vector2f& B);
    static float Angle(const sf::Vector2f& A, const sf::Vector2f& B);

    static sf::Vector2f RotateCCW(const sf::Vector2f& V, float Angle);
    static sf::Vector2f RotateCW(const sf::Vector2f& V, float Angle);
    static sf::Vector2f Project(const sf::Vector2f& Origin, const sf::Vector2f& Direction, const sf::Vector2f& Point);
};

#endif