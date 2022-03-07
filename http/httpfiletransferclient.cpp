#include "httpfiletransferclient.h"

HttpFileTransferClient::HttpFileTransferClient(QObject* parent) : QObject(parent)
{

}

bool HttpFileTransferClient::download(QString url, QMap<QString, QString>& values, QString saveFileName)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QMap<QString, QString>::iterator it = values.begin();
    for (; it != values.end(); it++)
    {
        qDebug() << it.key() << it.value();
        QHttpPart part;

        part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(it.key())));
        part.setBody(QString(it.value()).toLatin1());

        multiPart->append(part);

    }
    request.setUrl(QUrl(url));

    QNetworkReply* replay = manager->post(request, multiPart);
    QEventLoop loop;
    connect(replay, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    int  retCode = replay->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << retCode;
    QByteArray retData = replay->readAll();
    qDebug() << retData.size();
    if (retData.size() > 0)
    {
        QFile file(saveFileName);
        file.open(QIODevice::WriteOnly);
        file.write(retData);
        file.close();
    }



    delete manager;
    delete multiPart;
    if (retCode != 200)
    {
        return false;
    }
    else
    {
        return retData.size() != 0;

    }


}

bool HttpFileTransferClient::upload(QString url, QMap<QString, QString>& values, QString savefieldName, QString saveFileName)
{
    QFile* file = new QFile(saveFileName);
    QFileInfo fileInfo(saveFileName);
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    // request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data"));


    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QMap<QString, QString>::iterator it = values.begin();
    for (; it != values.end(); it++)
    {
        qDebug() << it.key() << it.value();
        QHttpPart part;

        part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(it.key())));
        part.setBody(QString(it.value()).toLatin1());

        multiPart->append(part);

    }

    {
//        QHttpPart fileNamePart;
//        fileNamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(savefieldName)));
//        fileNamePart.setBody(QString(file->fileName()).toLatin1());
//        multiPart->append(fileNamePart);

        QHttpPart filePart;

        QString requestFormat = QString("form-data;name=%1;filename=%2;type = application/octet-stream")
                                .arg(savefieldName)
                                .arg(fileInfo.fileName());
        qDebug() << requestFormat;
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(requestFormat));




        file->open(QIODevice::ReadOnly);
        filePart.setBodyDevice(file);
        //file->setParent(multiPart);
        // we cannot delete the file now, so delete it with the multiPart
        multiPart->append(filePart);







    }

    request.setUrl(QUrl(url));

    QNetworkReply* replay = manager->post(request, multiPart);
    QEventLoop loop;
    connect(replay, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    int  retCode = replay->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << retCode;




    delete manager;
    delete multiPart;
    delete file;
    if (retCode != 200)
    {
        return false;
    }
    else
    {
        return true;

    }


}
