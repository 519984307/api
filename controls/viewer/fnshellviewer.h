#ifndef FNSHELLVIEWER_H
#define FNSHELLVIEWER_H

#include <QWidget>
#include <QStack>
#include "fnshellfolderrect.h"
#include <QFileInfo>
#include <QDir>
#include <QPainter>
#include "fnshellitem.h"
#include "../base/widgethelper.h"
#include <QWheelEvent>

namespace Ui
{
class FnShellViewer;
}

class FnShellViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FnShellViewer(QWidget* parent = nullptr);
    ~FnShellViewer();

    const QString& rootPath() const;
    void setRootPath(const QString& newRootPath);
    WidgetHelper* helper() const;
    void setHelper(WidgetHelper* newHelper);
    void addFolderRect(QString path);
    FnShellItem* getSelectItem();
    void calHorScroll();

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
private:
    Ui::FnShellViewer* ui;
    QString m_rootPath;
    QList<FnShellFolderRect*> m_folders;
    WidgetHelper* m_helper;
    QRect m_horScrollRect;
    bool m_horScrollVisble;
    double m_factor;
    int m_allFoldersWidth;
};

#endif // FNSHELLVIEWER_H
