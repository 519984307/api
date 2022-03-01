#include "fnappconfig.h"
shared_ptr<FnAppConfig> FnAppConfig::m_fnAppConfig = nullptr;
FnAppConfig::FnAppConfig(QObject* parent) : QObject(parent)
{
    qDebug() << "FnAppConfig()";
    m_groupName = "set";
    m_configPath = QApplication::applicationDirPath() + "/config.ini";


}

FnAppConfig::~FnAppConfig()
{
    qDebug() << "~FnAppConfig()";

}

QString FnAppConfig::configPath() const
{
    return m_configPath;
}

void FnAppConfig::setConfigPath(const QString& configPath)
{
    m_configPath = configPath;
}

void FnAppConfig::setValue(QString key, QVariant value)
{
    QSettings ini(m_configPath, QSettings::IniFormat);
    ini.beginGroup(m_groupName);
    ini.setValue(key, value);
    ini.endGroup();
}

QVariant FnAppConfig::getValue(QString key, QVariant defaultValue)
{
    QSettings ini(m_configPath, QSettings::IniFormat);
    ini.beginGroup(m_groupName);
    QVariant ret = ini.value(key, defaultValue);
    ini.endGroup();
    return ret;
}

QString FnAppConfig::groupName() const
{
    return m_groupName;
}

void FnAppConfig::setGroupName(const QString& groupName)
{
    m_groupName = groupName;
}

void FnAppConfig::setValue(QString key, QLineEdit* edit)
{
    setValue(key, edit->text());

}



FnAppConfig* fnAppConfig()
{
    if (FnAppConfig::m_fnAppConfig == nullptr)
    {
        FnAppConfig::m_fnAppConfig = shared_ptr<FnAppConfig>(new FnAppConfig());
    }

    return FnAppConfig::m_fnAppConfig.get();
}
