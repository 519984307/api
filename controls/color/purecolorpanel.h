#ifndef PURECOLORPANEL_H
#define PURECOLORPANEL_H

#include <QAction>
#include <QListWidget>
#include <QPainter>
#include <QWidget>
namespace Ui {
class PureColorPanel;
}

class PureColorPanel : public QWidget {
    Q_OBJECT

public:
    explicit PureColorPanel(QWidget* parent = nullptr);
    ~PureColorPanel();

    int r() const;
    void setR(int r);

    int g() const;
    void setG(int g);

    int b() const;
    void setB(int b);

    int a() const;
    void setA(int a);

    QString name() const;
    void setName(const QString& name);

    int id() const;
    void setId(int id);
    QString intToHex(int i);
    static int lastId;
    QListWidgetItem* item() const;
    void setItem(QListWidgetItem* item);
    QString htmlColor();

public slots:
    void triggered();
signals:
    void onClick();
    void onMenuClick(PureColorPanel* sender, QAction* action);

protected:
    void paintEvent(QPaintEvent* event);
    void focusOutEvent(QFocusEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::PureColorPanel* ui;
    int m_r;
    int m_g;
    int m_b;
    int m_a;
    int m_id;
    QString m_name;
    QListWidgetItem* m_item;
};

#endif // PURECOLORPANEL_H
