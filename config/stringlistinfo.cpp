#include "stringlistinfo.h"

StringListInfo::StringListInfo(QObject* parent) : QObject(parent)
{
    m_folderPath = QApplication::applicationDirPath() + "/configs";
    setFolderPath(m_folderPath);
    m_fileName = "default.txt";
}



const QString& StringListInfo::folderPath() const
{
    return m_folderPath;
}

void StringListInfo::setFolderPath(const QString& newFolderPath)
{
    m_folderPath = newFolderPath;
    QDir dir;
    dir.mkpath(m_folderPath);
}

const QString& StringListInfo::fileName() const
{
    return m_fileName;
}

void StringListInfo::setFileName(const QString& newFileName)
{
    m_fileName = newFileName;
}

void StringListInfo::loadInfo()
{
    QFile file(m_folderPath + "/" + m_fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream stm(&file);
    this->clear();
    QStringList stl;
    while (!stm.atEnd())
    {
        stl << stm.readLine();

    }

    this->append(stl);
    file.close();

}

void StringListInfo::saveInfo()
{
    QFile file(m_folderPath + "/" + m_fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream stm(&file);
    for (int i = 0; i < this->count(); i++)
    {
        stm << this->at(i) << "\n";
    }
    file.close();


}
