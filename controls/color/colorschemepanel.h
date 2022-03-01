#ifndef COLORSCHEMEPANEL_H
#define COLORSCHEMEPANEL_H

#include "../../color/colorobject.h"
#include <QAction>
#include <QPainter>
#include <QWidget>

namespace Ui {
class ColorSchemePanel;
}

class ColorSchemePanel : public QWidget {
    Q_OBJECT

public:
    explicit ColorSchemePanel(QWidget* parent = nullptr);
    ~ColorSchemePanel();

    int id() const;
    void setId(int id);

    QString& name();
    void setName(QString name);
    void paintEvent(QPaintEvent* event);
    void clearColors();
    QList<ColorObject*> colors() const;
    void setColors(const QList<ColorObject*>& colors);
    void addColor(int id, QString name, int r, int g, int b);
    void mouseDoubleClickEvent(QMouseEvent* event);
signals:
    void onDoubleClick();

private:
    Ui::ColorSchemePanel* ui;
    int m_id;
    QString m_name;
    QList<ColorObject*> m_colors;
};

#endif // COLORSCHEMEPANEL_H
