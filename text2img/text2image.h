#ifndef TEXT2IMAGE_H
#define TEXT2IMAGE_H

#include <QObject>
#include "text2imageobject.h"
#include <QList>
#include <QImage>
#include <QPainter>

class Text2Image : public QObject
{
    Q_OBJECT
public:
    explicit Text2Image(QObject* parent = nullptr);

    QString srcInfo() const;
    void setSrcInfo(const QString& srcInfo);
    void clearTextObjects();
    void saveToImage(QImage& img);

    int lines() const;
    void setLines(int lines);

    QColor backGroundColor() const;
    void setBackGroundColor(const QColor& backGroundColor);

    QColor fontColor() const;
    void setFontColor(const QColor& fontColor);

    int fontSize() const;
    void setFontSize(int fontSize);

signals:

private:
    QString m_srcInfo;
    QList<Text2ImageObject*> m_textObjects;
    int m_leftMargin;
    int m_topMargin;
    int m_rightMargin;
    int m_bottomMargin;
    int m_pageWidth;
    int m_lines;
    int m_minPageHeight;
    int m_lineHeight;
    QColor m_backGroundColor;
    QColor m_fontColor;
    int m_fontSize;
    int m_fontWidth;

};

#endif // TEXT2IMAGE_H
