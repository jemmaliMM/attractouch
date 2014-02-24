#include "utils/helper.h"

std::auto_ptr<AT::XML::LevelType> Helper::GetLevel(const std::string& LevelName)
{
    std::stringstream ss;

    ss << "content/levels/" << LevelName << ".xml";
    std::string fileName = ss.str();

    std::auto_ptr<AT::XML::LevelType> xmlLevel;
    try {
        xmlLevel = AT::XML::level(fileName);
    } catch(xml_schema::Exception& ex) {
        ss.str("");
        ss << ex;
        Helper::Message(ss.str());
        throw;
    }

    return xmlLevel;
}

sf::Color Helper::Blend(const sf::Color& A, const sf::Color& B, float Factor)
{
    return sf::Color(
        sf::Uint8((1.0f - Factor) * A.r) + sf::Uint8(Factor * B.r),
        sf::Uint8((1.0f - Factor) * A.g) + sf::Uint8(Factor * B.g),
        sf::Uint8((1.0f - Factor) * A.b) + sf::Uint8(Factor * B.b),
        sf::Uint8((1.0f - Factor) * A.a) + sf::Uint8(Factor * B.a)
    );
}

float Helper::Magnitude(const sf::Vector2f& V)
{
    return sqrt(Dot(V, V));
}

void Helper::Normalize(sf::Vector2f& V)
{
    float magSquared = Dot(V, V);
    if(magSquared <= 0.0000001f)
        magSquared = 0.0000001f;

    V /= sqrt(magSquared);
}

sf::Vector2f Helper::Normal(const sf::Vector2f& V)
{
    return sf::Vector2f(-V.y, V.x);
}

float Helper::Distance(const sf::Vector2f& A, const sf::Vector2f& B)
{
    return Magnitude(B - A);
}

float Helper::Dot(const sf::Vector2f& A, const sf::Vector2f& B)
{
    return A.x * B.x + A.y * B.y;
}

float Helper::Angle(const sf::Vector2f& A, const sf::Vector2f& B)
{
    return atan2(Dot(Normal(A), B), Dot(A, B));
    //return atan2(Dot(A, B), Dot(Normal(A), B));
}

// counter clockwise
sf::Vector2f Helper::RotateCCW(const sf::Vector2f& V, float Angle)
{
    float cosAngle = cos(Angle);
    float sinAngle = sin(Angle);
    return sf::Vector2f(V.x * cosAngle + V.y * sinAngle, -V.x * sinAngle + V.y * cosAngle);
}

// clockwise
sf::Vector2f Helper::RotateCW(const sf::Vector2f& V, float Angle)
{
    float cosAngle = cos(Angle);
    float sinAngle = sin(Angle);
    return sf::Vector2f(V.x * cosAngle - V.y * sinAngle, V.x * sinAngle + V.y * cosAngle);
}

sf::Vector2f Helper::Project(const sf::Vector2f& Origin, const sf::Vector2f& Direction, const sf::Vector2f& Point)
{
    float u = Dot(Point - Origin, Direction) / Dot(Direction, Direction);
    return Origin + Direction * u;
}

int Helper::FindVideoModeIndex(sf::VideoMode modeToFind)
{
    int index = -1;
    for(unsigned int i = 0; i < sf::VideoMode::GetModesCount(); ++i) {
        sf::VideoMode mode = sf::VideoMode::GetMode(i);
        if(modeToFind == mode) {
            index = (int)i;
            break;
        }
    }
    return index;
}

sf::VideoMode Helper::VideoModeOffset(sf::VideoMode mode, int offset, unsigned int bpp)
{
    int index = FindVideoModeIndex(mode);
    if(index < 0)
        throw std::exception("Can't find video mode");

    sf::VideoMode newMode;
    do {
        index += offset;
        if(index < 0)
            index += sf::VideoMode::GetModesCount();
        if(index >= (int)sf::VideoMode::GetModesCount())
            index -= sf::VideoMode::GetModesCount();

        newMode = sf::VideoMode::GetMode(index);
    } while(newMode.BitsPerPixel != bpp);

    return newMode;
}

// from http://betterexplained.com/articles/understanding-quakes-fast-inverse-square-root/
float Helper::InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x; // store floating-point bits in integer
    i = 0x5f3759d5 - (i >> 1); // initial guess for Newton's method
    x = *(float*)&i; // convert new bits into float
    x = x*(1.5f - xhalf*x*x); // One round of Newton's method
    return x;
}

float Helper::Ease(float X)
{
    return (float)(X - sin(X * PI * 2.0f) / (PI * 2.0f));
}

float Helper::Min(float a, float b)
{
    return a < b ? a : b;
}

float Helper::Max(float a, float b)
{
    return a > b ? a : b;
}

float Helper::Clamp(float v, float min, float max)
{
    if(v < min)
        v = min;
    if(v > max)
        v = max;
    return v;
}

void Helper::Message(const std::string& Text)
{
    std::cout << Text << std::endl;
#ifdef WIN32
    MessageBox(NULL, Text.c_str(), "Message", MB_OK);
#endif
}