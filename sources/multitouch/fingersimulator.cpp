#include "multitouch/fingersimulator.h"

namespace AT {

    FingerSimulator::FingerSimulator()
        :server(0), draggedFinger(0), width(1), height(1)
    {

    }

    FingerSimulator::~FingerSimulator()
    {
        
    }

    FingerSimulator& FingerSimulator::Instance()
    {
        static FingerSimulator instance;
        return instance;
    }

    void FingerSimulator::Start(int PortTUIO, int Width, int Height)
    {
        if(server == 0) {
            server = new TUIO::TuioServer("127.0.0.1", PortTUIO);
            server->setVerbose(false);
        }
        width = Width;
        height = Height;
    }

    void FingerSimulator::Stop()
    {
        if(server != 0) {
            delete server;
            server = 0;
        }
    }

    void FingerSimulator::Update()
    {
        
    }

    Finger* FingerSimulator::FindNearest(int X, int Y)
    {
        float maxDistance = 5.0f;
        Finger *foundFinger = 0;

        for(SimulatedFingers::iterator it = fingers.begin(); it != fingers.end(); ++it) {
            Finger *finger = *it;
            int cursorX = finger->getScreenX(width);
            int cursorY = finger->getScreenY(height);

            float deltaX = float(cursorX - X);
            float deltaY = float(cursorY - Y);

            float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

            if(distance < maxDistance) {
                maxDistance = distance;
                foundFinger = finger;
            }
        }

        return foundFinger;
    }

    void FingerSimulator::Process(sf::Event &Event)
    {
        if(server == 0)
            return;
        server->initFrame(TUIO::TuioTime::getSessionTime());

        if(Event.Type == sf::Event::MouseButtonPressed && draggedFinger == 0) {

            Finger *fingerNearest = FindNearest(Event.MouseButton.X, Event.MouseButton.Y);

            if(Event.MouseButton.Button == sf::Mouse::Left) {
                if(fingerNearest == 0) {
                    fingerNearest = server->addTuioCursor(Event.MouseButton.X / (float)width, Event.MouseButton.Y / (float)height);
                }
                draggedFinger = fingerNearest;
            }
            if(Event.MouseButton.Button == sf::Mouse::Right) {
                if(fingerNearest == 0) {
                    fingerNearest = server->addTuioCursor(Event.MouseButton.X / (float)width, Event.MouseButton.Y / (float)height);
                    fingers.push_back(fingerNearest);
                } else {
                    for(SimulatedFingers::iterator it = fingers.begin(); it != fingers.end();) {
                        Finger *finger = *it;
                        if(finger->getSessionID() == fingerNearest->getSessionID()) {
                            it = fingers.erase(it);
                        } else
                            ++it;
                    }
                    server->removeTuioCursor(fingerNearest);
                }
            }
        }
        if(Event.Type == sf::Event::MouseButtonReleased) {
 
            float mouseX = Event.MouseButton.X / (float)width;
            float mouseY = Event.MouseButton.Y / (float)height;

            if(draggedFinger != 0) {

                bool isSticky = false;
                for(SimulatedFingers::iterator it = fingers.begin(); it != fingers.end(); ++it) {
                    Finger *finger = *it;
                    if(finger->getSessionID() == draggedFinger->getSessionID()) {
                        isSticky = true;
                        break;
                    }
                }

                if(!isSticky) {
                    server->removeTuioCursor(draggedFinger);
                }
                draggedFinger = 0;
            }
        }
        if(Event.Type == sf::Event::MouseMoved) {

            float mouseX = Event.MouseMove.X / (float)width;
            float mouseY = Event.MouseMove.Y / (float)height;

            if(draggedFinger != 0) {
                server->updateTuioCursor(draggedFinger, mouseX, mouseY);
            }
        }

        server->stopUntouchedMovingCursors();
        server->commitFrame();
    }


}