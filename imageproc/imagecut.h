#ifndef IMAGECUT_H
#define IMAGECUT_H

#include <QObject>
#include <QPixmap>
#include <QFileInfo>
#include <QPainter>

class ImageCut : public QObject
{
    Q_OBJECT
public:
    explicit ImageCut(QObject* parent = nullptr);

    QString srcPath() const;
    void setSrcPath(const QString& srcPath);

    QString getExportFolder() const;
    void setExportFolder(const QString& value);
    void cutByNumbers(int hor, int ver);

signals:
private:
    QString m_srcPath;
    QString m_exportFolder;

};

#endif // IMAGECUT_H
