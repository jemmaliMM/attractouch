#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <iostream>
#include <string>

#include "schemas/constants-xml.h"

namespace AT {

    class Constants
    {
    private:
        float fingerRadius;
        std::string firstLevel;

        Constants();
        ~Constants()
        {}
        Constants(const Constants&)
        {}
        Constants& operator=(const Constants&)
        { return *this; }
    public:
        static Constants& Instance();

        float FingerRadius() const
        { return fingerRadius; }
        const std::string& FirstLevel() const
        { return firstLevel; }
    };
}

#endif