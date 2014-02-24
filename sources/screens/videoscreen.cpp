#include "screens/videoscreen.h"

namespace AT {

    bool VideoScreen::init = false;

    VideoScreen::VideoScreen(ScreenManager& ScreenManager, const std::string& VideoFile)
        :Screen(ScreenManager), loaded(false), videoFile(VideoFile), videoState(VideoState::Stopped), formatContext(NULL), codecContext(NULL), frame(NULL), frameRGB(NULL), width(0), height(0), videoScale(1.0f), videoAlpha(1.0f), frameRate(1.0), frameCount(0), frameNumber(0), updateAccum(0.0), bufferFrame(NULL), scaleContext(NULL), texture(0), textureInit(false)
    {
        if(!init) {
            av_register_all();
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    VideoScreen::~VideoScreen()
    {
        Destroy();
        glDeleteTextures(1, &texture);
    }

    bool VideoScreen::DecodeFrame()
    {
        AVPacket packet;
        int frameFinished = 0;

        if(av_read_frame(formatContext, &packet) >= 0) {
            // Is this a packet from the video stream?
            if(packet.stream_index == videoStream) {
                // Decode video frame
                avcodec_decode_video(codecContext, frame, &frameFinished, packet.data, packet.size);
                return frameFinished != 0;
            }

            // Free the packet that was allocated by av_read_frame
            av_free_packet(&packet);
        }
        return false;
    }

    void VideoScreen::Load(sf::RenderTarget& Target)
    {
        if(av_open_input_file(&formatContext, videoFile.c_str(), NULL, 0, NULL) != 0) {
            std::cout << "File '" << videoFile << "' not found!" << std::endl;
            return;
        }

        if(av_find_stream_info(formatContext) < 0) {
            std::cout << "No stream information in '" << videoFile << "'" << std::endl;
            Destroy();
            return;
        }

        dump_format(formatContext, 0, videoFile.c_str(), 0);

        videoStream = -1;
        for(unsigned int i = 0; i < formatContext->nb_streams; ++i) {
            if(formatContext->streams[i]->codec->codec_type == CODEC_TYPE_VIDEO) {
                videoStream = (int)i;
                break;
            }
        }
        if(videoStream == -1) {
            std::cout << "No video stream found in '" << videoFile << "'";
            Destroy();
            return;
        }

        std::cout << "Video stream: " << videoStream << std::endl;

        codecContext = formatContext->streams[videoStream]->codec;


        AVCodec *codec = avcodec_find_decoder(codecContext->codec_id);
        if(codec == NULL) {
            std::cout << "Codec '" << codecContext->codec_name << "' not supported" << std::endl;
            Destroy();
            return;
        }

        if(avcodec_open(codecContext, codec) < 0) {
            std::cout << "Error opening codec '" << codecContext->codec_name << "'" << std::endl;
            Destroy();
            return;
        }

        duration = formatContext->duration / (double)AV_TIME_BASE;
        frameRate = av_q2d(formatContext->streams[videoStream]->r_frame_rate);
        updateTimeStep = 1.0 / frameRate;
        frameCount = int(duration * frameRate);

        frame = avcodec_alloc_frame();
        if(frame == NULL) {
            std::cout << "Can't allocate frame" << std::endl;
            Destroy();
            return;
        }

        frameRGB = avcodec_alloc_frame();
        if(frameRGB == NULL) {
            std::cout << "Can't allocate frame for RGB" << std::endl;
            Destroy();
            return;
        }

        
        width = codecContext->width;
        height = codecContext->height;

        PixelFormat desiredFormat = PIX_FMT_RGBA;

        int numBytes = avpicture_get_size(desiredFormat, width, height);
        bufferFrame = new uint8_t[numBytes];

        avpicture_fill((AVPicture*)(frameRGB), bufferFrame, desiredFormat, width, height);

        scaleContext = sws_getContext(width, height, codecContext->pix_fmt, width, height, desiredFormat, SWS_BICUBIC, NULL, NULL, NULL);
        if(scaleContext == NULL) {
            std::cout << "Couldn't create the scale context" << std::endl;
            Destroy();
            return;
        }

        std::cout << "Loaded '" << videoFile << "' : " << width << "x" << height << ", " << frameCount << " frames, frame rate " << frameRate << std::endl;
    }

    void VideoScreen::Destroy()
    {
        // Destroy buffer
        delete[] bufferFrame;
        bufferFrame = NULL;

        // Destroy frames
        av_free(frame);
        av_free(frameRGB);

        // Destroy codec context
        avcodec_close(codecContext);
        codecContext = NULL;

        // Close video file
        av_close_input_file(formatContext);
        formatContext = NULL;
    }

    bool VideoScreen::Process(sf::Event& Event)
    {
        return false;
    }

    bool VideoScreen::Update(float TimeStep)
    {
        Screen::Update(TimeStep);

        updateAccum += TimeStep;
        if(updateAccum >= updateTimeStep) {
            updateAccum -= updateTimeStep;
        } else {
            return false;
        }

        if(videoState == VideoState::Playing) {
            if(DecodeFrame()) {
                int result = sws_scale(scaleContext, frame->data, frame->linesize, 0, height, frameRGB->data, frameRGB->linesize);
                //std::cout << "Frame " << frameNumber << "/" << frameCount << std::endl;
                ++frameNumber;

                glBindTexture(GL_TEXTURE_2D, texture);
                if(!textureInit) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferFrame);
                    textureInit = true;
                } else {
                    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bufferFrame);
                }
            }
        }
        if(frameNumber >= frameCount && videoState == VideoState::Playing) {
            std::cout << "STOP!!!" << std::endl;
            SetVideoState(VideoState::Stopped);
        }
        return false;
    }

    void VideoScreen::Draw(sf::RenderTarget& Target)
    {
        if(!textureInit)
            return;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor4f(1.0f, 1.0f, 1.0f, videoAlpha);
        glPushMatrix();
        glScalef(videoScale, videoScale, 1.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(width, 0.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(width, height);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(0.0f, height);
        glEnd();
        glPopMatrix();
    }

    void VideoScreen::Rewind()
    {
        if(formatContext != NULL)
            av_seek_frame(formatContext, videoStream, 0, AVSEEK_FLAG_BYTE);
        frameNumber = 0;
    }

    void VideoScreen::SetVideoState(VideoState::Value NewState)
    {
        VideoState::Value oldState = videoState;
        videoState = NewState;
        OnVideoStateChange(oldState);
    }
}