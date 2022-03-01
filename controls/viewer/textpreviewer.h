#ifndef TEXTPREVIEWER_H
#define TEXTPREVIEWER_H

#include <QWidget>
#include <QPainter>
#include "../base/widgethelper.h"
#include "../base/drawtextitem.h"
#include <QWheelEvent>

namespace Ui
{
class TextPreViewer;
}

class TextPreViewer : public QWidget
{
    Q_OBJECT

public:
    explicit TextPreViewer(QWidget* parent = nullptr);
    ~TextPreViewer();


    int fontSize() const;
    void setFontSize(int newFontSize);



    const QList<DrawTextItem*>& lines() const;
    void setLines(const QList<DrawTextItem*>& newLines);
    void loadLines(QStringList& lines);
signals:
    void doubleClickItem(DrawTextItem* item);
    void clickItem(DrawTextItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    bool event(QEvent* event) override;
private:
    Ui::TextPreViewer* ui;
    QList<DrawTextItem*> m_lines;
    WidgetHelper* m_helper;
    int m_fontSize;
    bool m_firstLineAsTitle;
    double m_touchLen1;
    double m_touchLen2;

};

#endif // TEXTPREVIEWER_H
