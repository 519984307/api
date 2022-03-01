#ifndef FILESEACHER_H
#define FILESEACHER_H

#include <QDir>
#include <QObject>
#include <QtDebug>

class FileSeacher : public QObject {
    Q_OBJECT
public:
    explicit FileSeacher(QObject* parent = nullptr);

    void startSearch(QString rootPath);

    int pid() const;
    void setPid(int pid);

private:
    QString rootPath;
    void searchDir(QString path);
signals:
    void findFileInfo(QString rootPath, QFileInfo& fileInfo);
public slots:

private:
    int m_pid;
};

#endif // FILESEACHER_H
