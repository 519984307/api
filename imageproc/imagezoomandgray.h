#ifndef IMAGEZOOMANDGRAY_H
#define IMAGEZOOMANDGRAY_H

#include <QObject>
#include <QFile>
#include <QFileInfoList>
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QApplication>


class ImageZoomAndGray : public QObject
{
    Q_OBJECT
public:
    QList<QString> imageFileNames;
    explicit ImageZoomAndGray(QObject* parent = nullptr);

    int zoomWidth() const;
    void setZoomWidth(int zoomWidth);

    int zoomHeight() const;
    void setZoomHeight(int zoomHeight);

    QString exportFolder() const;
    void setExportFolder(const QString& exportFolder);
    void startProc();
    void openFolder(QString path);
    QImage toGray(QImage image);
signals:

private:
    int m_zoomWidth;
    int m_zoomHeight;
    QString m_exportFolder;

};

#endif // IMAGEZOOMANDGRAY_H
