#ifndef REPORTCELL_H
#define REPORTCELL_H

#include <QObject>
#include <QRectF>
#include <QJsonObject>
#include <functional>
using namespace std;
class ReportCell;

class ReportCell : public QObject
{
    Q_OBJECT
public:
    explicit ReportCell(QObject* parent = nullptr);


    const QString& text() const;
    void setText(const QString& newText);


    double right();
    void setRectMm(double leftMm, double topMm, double widthMm, double BottomMm);
    double MmToPt(double m);
    double left() const;
    void setLeft(double newLeft);

    double top() const;
    void setTop(double newTop);

    double width() const;
    void setWidth(double newWidth);

    double height() const;
    void setHeight(double newHeight);

    const QString& fontName() const;
    void setFontName(const QString& newFontName);

    int fontSize() const;
    void setFontSize(int newFontSize);

    void drawAllBorder(bool b);

    bool drawLeft() const;
    void setDrawLeft(bool newDrawLeft);

    bool drawRight() const;
    void setDrawRight(bool newDrawRight);

    bool drawTop() const;
    void setDrawTop(bool newDrawTop);

    bool drawBottom() const;
    void setDrawBottom(bool newDrawBottom);

    QRectF rectF();
    QRect rect();

    bool selected() const;
    void setSelected(bool newSelected);
    void movePositionBy(double dx, double dy);

    int colIndex() const;
    void setColIndex(int newColIndex);

    int rowIndex() const;
    void setRowIndex(int newRowIndex);
    double bottom();

    QJsonObject toJsonObject();
    void fromJObject(QJsonObject& jobj);

    bool bold() const;
    void setBold(bool newBold);

signals:
private:
    bool m_drawLeft;
    bool m_drawRight;
    bool m_drawTop;
    bool m_drawBottom;

    double m_left;
    double m_top;
    double m_width;
    double m_height;
    QString m_text;
    QString m_fontName;
    int m_fontSize;
    bool m_selected;
    int m_colIndex;
    int m_rowIndex;
    bool m_bold;

};

#endif // REPORTCELL_H
