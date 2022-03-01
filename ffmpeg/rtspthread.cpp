#include "rtspthread.h"

RtspThread::RtspThread(QObject* parent) : QThread(parent)
{
    m_isStart = false;


}

RtspThread::~RtspThread()
{
    qDebug() << "~RtspThread()";
}

void RtspThread::run()
{
    m_videoStreamIndex = -1;
    // 初始化FFmpeg
    //av_register_all();//注册库中所有可用的文件格式和解码器
    //avformat_network_init();//初始化网络流格式,使用RTSP网络流时必须先执行

    //申请一个AVFormatContext结构的内存,并进行简单初始化
    m_pAVFormatContext = avformat_alloc_context();
    m_pAVFrame = av_frame_alloc();
    m_pAVFrameYUV = av_frame_alloc();
    m_isSuspended = false;
    m_pAVPacket = {};

    AVDictionary* format_opts = nullptr;
    av_dict_set(&format_opts, "rtsp_transport", "tcp", 0); //设置推流的方式
    av_dict_set(&format_opts, "stimeout", "3000", 0); //设置超时3秒
    av_dict_set(&format_opts, "buffer_size", "5000", 0);
    //打开视频流
    int result = avformat_open_input(&m_pAVFormatContext, m_rtspUrl.toLocal8Bit().data(), NULL, &format_opts);
    if (result < 0)
    {
        qDebug() << QString("打开视频流失败 channel %1").arg(m_channel);
        return;
    }
    //获取视频流信息
    result = avformat_find_stream_info(m_pAVFormatContext, nullptr);
    if (result < 0)
    {
        qDebug() << "获取视频流信息失败";
        return;
    }
    //获取视频流索引
    m_videoStreamIndex = -1;
    for (uint i = 0; i < m_pAVFormatContext->nb_streams; i++)
    {
        if (m_pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            m_videoStreamIndex = i;
            break;
        }
    }
    if (m_videoStreamIndex == -1)
    {
        qDebug() << "获取视频流索引失败";
        return;
    }

    //获取视频流的分辨率大小
    m_pAVCodecContext = m_pAVFormatContext->streams[m_videoStreamIndex]->codec;
    m_videoWidth = m_pAVCodecContext->width;
    m_videoHeight = m_pAVCodecContext->height;

    qDebug() << "kuan: " << m_videoWidth << "; gao: " << m_videoHeight;
    if (m_videoWidth == 0 || m_videoHeight == 0)
    {
        qDebug() << "加载视频流失败。";
        return;
    }


    avpicture_alloc(&pAVPicture, AV_PIX_FMT_RGB24, m_videoWidth, m_videoHeight);

    AVCodec* pAVCodec = new AVCodec();

    //获取视频流解码器
    pAVCodec = avcodec_find_decoder(m_pAVCodecContext->codec_id);
#if defined (Q_OS_WIN32)
    pSwsContext = sws_getContext(m_videoWidth, m_videoHeight, AV_PIX_FMT_YUV420P, m_videoWidth, m_videoHeight, AV_PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);
#endif
    //打开对应解码器
    result = avcodec_open2(m_pAVCodecContext, pAVCodec, nullptr);
    if (result < 0)
    {
        qDebug() << "打开解码器失败";
        return;
    }
    qDebug() << "初始化视频流成功";

    int frameFinished = 0;
    m_checker.start();
    while (true)
    {
        m_isStart = true;
        if (av_read_frame(m_pAVFormatContext, &m_pAVPacket) >= 0)
        {
            if (m_pAVPacket.stream_index == m_videoStreamIndex)
            {



                //qDebug() << "开始解码了。。。。";
                avcodec_decode_video2(m_pAVCodecContext, m_pAVFrame, &frameFinished, &m_pAVPacket);

                if (frameFinished)
                {

                    sws_scale(pSwsContext, (const uint8_t* const*)m_pAVFrame->data, m_pAVFrame->linesize, 0, m_videoHeight, pAVPicture.data, pAVPicture.linesize);
                    //发送获取一帧图像信号
                    uchar* data = pAVPicture.data[0];
                    int sz = avpicture_get_size(AV_PIX_FMT_RGB24, m_videoWidth, m_videoHeight);
                    saveFrame(data, m_videoWidth, m_videoHeight, sz);
                    QDateTime d = QDateTime::currentDateTime();

                    emit onSaveFrame(data, m_videoWidth, m_videoHeight, sz, d, this);

                }

            }

            av_free_packet(&m_pAVPacket); //释放资源,否则内存会一直上升
            QThread::msleep(1);
            if (isInterruptionRequested())
            {
                return;
            }


        }
    }


}

QString RtspThread::rtspUrl() const
{
    return m_rtspUrl;
}

void RtspThread::setRtspUrl(const QString& rtspUrl)
{
    m_rtspUrl = rtspUrl;
}

QString RtspThread::name() const
{
    return m_name;
}

void RtspThread::setName(const QString& name)
{
    m_name = name;
}

void RtspThread::saveFrame(uchar* data, int width, int height, int sz)
{

}

QString RtspThread::channel() const
{
    return m_channel;
}

void RtspThread::setChannel(const QString& channel)
{
    m_channel = channel;
}

QString RtspThread::captureTime() const
{
    return m_captureTime;
}

void RtspThread::setCaptureTime(const QString& captureTime)
{
    m_captureTime = captureTime;
}

int RtspThread::randomIndex() const
{
    return m_randomIndex;
}

void RtspThread::setRandomIndex(int randomIndex)
{
    m_randomIndex = randomIndex;
}

QString RtspThread::devId() const
{
    return m_devId;
}

void RtspThread::setDevId(const QString& devId)
{
    m_devId = devId;
}

bool RtspThread::isStart() const
{
    return m_isStart;
}

void RtspThread::setIsStart(bool isStart)
{
    m_isStart = isStart;
}


