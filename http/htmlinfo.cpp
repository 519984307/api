#include "htmlinfo.h"



QString getTitle(QString html)
{
    int p = html.indexOf("<title>");
    int q = html.indexOf("</title>");
    QString s = html.mid(p + 7, q - p - 7);
    return s;

}

bool hasKeywordInHtml(QString html, QString s)
{
    return html.indexOf(s) >= 0;
}

void getImageSrc(QString html, QStringList& stl)
{
    QString s = html;
    int p = s.indexOf("<img");

    while (p >= 0)
    {
        s = s.mid(p);
        int q = s.indexOf(">");
        QString v = s.left(q + 1);
        stl << getSrcFromImageTag(v);
        s = s.mid(q + 1);
        p = s.indexOf("<img");

    }

}

QString getSrcFromImageTag(QString imgTag)
{
    QString s = imgTag;
    int p = s.indexOf("\"");
    s = s.mid(p + 1);
    p = s.indexOf("\"");
    s = s.left(p);
    return s;

}
