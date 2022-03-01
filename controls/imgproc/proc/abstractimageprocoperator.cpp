#include "abstractimageprocoperator.h"

AbstractImageProcOperator::AbstractImageProcOperator(QObject* parent) : QObject(parent)
{

}

const QString& AbstractImageProcOperator::name() const
{
    return m_name;
}

void AbstractImageProcOperator::setName(const QString& newName)
{
    m_name = newName;
}

void AbstractImageProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{

}
