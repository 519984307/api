#include "aesfile.h"

AesFile::AesFile(QObject* parent) : QObject(parent)
{
    setKey("Qin1987Xiao0428feng");


}

const QString& AesFile::pathName() const
{
    return m_pathName;
}

void AesFile::setPathName(const QString& newPathName)
{
    m_pathName = newPathName;
}



const QString& AesFile::key() const
{
    return m_key;
}

void AesFile::setKey(const QString& newKey)
{
    m_key = newKey;
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(m_key.toUtf8());
    m_hash = hash.result();

}

void AesFile::encryptFile(QString pathName, QString retPathName)
{


    QFile file(pathName);
    file.open(QFile::ReadOnly);
    QByteArray srcData = file.readAll();
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QByteArray destData = encryption.encode(srcData, m_hash);
    file.close();
    QFile destFile(retPathName);
    destFile.open(QFile::WriteOnly);
    destFile.write(destData);
    destFile.close();

}

void AesFile::encryptImageFile(QString pathName, QString retPathName, int maxSideLen)
{
    QPixmap pix(pathName);
    if (pix.width() > pix.height())
    {
        if (pix.width() > maxSideLen)
        {
            pix = pix.scaledToWidth(maxSideLen);
        }
    }
    else
    {
        if (pix.height() > maxSideLen)
        {
            pix.scaledToHeight(maxSideLen);
        }
    }
    QFileInfo info(pathName);
    QByteArray srcData = QByteArray();;
    QBuffer buf(&srcData);
    buf.open(QIODevice::WriteOnly);
    pix.save(&buf, info.suffix().toLocal8Bit().data());
    buf.close();


    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QByteArray destData = encryption.encode(srcData, m_hash);

    QFile destFile(retPathName);
    destFile.open(QFile::WriteOnly);
    destFile.write(destData);
    destFile.close();
    QString configPath = retPathName + ".json";
    QJsonDocument jdoc;
    QFile jdocFile(configPath);
    jdocFile.open(QFile::WriteOnly);
    QJsonObject jobj;
    jobj["width"] = pix.width();
    jobj["height"] = pix.height();
    jdoc.setObject(jobj);
    QByteArray jdata = jdoc.toJson();
    jdocFile.write(jdata);

    jdocFile.close();

}

void AesFile::encryptByteArray(QByteArray& srcData, QString retPathName)
{

    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QByteArray destData = encryption.encode(srcData, m_hash);
    QFile destFile(retPathName);
    destFile.open(QFile::WriteOnly);
    destFile.write(destData);
    destFile.close();
}

void AesFile::decryptFile(QString pathName, QString retPathName)
{
    QFile file(pathName);
    file.open(QFile::ReadOnly);
    QByteArray srcData = file.readAll();
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QByteArray destData = encryption.decode(srcData, m_hash);
    file.close();
    QFile destFile(retPathName);
    destFile.open(QFile::WriteOnly);
    destFile.write(destData);
    destFile.close();
}

void AesFile::decryptAsPixmap(QString pathName, QPixmap& pix)
{
    QFile file(pathName);
    file.open(QFile::ReadOnly);
    QByteArray srcData = file.readAll();
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QByteArray destData = encryption.decode(srcData, m_hash);
    file.close();

    pix.loadFromData(destData);
}

void AesFile::decryptAsJsonDocument(QString pathName, QJsonDocument& jdoc)
{
    QFile file(pathName);
    file.open(QFile::ReadOnly);
    QByteArray srcData = file.readAll();
    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB);
    QByteArray destData = encryption.decode(srcData, m_hash);
    file.close();
    jdoc = QJsonDocument::fromJson(destData);

}


