#ifndef SELECTIONITEM_H
#define SELECTIONITEM_H

#include <QObject>
#include <QPixmap>
#include <QRect>

class SelectionItem : public QObject {
    Q_OBJECT
public:
    explicit SelectionItem(QObject* parent = nullptr);
    void setItemRect(QRect& itemRect);
    QRect& itemRect();
    QString caption() const;
    void setCaption(const QString& caption);

    QPixmap icon() const;
    void setIcon(const QPixmap& icon);

    bool selected() const;
    void setSelected(bool selected);

signals:

private:
    QString m_caption;
    QRect m_itemRect;
    QPixmap m_icon;
    bool m_selected;
};

#endif // SELECTIONITEM_H
