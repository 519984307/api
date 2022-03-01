#ifndef FNTITLEBAR_H
#define FNTITLEBAR_H

#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include <QStyle>
#include <QMenuBar>



namespace Ui
{
class FnTitleBar;
}
enum FnTitleBarStyle
{
    fsVsCode,
    fsWord
};

class FnTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit FnTitleBar(QWidget* parent = nullptr);
    ~FnTitleBar();


    FnTitleBarStyle titleBarStyle() const;
    void setTitleBarStyle(const FnTitleBarStyle& titleBarStyle);

    QPixmap icon() const;
    void setIcon(const QPixmap& icon);
    QMainWindow* parentWindow() const;
    void setParentWindow(QMainWindow* parentWindow);

    QPixmap minIcon() const;
    void setMinIcon(const QPixmap& minIcon);

    QPixmap maxIcon() const;
    void setMaxIcon(const QPixmap& maxIcon);

    QPixmap closeIcon() const;

    QPixmap restoreIcon() const;
    void setRestoreIcon(const QPixmap& restoreIcon);

    void setCloseIcon(const QPixmap& closeIcon);

    void setMenuBar(QMenuBar* menuBar);

    QMenuBar* menuBar() const;

    bool isMaxButtonEnabled() const;
    void setIsMaxButtonEnabled(bool newIsMaxButtonEnabled);

    const QString& caption() const;
    void setCaption(const QString& newCaption);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private slots:
    void on_btnMax_clicked();

    void on_btnMin_clicked();

    void on_btnClose_clicked();

private:
    Ui::FnTitleBar* ui;
    FnTitleBarStyle m_titleBarStyle;
    QPixmap m_icon;
    QMainWindow* m_parentWindow;
    bool m_mousedownFlag;
    QPoint m_mouseDownPoint;
    QPixmap m_minIcon;
    QPixmap m_maxIcon;
    QPixmap m_closeIcon;
    QPixmap m_restoreIcon;
    bool m_isNormal;
    QMenuBar* m_menuBar;
    bool m_isMaxButtonEnabled;
    QString m_caption;

};

#endif // FNTITLEBAR_H
