#ifndef RTSP2RTMPTHREAD_H
#define RTSP2RTMPTHREAD_H

#include <QObject>
#include <QThread>
#include "ffmpegapi.h"

class Rtsp2RtmpThread : public QThread
{
    Q_OBJECT
public:
    explicit Rtsp2RtmpThread(QObject* parent = nullptr);
    ~Rtsp2RtmpThread();
    QString rtspUrl() const;
    void setRtspUrl(const QString& rtspUrl);

    QString rtmpUrl() const;
    void setRtmpUrl(const QString& rtmpUrl);
    QString nodeName() const;
    void setNodeName(const QString& nodeName);

protected:
    void run();
signals:

private:
    QString m_rtspUrl;
    QString m_rtmpUrl;
    QString m_nodeName;

};

#endif // RTSP2RTMPTHREAD_H
