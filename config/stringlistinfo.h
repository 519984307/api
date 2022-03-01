#ifndef STRINGLISTINFO_H
#define STRINGLISTINFO_H

#include <QObject>
#include <QApplication>
#include <QDir>
#include <QUuid>
#include <QTextStream>


class StringListInfo : public QObject, public QStringList
{
    Q_OBJECT
public:
    explicit StringListInfo(QObject* parent = nullptr);




    const QString& folderPath() const;
    void setFolderPath(const QString& newFolderPath);

    const QString& fileName() const;
    void setFileName(const QString& newFileName);
    void loadInfo();
    void saveInfo();
signals:
private:

    QString m_folderPath;
    QString m_fileName;
};

#endif // STRINGLISTINFO_H
