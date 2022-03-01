#ifndef IMAGEPRINTER_H
#define IMAGEPRINTER_H

#include <QObject>
#include <QList>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QApplication>

class ImagePrinter : public QObject
{
    Q_OBJECT
public:
    explicit ImagePrinter(QObject* parent = nullptr);

    const QStringList& printFiles() const;
    void setPrintFiles(const QStringList& newPrintFiles);
    void loadFromFolder(QString folderPath);
    void print();
signals:
private:
    QStringList m_printFiles;

};

#endif // IMAGEPRINTER_H
