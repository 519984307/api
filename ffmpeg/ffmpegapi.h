#ifndef FFMPEGAPI_H
#define FFMPEGAPI_H

#include <QObject>
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/frame.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil\time.h"
}
#include "rtsp2rtmpthread.h"
#include "rtsp2rtmp.h"
///初始化ffpeg库
void initFFmpegLib();

#endif // FFMPEGAPI_H
