#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H

#include <QObject>
#include <QUuid>
#include <QWidget>

class AbstractDao : public QObject {
    Q_OBJECT
public:
    explicit AbstractDao(QObject* parent = nullptr);
    QString createuuid();
signals:
};

#endif // ABSTRACTDAO_H
