#ifndef VALUESPLITER_H
#define VALUESPLITER_H

#include <QObject>

class ValueSpliter : public QObject
{
    Q_OBJECT
public:
    explicit ValueSpliter(QObject* parent = nullptr);

    const QString& value() const;
    void setValue(const QString& newValue);
    QStringList result();
    QStringList valueToStringList(QString s);
    double valueStep() const;
    void setValueStep(double newValueStep);

signals:
private:
    QString m_value;
    double m_valueStep;



};

#endif // VALUESPLITER_H
