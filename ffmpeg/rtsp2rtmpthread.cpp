#include "rtsp2rtmpthread.h"

Rtsp2RtmpThread::Rtsp2RtmpThread(QObject* parent) : QThread(parent)
{

}

Rtsp2RtmpThread::~Rtsp2RtmpThread()
{
    qDebug() << "~Rtsp2RtmpThread()";

}

QString Rtsp2RtmpThread::rtspUrl() const
{
    return m_rtspUrl;
}

void Rtsp2RtmpThread::setRtspUrl(const QString& rtspUrl)
{
    m_rtspUrl = rtspUrl;
}

QString Rtsp2RtmpThread::rtmpUrl() const
{
    return m_rtmpUrl;
}

void Rtsp2RtmpThread::setRtmpUrl(const QString& rtmpUrl)
{
    m_rtmpUrl = rtmpUrl;
}

void Rtsp2RtmpThread::run()
{
    Rtsp2RtmpReq_t req;
    req.node = m_nodeName;
    req.rtspUrl = m_rtspUrl;
    req.rtmpUrl = m_rtmpUrl;
    Rtsp2Rtmp* r2r = new Rtsp2Rtmp(req, 1);
    r2r->parentThead = this;
    r2r->start();

}

QString Rtsp2RtmpThread::nodeName() const
{
    return m_nodeName;
}

void Rtsp2RtmpThread::setNodeName(const QString& nodeName)
{
    m_nodeName = nodeName;
}
