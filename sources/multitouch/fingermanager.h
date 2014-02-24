#ifndef _FINGER_MANAGER_H
#define _FINGER_MANAGER_H

#include <vector>

#include "TuioListener.h"
#include "TuioClient.h"

namespace AT {

    typedef TUIO::TuioCursor Finger;
    struct FingerData
    {
        Finger *finger;
        float x, y;
        float smoothX, smoothY;

        TUIO::TuioTime addTime;
        TUIO::TuioTime lastUpdateTime;
        TUIO::TuioTime removeTime;

        void Update(Finger *finger);
        void UpdateSmooth();
        float ScreenX(int Width) const;
        float ScreenY(int Height) const;
        float ScreenSmoothX(int Width) const;
        float ScreenSmoothY(int Height) const;
    };
    typedef std::vector<FingerData> Fingers;

    class FingerManager : TUIO::TuioListener
    {
    public:
        typedef bool (*IsFingerOKCallback)(const FingerData& FingerData, void *Data);
    private:
        TUIO::TuioClient *client;

        int nFingers;
        Fingers fingers;

        FingerManager();
        virtual ~FingerManager();

        IsFingerOKCallback isFingerOK;
        void *isFingerOKData;

        void FingerAdded(int n);
        void FingerUpdated(int n);
        void FingerRemoved(int n);

        /* TuioListener interface */
        void addTuioObject(TUIO::TuioObject *tobj);
        void updateTuioObject(TUIO::TuioObject *tobj);
        void removeTuioObject(TUIO::TuioObject *tobj);

        void addTuioCursor(TUIO::TuioCursor *tcur);
        void updateTuioCursor(TUIO::TuioCursor *tcur);
        void removeTuioCursor(TUIO::TuioCursor *tcur);

        void refresh(TUIO::TuioTime bundleTime);
    public:
        static FingerManager& Instance();
        static FingerData MakeData(Finger *Finger);

        void Start(int PortTUIO);
        void Stop();

        void SetIsFingerOK(IsFingerOKCallback IsFingerOK, void *Data = NULL)
        { isFingerOK = IsFingerOK; isFingerOKData = Data; }

        const Fingers& GetFingers() const
        { return fingers; }
        int NFingers() const
        { return nFingers; }

        void Update(float TimeStep);
    };
}

#endif
