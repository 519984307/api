#include "rtsp2rtmp.h"


using namespace std;


// ref:https://blog.csdn.net/yao_hou/article/details/103267569
// ref:https://www.cnblogs.com/wanggang123/p/7222215.html
Rtsp2Rtmp::Rtsp2Rtmp(const Rtsp2RtmpReq_t& req, int rtmpMode)
    : _isWorking(false),
      _isInited(false),
      _playCount(0),
      _node(req.node),
      _inputUrl(req.rtspUrl),
      _outUrl(req.rtmpUrl),
      _rtmpMode(rtmpMode)
{
    init();
}

Rtsp2Rtmp::~Rtsp2Rtmp()
{
    unInit();
}

void Rtsp2Rtmp::init()
{

    av_log_set_level(AV_LOG_ERROR);
    m_videoIndex = -1;
    qDebug() << "rtsp url: " << _inputUrl ;
    qDebug() << "rtmp url: " << _outUrl ;

    int ret = 0;
    if (_rtmpMode)
    {
        qDebug() << "open input url by tcp" ;
        ret = openInputByTcp(_inputUrl.toStdString());
    }
    else
    {
        qDebug() << "open input url by udp" ;
        ret = openInputByUdp(_inputUrl.toStdString());
    }

    if (ret >= 0)
    {
        _isInited = true;
        ret = openOutput(_outUrl.toStdString());
        _isWorking = true;
    }

    if (ret < 0)
    {
        //?????????????
        _isWorking = false;
        _playCount = 0;
    }
}

void Rtsp2Rtmp::unInit()
{
    _isWorking = false;
    if (_isInited)
    {
        if (_outputContext)
        {
            qDebug() << "close output url" ;
            avformat_close_input(&_outputContext);
        }
        if (_inputContextTcp)
        {
            qDebug() << "close tcp input url" ;
            avformat_close_input(&_inputContextTcp);
        }

        if (_inputContextUdp)
        {
            qDebug() << "close udp input url" ;
            avformat_close_input(&_inputContextUdp);
        }
        _isInited = false;
    }
}

int Rtsp2Rtmp::setPlayCount(bool isPlay)
{
    if (isPlay)
    {
        _playCount++;
        qDebug() << "after play, the play count: " << _playCount << ", the node is " << _node ;
    }
    else
    {
        if (_playCount > 0)
        {
            _playCount--;
            qDebug() << "after play done, the play count: " << _playCount << ", the node is " << _node ;
        }
    }

    return _playCount;
}

bool Rtsp2Rtmp::getRtsp2RtmpFlag()
{
    return _isWorking;
}

void Rtsp2Rtmp::setRtsp2RtmpFlag(bool flag)
{
    qDebug() << "set the rtsp2rtmp flag to " << flag << ", the node is " << _node ;
    _isWorking = flag;
}

void Rtsp2Rtmp::start()
{
    do
    {
        int64_t count = 0;
        while (_isWorking)
        {
            shared_ptr<AVPacket> packet = nullptr;

            if (_rtmpMode)
            {
                //LOG(kDebug) << "read packet by tcp" ;
                packet = readPacketFromSourceByTcp();
            }
            else
            {
                //LOG(kDebug) << "read packet by udp" ;
                packet = readPacketFromSourceByUdp();
            }

            if (packet)
            {
                int ret = writePacket(packet);

                //  this_thread::sleep_for(std::chrono::seconds(5000));
                if (ret >= 0)
                {
                    count++;
                    if ((count % 10000) == 0)
                        qDebug() << " WritePacket Success! node: " << _node << endl;
                }
                else if (ret < 0)
                {
                    // qDebug() << "WritePacket failed! ret: " << ret << ", node: " << _node << endl;
                }
            }
            else
            {
                this_thread::sleep_for(chrono::milliseconds(1));
            }
            if (parentThead->isInterruptionRequested())
            {
                break;
            }
        }
        unInit();
        qDebug() << "shut down rtsp2rtmp, node: " << _node << endl;


    }
    while (0);
}

int Rtsp2Rtmp::openInputByTcp(const string& inputUrl)
{
    _inputContextTcp = avformat_alloc_context();
    _inputContextTcp->flags = _inputContextTcp->flags & AVFMT_FLAG_NOBUFFER;
    _inputContextTcp->probe_score = 50 * 1024;
    _inputContextTcp->max_delay = 5 * AV_TIME_BASE;
    AVDictionary* options = nullptr;
    av_dict_set(&options, "rtsp_transport", "tcp", 0);
    av_dict_set(&options, "stimeout", "6", 0);
    av_dict_set(&options, "framerate", "15", 0);
    av_dict_set(&options, "buffer_size", "1024000", 0);
    _inputContextTcp->flags |= AVFMT_FLAG_NOBUFFER;
    int ret = avformat_open_input(&_inputContextTcp, inputUrl.c_str(), nullptr, &options);
    if (ret < 0)
    {
        qDebug() << "open input url " << QString::fromStdString(inputUrl) << " failed" ;
        return  ret;
    }

    ret = avformat_find_stream_info(_inputContextTcp, nullptr);
    if (ret < 0)
    {
        qDebug() << "find input url stream information failed" ;
    }
    else
    {
        qDebug() << "open input url " <<  QString::fromStdString(inputUrl) << " success" ;
    }

    for (unsigned int i = 0; i < _inputContextTcp->nb_streams; i++)
    {
        if (_inputContextTcp->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            m_videoIndex = i;
            break;
        }
    }

    return ret;
}

int Rtsp2Rtmp::openInputByUdp(const string& inputUrl)
{
    _inputContextUdp = avformat_alloc_context();
    AVDictionary* options = nullptr;
    av_dict_set(&options, "rtsp_transport", "udp", 0);
    av_dict_set(&options, "stimeout", "5000000", 0);

    int ret = avformat_open_input(&_inputContextUdp, inputUrl.c_str(), nullptr, &options);
    if (ret < 0)
    {
        qDebug() << "open input url " <<  QString::fromStdString(inputUrl) << " failed" ;
        return  ret;
    }

    ret = avformat_find_stream_info(_inputContextUdp, nullptr);
    if (ret < 0)
    {
        qDebug() << "find input url stream information failed" ;
    }
    else
    {
        qDebug() << "open input url " <<  QString::fromStdString(inputUrl) << " success" ;
    }

    return ret;
}

shared_ptr<AVPacket> Rtsp2Rtmp::readPacketFromSourceByTcp()
{
    shared_ptr<AVPacket> packet(
        static_cast<AVPacket*>(av_malloc(sizeof(AVPacket))),
    [&](AVPacket * p) { av_packet_free(&p); av_freep(&p); }
    );

    av_init_packet(packet.get());

    int ret = av_read_frame(_inputContextTcp, packet.get());
    if (ret >= 0)
    {
        return packet;

    }
    else
    {
        return nullptr;
    }
}

shared_ptr<AVPacket> Rtsp2Rtmp::readPacketFromSourceByUdp()
{
    shared_ptr<AVPacket> packet(
        static_cast<AVPacket*>(av_malloc(sizeof(AVPacket))),
    [&](AVPacket * p) { av_packet_free(&p); av_freep(&p); }
    );

    av_init_packet(packet.get());

    int ret = av_read_frame(_inputContextUdp, packet.get());
    if (ret >= 0)
    {
        return packet;
    }
    else
    {
        return nullptr;
    }
}

void Rtsp2Rtmp::av_packet_rescale_ts(AVPacket* pkt, AVRational src_tb, AVRational dst_tb)
{
    if (pkt->pts != AV_NOPTS_VALUE)
        pkt->pts = av_rescale_q(pkt->pts, src_tb, dst_tb);

    if (pkt->dts != AV_NOPTS_VALUE)
        pkt->dts = av_rescale_q(pkt->dts, src_tb, dst_tb);

    if (pkt->duration > 0)
        pkt->duration = av_rescale_q(pkt->duration, src_tb, dst_tb);
}

int Rtsp2Rtmp::writePacket(shared_ptr<AVPacket> packet)
{
    auto outputStream = _outputContext->streams[packet->stream_index];

    if (_inputContextTcp)
    {
        auto inputStream = _inputContextTcp->streams[packet->stream_index];

        av_packet_rescale_ts(packet.get(), inputStream->time_base, outputStream->time_base);
    }
    else if (_inputContextUdp)
    {
        auto inputStream = _inputContextUdp->streams[packet->stream_index];

        av_packet_rescale_ts(packet.get(), inputStream->time_base, outputStream->time_base);
    }

    return av_interleaved_write_frame(_outputContext, packet.get());
}

int Rtsp2Rtmp::openOutput(const string& outUrl)
{
    int ret = 0;

    do
    {
        ret = avformat_alloc_output_context2(&_outputContext, nullptr, "flv", outUrl.c_str());
        if (ret < 0)
        {
            qDebug() << "open output context failed" ;
            goto Error;
        }

        _outputContext->flags = _inputContextTcp->flags & AVFMT_FLAG_NOBUFFER;
        _outputContext->probe_score = 50 * 1024;
        _outputContext->max_delay = 5 * AV_TIME_BASE;
        ret = avio_open2(&_outputContext->pb, outUrl.c_str(), AVIO_FLAG_READ_WRITE, nullptr, nullptr);
        if (ret < 0)
        {
            qDebug() << "open avio failed" ;
            goto Error;
        }

        if (_inputContextTcp)
        {
            for (int i = 0; i < _inputContextTcp->nb_streams; i++)
            {
                AVStream* stream = avformat_new_stream(_outputContext, _inputContextTcp->streams[i]->codec->codec);
                ret = avcodec_copy_context(stream->codec, _inputContextTcp->streams[i]->codec);
                if (ret < 0)
                {
                    qDebug() << "copy coddec context failed" ;
                    goto Error;
                }
            }
        }
        else if (_inputContextUdp)
        {
            for (int i = 0; i < _inputContextUdp->nb_streams; i++)
            {

                AVStream* stream = avformat_new_stream(_outputContext, _inputContextUdp->streams[i]->codec->codec);
                ret = avcodec_copy_context(stream->codec, _inputContextUdp->streams[i]->codec);
                if (ret < 0)
                {
                    qDebug() << "copy coddec context failed" ;
                    goto Error;
                }
            }
        }

        ret = avformat_write_header(_outputContext, nullptr);
        if (ret < 0)
        {
            qDebug() << "format write header failed" ;
            goto Error;
        }

        qDebug() << "open output url " <<  QString::fromStdString(outUrl) << " success" ;

        return ret;

    }
    while (0);

Error:
    if (_outputContext)
    {
        for (int i = 0; i < _outputContext->nb_streams; i++)
        {
            avcodec_close(_outputContext->streams[i]->codec);
        }

        avformat_close_input(&_outputContext);
    }

    return ret;
}


//int main(int argc, const char** argv)
//{
//    if (argc < 3)
//    {
//        std::cout << "Usage ./rtsp2rtmp [rtsp:url] [rtmp:url]" ;
//        return -1;
//    }

//    std::string rtsp_url(argv[1]);
//    std::string rtmp_url(argv[2]);

//    std::cout << "rtsp url " << rtsp_url ;
//    std::cout << "rtmp url " << rtmp_url ;

//    Rtsp2RtmpReq_t req;
//    req.node = "123";
//    //req.rtspUrl = "rtsp://10.40.27.37:554/047COUNTFX26_1/real?";
//    //req.rtmpUrl = "rtmp://10.40.27.158:1935/rock/mystream";
//    req.rtspUrl = rtsp_url;
//    req.rtmpUrl = rtmp_url;
//    Rtsp2Rtmp r2r(req, 1);
//    r2r.start();

//    return 0;
//}
