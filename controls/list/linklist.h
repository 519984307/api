#ifndef LINKLIST_H
#define LINKLIST_H

#include <QWidget>
#include "linkinfo.h"
#include "../base/widgethelper.h"
#include <QDesktopServices>
#include <QUrl>
#include <QToolTip>
#include <QWheelEvent>
#include <QAction>
#include <QClipboard>

namespace Ui
{
class LinkList;
}

class LinkList : public QWidget
{
    Q_OBJECT

public:
    explicit LinkList(QWidget* parent = nullptr);
    ~LinkList();

    int linkWidth() const;
    void setLinkWidth(int newLinkWidth);

    int linkHeight() const;
    void setLinkHeight(int newLinkHeight);
    QList<LinkInfo*> m_linkInfos;
    void clearLinks();
    LinkInfo* addLink(QString name, QString url);
    void addDefaultMenu();
signals:
    void clickLink(LinkInfo* link);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private slots:
    void onMenuTriggered();
private:
    Ui::LinkList* ui;
    int m_linkWidth;
    int m_linkHeight;
    WidgetHelper* m_helper;
    LinkInfo* m_selLink;
};

#endif // LINKLIST_H
