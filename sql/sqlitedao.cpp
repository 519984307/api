#include "sqlitedao.h"
SqliteDao* SqliteDao::m_instance = nullptr;
SqliteDao* SqliteDao::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new SqliteDao(nullptr);
    }
    return m_instance;
}

void SqliteDao::freeInstance()
{
    if (m_instance != nullptr)
    {
        delete m_instance;
    }
}

SqliteDao::SqliteDao(QObject* parent)
    : QObject(parent)
{

    m_sqliteWrapper = new SqliteWrapper(this);
#ifdef Q_OS_ANDROID
    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    QString path = paths[0] + "/data.db";
    QFileInfo info;
    if (!info.exists(path))
    {

        QFile f;
        f.copy("assets:/data/data.db", path);
        f.setPermissions(path, QFile::ReadOwner | QFile::WriteOwner);
    }
    qDebug() << path;
    m_sqliteWrapper->setFileName(path);
#else
    m_sqliteWrapper->setFileName("data/data.db");
#endif

    m_sqliteWrapper->setDbName("data");
    m_sqliteWrapper->open();
}

SqliteWrapper* SqliteDao::sqliteWrapper() const
{
    return m_sqliteWrapper;
}

bool SqliteDao::transaction()
{
    m_sqliteWrapper->getDataBase().transaction();
    return true;
}

void SqliteDao::commit()
{
    m_sqliteWrapper->getDataBase().commit();
}

SqliteDao* sqliteDao()
{
    return SqliteDao::instance();
}
