#ifndef IOUTILS_H
#define IOUTILS_H

#include <QObject>
#include <QFile>
#include <QTextCodec>
#include <QDebug>

//读取数据信息
QString readString(QByteArray data);
QString readString(QString filePath);
#endif // IOUTILS_H
