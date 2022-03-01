#include "text2image.h"

Text2Image::Text2Image(QObject* parent) : QObject(parent)
{
    m_leftMargin = 32;
    m_topMargin = 64;
    m_rightMargin = 32;
    m_bottomMargin = 32;
    m_pageWidth = 1080;
    m_minPageHeight = 1920;
    m_lineHeight = 48;
    m_backGroundColor = Qt::white;
    m_fontColor = Qt::black;
    m_fontSize = 28;
    m_fontWidth = 14;

}

QString Text2Image::srcInfo() const
{
    return m_srcInfo;
}

void Text2Image::setSrcInfo(const QString& srcInfo)
{
    m_srcInfo = srcInfo;
    clearTextObjects();
    int l = m_leftMargin;
    int t = m_topMargin;
    int sz = m_fontSize;
    int h = m_lineHeight;
    int w = m_fontWidth;
    m_lines = 1;
    for (int i = 0; i < m_srcInfo.count(); i++)
    {
        Text2ImageObject* obj = new Text2ImageObject(this);
        obj->setText(m_srcInfo.at(i));
        QRect rc(l, t, w * obj->length(), h);
        obj->setTextRect(rc);

        m_textObjects << obj;
        if (((l + w * 4) >= (m_pageWidth - m_rightMargin)) || (obj->text() == "\n"))
        {
            l = m_leftMargin;
            t += h;
            m_lines++;
        }
        else
        {
            l += w * obj->length();
        }




    }
    m_lines += 4;
}

void Text2Image::clearTextObjects()
{
    qDeleteAll(m_textObjects);
    m_textObjects.clear();
}

void Text2Image::saveToImage(QImage& img)
{
    int imgHeight = m_lines * m_lineHeight + m_bottomMargin >= m_minPageHeight
                    ? m_lines * m_lineHeight + m_bottomMargin : m_minPageHeight;
    img = QImage(m_pageWidth, imgHeight, QImage::Format_RGB888);
    QPainter painter;

    painter.begin(&img);
    painter.setPen(m_fontColor);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    QFont font = painter.font();
    font.setFamily("楷体_GB2312");
    font.setPixelSize(m_fontSize);
    painter.setFont(font);
    QRect clientRc = QRect(0, 0, img.width(), img.height());
    painter.fillRect(clientRc, QBrush(m_backGroundColor));
    for (int i = 0; i < m_textObjects.count(); i++)
    {
        Text2ImageObject* obj = m_textObjects.at(i);
        painter.drawText(obj->textRect(), Qt::AlignCenter, obj->text());
    }
    painter.end();



}

int Text2Image::lines() const
{
    return m_lines;
}

void Text2Image::setLines(int lines)
{
    m_lines = lines;
}

QColor Text2Image::backGroundColor() const
{
    return m_backGroundColor;
}

void Text2Image::setBackGroundColor(const QColor& backGroundColor)
{
    m_backGroundColor = backGroundColor;
}

QColor Text2Image::fontColor() const
{
    return m_fontColor;
}

void Text2Image::setFontColor(const QColor& fontColor)
{
    m_fontColor = fontColor;
}

int Text2Image::fontSize() const
{
    return m_fontSize;
}

void Text2Image::setFontSize(int fontSize)
{
    m_fontSize = fontSize;
}
