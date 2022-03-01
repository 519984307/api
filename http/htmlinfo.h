#ifndef HTMLINFO_H
#define HTMLINFO_H

#include <QObject>
#include <QString>
#include <QRegExp>

QString getTitle(QString html);
bool hasKeywordInHtml(QString html, QString s);
void getImageSrc(QString html, QStringList& stl);
QString getSrcFromImageTag(QString imgTag);

#endif // HTMLINFO_H
