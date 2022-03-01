#include "removenoizeprocoperator.h"

RemoveNoizeProcOperator::RemoveNoizeProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "快速去噪";

}

void RemoveNoizeProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    fastNlMeansDenoisingColored(src, dest, 15, 10, 7, 21);
}
