#include "multitouch/fingermanager.h"
#include "multitouch/oscmessenger.h"

namespace AT {

    void FingerData::Update(Finger *Finger)
    {
        if(finger != NULL)
            finger->update(Finger);
        x = finger->getX();
        y = finger->getY();
        lastUpdateTime = finger->getTuioTime();
    }

    void FingerData::UpdateSmooth()
    {
        smoothX += (x - smoothX) * 0.1f;
        smoothY += (y - smoothY) * 0.1f;
    }

    float FingerData::ScreenX(int Width) const
    {
        return x * Width;
    }

    float FingerData::ScreenY(int Height) const
    {
        return y * Height;
    }

    float FingerData::ScreenSmoothX(int Width) const
    {
        return smoothX * Width;
    }

    float FingerData::ScreenSmoothY(int Height) const
    {
        return smoothY * Height;
    }

    FingerManager::FingerManager()
        :client(0), nFingers(0), isFingerOK(0), isFingerOKData(0)
    {

    }

    FingerManager::~FingerManager()
    {
        Stop();
        delete client;
    }

    FingerManager& FingerManager::Instance()
    {
        static FingerManager instance;
        return instance;
    }

    FingerData FingerManager::MakeData(Finger *Finger)
    {
        FingerData data = {
            Finger,
            Finger->getX(), Finger->getY(),
            Finger->getX(), Finger->getY(),
            Finger->getTuioTime()
        };
        return data;
    }

    void FingerManager::Start(int PortTUIO)
    {
        if(client == 0) {
            client = new TUIO::TuioClient(PortTUIO);
            client->addTuioListener(this);
        }

        if(client != 0 && !client->isConnected()) {
            client->connect();
        }
    }

    void FingerManager::Stop()
    {
        nFingers = 0;
        fingers.clear();

        if(client != 0) {
            if(client->isConnected())
                client->disconnect();
        }
    }

    void FingerManager::FingerAdded(int n)
    {
        ++nFingers;

        FingerData& data = fingers[n];
        data.addTime = TUIO::TuioTime::getSessionTime();

        OSCMessenger::Instance().Add(n, data);
    }

    void FingerManager::FingerUpdated(int n)
    {
        OSCMessenger::Instance().Update(n, fingers[n]);
    }

    void FingerManager::FingerRemoved(int n)
    {
        --nFingers;
        OSCMessenger::Instance().Remove(n);
    }

    void FingerManager::addTuioObject(TUIO::TuioObject *tobj)
    {
        //std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
    }

    void FingerManager::updateTuioObject(TUIO::TuioObject *tobj)
    {
        //std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() 
        //    << " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
    }

    void FingerManager::removeTuioObject(TUIO::TuioObject *tobj)
    {
        //std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
    }

    void FingerManager::addTuioCursor(TUIO::TuioCursor *tcur)
    {
        //std::cout << "client: add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;

        FingerData data = MakeData(tcur);

        if(isFingerOK != 0 && !isFingerOK(data, isFingerOKData))
            return;

        int slotIndex = 0;
        bool slotFound = false;
        for(size_t i = 0; i < fingers.size(); ++i) {
            if(fingers[i].finger == 0) {
                fingers[i] = data;
                slotIndex = i;
                slotFound = true;
                break;
            }
        }

        if(!slotFound) {
            slotIndex = fingers.size();
            fingers.push_back(data);
        }

        FingerAdded(slotIndex);

        //DebugPrint();
    }

    void FingerManager::updateTuioCursor(TUIO::TuioCursor *tcur)
    {
        //std::cout << "client: set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
            //<< " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;

        for(size_t i = 0; i < fingers.size(); ++i) {
            FingerData& data = fingers[i];
            if(data.finger == 0)
                continue;

            if(data.finger->getSessionID() == tcur->getSessionID()) {
                data.Update(tcur);
                FingerUpdated(i);
                break;
            }
        }

        //DebugPrint();
    }

    void FingerManager::removeTuioCursor(TUIO::TuioCursor *tcur)
    {
        //std::cout << "client: del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;

        for(size_t i = 0; i < fingers.size(); ++i) {
            FingerData& data = fingers[i];
            if(data.finger == 0)
                continue;

            if(data.finger->getSessionID() == tcur->getSessionID()) {
                data.finger = 0;
                data.removeTime = TUIO::TuioTime::getSessionTime();
                FingerRemoved(i);
                break;
            }
        }

        //DebugPrint();
    }

    void  FingerManager::refresh(TUIO::TuioTime bundleTime) {
        //std::cout << bundleTime.getTotalMilliseconds() << std::endl;
    }

    void FingerManager::Update(float TimeStep)
    {
        for(size_t i = 0; i < fingers.size(); ++i) {
            FingerData& data = fingers[i];
            if(data.finger == 0)
                continue;

            data.UpdateSmooth();
        }
    }

}