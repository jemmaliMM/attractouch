#ifndef _FINGER_SIMULATOR_H
#define _FINGER_SIMULATOR_H

#include <vector>

#include "TuioServer.h"
#include "SFML/Graphics.hpp"

#include "multitouch/fingermanager.h"

namespace AT {

    typedef std::vector<Finger*> SimulatedFingers;

    class FingerSimulator
    {
    private:
        TUIO::TuioServer *server;

        SimulatedFingers fingers;

        Finger *draggedFinger;

        int width, height;

        FingerSimulator();
        virtual ~FingerSimulator();

        Finger* FindNearest(int X, int Y);
    public:
        static FingerSimulator& Instance();

        void Start(int PortTUIO, int Width, int Height);
        void Stop();

        void Update();
        void Process(sf::Event& Event);
    };
}

#endif
