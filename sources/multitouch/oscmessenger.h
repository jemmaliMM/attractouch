#ifndef _OSC_MESSENGER_H
#define _OSC_MESSENGER_H

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "TuioCursor.h"

#define OSC_BUFFER_SIZE 1024

#include "multitouch/fingermanager.h"

namespace AT {

    class OSCMessenger
    {
    private:
        UdpTransmitSocket *oscSocket;

        OSCMessenger();
        ~OSCMessenger();
    public:
        static OSCMessenger& Instance();

        void Start(int PortOSC);
        void Stop();

        void Add(int n, FingerData FingerData); // message: at/add n x y
        void Update(int n, FingerData FingerData); // message: /at/update n x y
        void Remove(int n); // message: at/remove n

        void NotTonight(); // refuse finger, message: /at/not-tonight

        void LauncherRate(float ParticlesPerSec); // message: /at/rate period (in ms)
        void LauncherActivated(int Particles); // message: /at/activated n

        void ParticleLost(); // message: /at/lost
        void ParticleCollided(); // message: /at/collided
        void ParticleAttracted(); // message: /at/fingered
        void ParticleReceived(); // message: /at/received

        void Intro(); // message: /at/intro
        void Menu(); // message: /at/menu
        void FirstLevel(); // message: /at/fist
        void ChangeLevel(); // message: /at/changelevel
        void Credits(); // message: /at/credits
        void End(); // message: /at/end
    };
}

#endif
