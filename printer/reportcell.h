#ifndef REPORTCELL_H
#define REPORTCELL_H

#include <QObject>

class ReportCell : public QObject
{
    Q_OBJECT
public:
    explicit ReportCell(QObject* parent = nullptr);


    const QString& text() const;
    void setText(const QString& newText);

    int left() const;
    void setLeft(int newLeft);

    int top() const;
    void setTop(int newTop);

    int width() const;
    void setWidth(int newWidth);

    int height() const;
    void setHeight(int newHeight);
    int right();
    void setRectMm(int leftMm, int topMm, int widthMm, int BottomMm);
    int MmToPt(int m);
signals:
private:
    bool m_drawLeft;
    bool m_drawRight;

    int m_left;
    int m_top;
    int m_width;
    int m_height;
    QString m_text;

};

#endif // REPORTCELL_H
