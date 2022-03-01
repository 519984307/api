#ifndef GLOBALCONST_H
#define GLOBALCONST_H

#include <QObject>
#include <QWidget>

const QString NullUuid = "00000000-0000-0000-0000-00000000000";
class GlobalConst : public QObject {
    Q_OBJECT
public:
    explicit GlobalConst(QObject* parent = nullptr);

signals:
};

#endif // GLOBALCONST_H
