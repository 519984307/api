#include "fnconvert.h"

FnConvert::FnConvert(QObject* parent) : QObject(parent)
{

}

QString intToStr(int i)
{
    return QString("%1").arg(i);
}
