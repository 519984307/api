#ifndef RTSPTHREAD_H
#define RTSPTHREAD_H

#include <QObject>
#include <QThread>
#include "ffmpegapi.h"
#include <QMutex>
#include <QImage>
#include <QElapsedTimer>
#include <QDateTime>

class RtspThread : public QThread
{
    Q_OBJECT
public:
    explicit RtspThread(QObject* parent = nullptr);
    ~RtspThread();
    void run();
    QString rtspUrl() const;
    void setRtspUrl(const QString& rtspUrl);

    QString name() const;
    void setName(const QString& name);

    virtual void saveFrame(uchar* data, int width, int height, int sz);
    QString channel() const;
    void setChannel(const QString& channel);

    QString captureTime() const;
    void setCaptureTime(const QString& captureTime);

    int randomIndex() const;
    void setRandomIndex(int randomIndex);

    QString devId() const;
    void setDevId(const QString& devId);

    bool isStart() const;
    void setIsStart(bool isStart);

signals:
    void onSaveFrame(uchar* data, int width, int height, int sz, QDateTime curTime, RtspThread* thd);
private:
    QString m_rtspUrl;
    QString m_name;
    AVFormatContext* m_pAVFormatContext;
    AVCodecContext* m_pAVCodecContext;
    AVFrame* m_pAVFrame;
    AVFrame* m_pAVFrameYUV;
    AVPacket m_pAVPacket;
#if defined (Q_OS_WIN32)
    AVPicture  pAVPicture;
    SwsContext* pSwsContext;
#endif


    bool m_pause = false;
    int m_videoWidth;
    int m_videoHeight;
    int m_videoStreamIndex;
    bool m_isSuspended;
    QElapsedTimer m_checker;
    QString m_currentTime;
    QString m_channel;
    QString m_captureTime;
    int m_randomIndex;
    QString m_devId;
    bool m_isStart;

};

#endif // RTSPTHREAD_H
