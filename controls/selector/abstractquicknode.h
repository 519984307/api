#ifndef ABSTRACTQUICKNODE_H
#define ABSTRACTQUICKNODE_H

#include <QObject>
#include <QWidget>

class AbstractQuickNode : public QObject
{
    Q_OBJECT
public:
    explicit AbstractQuickNode(QObject* parent = nullptr);

    QRect rect() const;
    void setRect(const QRect& rect);

    QString caption() const;
    void setCaption(const QString& caption);

    int startPos() const;
    void setStartPos(int startPos);

signals:
protected:
    QRect m_rect;
    QString m_caption;
    int m_startPos;

};

#endif // ABSTRACTQUICKNODE_H
