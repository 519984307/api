#include "colorutils.h"


QColor hexToColor(QString hex, QColor defaultColor)
{
    if (!hex.startsWith("0x"))
    {
        return defaultColor;
    }
    //0xffffff
    QString sr = hex.mid(2, 2);
    QString sg = hex.mid(4, 2);
    QString sb = hex.mid(6, 2);
    int r = sr.toInt(nullptr, 16);
    int g = sg.toInt(nullptr, 16);
    int b = sb.toInt(nullptr, 16);
    return QColor(r, g, b);

}
