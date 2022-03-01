#include "ioutils.h"


QString readString(QByteArray data)
{
    QTextCodec::ConverterState state;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QString text = codec->toUnicode(data.constData(), data.size(), &state);
    //等于是是GBK
    if (state.invalidChars > 0)
    {
        text = QTextCodec::codecForName("GBK")->toUnicode(data);
    }
    else
    {
        text = data;
    }

    return text;
}

QString readString(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = file.readAll();
    QString s = readString(data);
    QStringList stl = s.split("\n");
    qDebug() << stl;
    file.close();
    return s;
}
