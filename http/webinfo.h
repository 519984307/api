#ifndef WEBINFO_H
#define WEBINFO_H

#include "synchttp.h"
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QRegExp>
#include <QTextCodec>
#else
#include <QtCore5Compat/QTextCodec>
#include <QtCore5Compat/QRegExp>
#endif

#include <QSslSocket>

#include <QWidget>

class WebInfo : public SyncHttp
{
    Q_OBJECT
public:
    explicit WebInfo(QWidget* parent = nullptr);
    QString getTitle(QString url);
    QImage getFavicon(QString url, bool& isBmp);
    bool isBmp(QByteArray& data);

signals:
};

#endif // WEBINFO_H
