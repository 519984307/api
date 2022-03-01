#ifndef FNAPPCONFIG_H
#define FNAPPCONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QWidget>
#include <memory>
#include <QApplication>
#include <QLineEdit>

using namespace std;

class FnAppConfig : public QObject
{
    Q_OBJECT
public:
    explicit FnAppConfig(QObject* parent = nullptr);
    ~FnAppConfig();
    static shared_ptr<FnAppConfig> m_fnAppConfig;
    QString configPath() const;
    void setConfigPath(const QString& configPath);
    void setValue(QString key, QVariant value);
    void setValue(QString key, QLineEdit* edit);
    QVariant getValue(QString key, QVariant defaultValue = QVariant());
    QString groupName() const;
    void setGroupName(const QString& groupName);

signals:
private:
    QString m_configPath;
    QString m_groupName;


};
FnAppConfig* fnAppConfig();

#endif // FNAPPCONFIG_H
