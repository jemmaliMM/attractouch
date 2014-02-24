#ifndef _ARG_PARSER_H
#define _ARG_PARSER_H

#include <exception>
#include <iostream>
#include <string>

namespace AT {

    class ArgParser
    {
    private:
        std::string level;

        ArgParser();
        ~ArgParser()
        {}
        ArgParser(const ArgParser&)
        {}
        ArgParser& operator=(const ArgParser&)
        { return *this; }
    public:
        static ArgParser& Instance();

        void Parse(int argc, char **argv);

        const std::string& Level() const
        { return level; }
    };
}

#endif