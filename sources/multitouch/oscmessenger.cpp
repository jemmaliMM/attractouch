#include "multitouch/oscmessenger.h"

namespace AT {

    OSCMessenger::OSCMessenger()
    {
        
    }

    OSCMessenger::~OSCMessenger()
    {
        
    }

    OSCMessenger& OSCMessenger::Instance()
    {
        static OSCMessenger instance;
        return instance;
    }

    void OSCMessenger::Start(int PortOSC)
    {
        if(oscSocket == 0) {
            oscSocket = new UdpTransmitSocket(IpEndpointName("127.0.0.1", PortOSC));
            if(oscSocket == 0)
                throw new std::exception("Couldn't create OSC socket");
        }
    }

    void OSCMessenger::Stop()
    {
        if(oscSocket != 0) {
            delete oscSocket;
            oscSocket = 0;
        }
    }

    void OSCMessenger::Add(int n, FingerData FingerData)
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/add") << n << FingerData.x << FingerData.y << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::Update(int n, FingerData FingerData)
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/update") << n << FingerData.x << FingerData.y << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::Remove(int n)
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/remove") << n << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::NotTonight()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/not-tonight") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::LauncherRate(float ParticlesPerSec)
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/rate") << (1000.0f / ParticlesPerSec) << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::LauncherActivated(int Particles)
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/activated") << Particles << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::ParticleLost()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/lost") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::ParticleCollided()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/collided") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::ParticleAttracted()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/fingered") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::ParticleReceived()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/received") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::Intro()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/intro") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::Menu()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/menu") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::ChangeLevel()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/changelevel") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::FirstLevel()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/fist") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::Credits()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/credits") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }

    void OSCMessenger::End()
    {
        if(oscSocket == 0)
            return;

        char buffer[OSC_BUFFER_SIZE];
        osc::OutboundPacketStream p(buffer, OSC_BUFFER_SIZE);

        p << osc::BeginBundleImmediate
            << osc::BeginMessage("/at/end") << osc::EndMessage
          << osc::EndBundle;

        oscSocket->Send(p.Data(), p.Size());
    }
}