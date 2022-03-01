#ifndef CHATLISTITEM_H
#define CHATLISTITEM_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class ChatListItem;
}
enum IconAlign {
    IaLeft,
    IaRight
};

class ChatListItem : public QWidget {
    Q_OBJECT

public:
    explicit ChatListItem(QWidget* parent = nullptr);
    ~ChatListItem();
    QPixmap icon() const;
    void setIcon(const QPixmap& icon);

    QString info() const;
    void setInfo(const QString& info);

    IconAlign iconAlign() const;
    void setIconAlign(const IconAlign& iconAlign);

    QColor textBackColor() const;
    void setTextBackColor(const QColor& textBackColor);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::ChatListItem* ui;
    QPixmap m_icon;
    QString m_info;
    IconAlign m_iconAlign;
    QColor m_textBackColor;
};

#endif // CHATLISTITEM_H
