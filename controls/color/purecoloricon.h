#ifndef PURECOLORICON_H
#define PURECOLORICON_H

#include <QListWidgetItem>
#include <QPainter>
#include <QWidget>

namespace Ui {
class PureColorIcon;
}

class PureColorIcon : public QWidget {
    Q_OBJECT

public:
    explicit PureColorIcon(QWidget* parent = nullptr);
    ~PureColorIcon();
    int r() const;
    void setR(int r);

    int g() const;
    void setG(int g);

    int b() const;
    void setB(int b);

    int a() const;
    void setA(int a);

    int id() const;
    void setId(int id);

    void setName(QString name);

    QString name() const;
    QString intToHex(int i);
    QString htmlColor();
    PureColorIcon* getNew(QWidget* parent);

    QListWidgetItem* getItem() const;
    void setItem(QListWidgetItem* item);

signals:
    void onDoubleClick();

protected:
    void paintEvent(QPaintEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    Ui::PureColorIcon* ui;
    int m_r;
    int m_g;
    int m_b;
    int m_a;
    int m_id;

    QString m_name;
    QListWidgetItem* m_item;
};

#endif // PURECOLORICON_H
