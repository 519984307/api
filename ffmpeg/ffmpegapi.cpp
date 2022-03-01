#include "ffmpegapi.h"

void initFFmpegLib()
{
    av_register_all();
    avcodec_register_all();

    avformat_network_init();

}
