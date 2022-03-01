#ifndef LOGOWIDGET_H
#define LOGOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QDebug>


namespace Ui
{
class LogoWidget;
}

class LogoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogoWidget(QWidget* parent = nullptr);
    ~LogoWidget();

    QString filePath() const;
    void setFilePath(const QString& filePath);

protected:
    void paintEvent(QPaintEvent* event);
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::LogoWidget* ui;
    QString m_filePath;
};

#endif // LOGOWIDGET_H
