
#pragma once

#include <thread>
#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <atomic>
#include <QDebug>




#include "ffmpegapi.h"

struct Rtsp2RtmpReq_t
{
    QString channelName;
    QString node;
    QString streamType;
    QString rtspUrl;
    QString rtmpUrl;
};

class Rtsp2Rtmp
{

public:
    Rtsp2Rtmp(const Rtsp2RtmpReq_t& req, int rtmpMode);
    ~Rtsp2Rtmp();
    void start();
    int setPlayCount(bool isPlay);
    bool getRtsp2RtmpFlag();
    void setRtsp2RtmpFlag(bool flag);
    QThread* parentThead;
private:
    void init();
    void unInit();

    int openInputByTcp(const std::string& inputUrl);
    int openInputByUdp(const std::string& inputUrl);
    int openOutput(const std::string& outUrl);

    std::shared_ptr<AVPacket> readPacketFromSourceByTcp();
    std::shared_ptr<AVPacket> readPacketFromSourceByUdp();
    int writePacket(std::shared_ptr<AVPacket> packet);

    void av_packet_rescale_ts(AVPacket* pkt, AVRational src_tb, AVRational dst_tb);

public:


private:
    AVFormatContext* _inputContextTcp = nullptr;
    AVFormatContext* _inputContextUdp = nullptr;
    AVFormatContext* _outputContext = nullptr;

    std::atomic<bool> _isWorking;
    std::atomic<bool> _isInited;
    std::atomic<int> _playCount;

    QString _node;
    QString _inputUrl;
    QString _outUrl;
    int _rtmpMode;
    int m_videoIndex;
};
