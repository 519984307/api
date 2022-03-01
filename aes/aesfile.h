#ifndef AESFILE_H
#define AESFILE_H

#include <QObject>
#include "qaesencryption.h"
#include <QFile>
#include <QCryptographicHash>
#include <QPixmap>
#include <QJsonObject>
#include <QBuffer>
#include <QFileInfo>
#include <QJsonDocument>

class AesFile : public QObject
{
    Q_OBJECT
public:
    explicit AesFile(QObject* parent = nullptr);

    const QString& pathName() const;
    void setPathName(const QString& newPathName);

    const QString& key() const;
    void setKey(const QString& newKey);
    void encryptFile(QString pathName, QString retPathName);
    void encryptImageFile(QString pathName, QString retPathName, int maxSideLen = 1920);
    void encryptByteArray(QByteArray& srcData, QString retPathName);
    void decryptFile(QString pathName, QString retPathName);
    void decryptAsPixmap(QString pathName, QPixmap& pix);
    void decryptAsJsonDocument(QString pathName, QJsonDocument& jdoc);
signals:
private:
    QString m_pathName;
    QString m_key;
    QByteArray m_hash;
};

#endif // AESFILE_H
