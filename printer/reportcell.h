#ifndef REPORTCELL_H
#define REPORTCELL_H

#include <QObject>

class ReportCell : public QObject
{
    Q_OBJECT
public:
    explicit ReportCell(QObject* parent = nullptr);


signals:
private:
    bool m_drawLeft;
    bool m_drawRight;

};

#endif // REPORTCELL_H
