#ifndef _VIDEO_SCREEN_H
#define _VIDEO_SCREEN_H

#include <sstream>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
}

#include "utils/helper.h"
#include "screens/screen.h"
#include "screens/screenmanager.h"
#include "screens/loadingscreen.h"

namespace AT {

    namespace VideoState {
        enum {
            Stopped,
            Paused,
            Playing
        };
        typedef unsigned long Value;
    }

    class VideoScreen : public Screen
    {
    protected:
        static bool init;
        bool loaded;
        std::string videoFile;

        VideoState::Value videoState;

        AVFormatContext *formatContext;
        AVCodecContext *codecContext;
        AVFrame *frame;
        AVFrame *frameRGB;
        int videoStream;
        int width, height;
        float videoScale;
        float videoAlpha;

        SwsContext *scaleContext;

        double duration;
        double frameRate;
        int frameCount;
        int frameNumber;

        double updateAccum;
        double updateTimeStep;

        uint8_t *bufferFrame;

        GLuint texture;
        bool textureInit;

        sf::Image image;
        sf::Sprite sprite;

        bool DecodeFrame();
        void Destroy();
    public:
        VideoScreen(ScreenManager& ScreenManager, const std::string& VideoFile);
        virtual ~VideoScreen();

        virtual void Load(sf::RenderTarget& Target);

        virtual bool Process(sf::Event& Event);
        virtual bool Update(float TimeStep);

        virtual void Draw(sf::RenderTarget& Target);

        void Rewind();

        void SetVideoState(VideoState::Value VideoState);
        virtual void OnVideoStateChange(VideoState::Value OldState) {}
    };

}

#endif