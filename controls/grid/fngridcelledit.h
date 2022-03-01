#ifndef FNGRIDCELLEDIT_H
#define FNGRIDCELLEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>

class FnGridCellEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit FnGridCellEdit(QWidget* parent = nullptr);

signals:

};

#endif // FNGRIDCELLEDIT_H
