#include "csvreader.h"

CsvReader::CsvReader(QObject* parent) : QObject(parent)
{

}

CsvReader::~CsvReader()
{
    clearRowDatas();
}

QString CsvReader::fileName() const
{
    return m_fileName;
}

void CsvReader::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

void CsvReader::loadfromFileName(QString& fileName)
{
    clearRowDatas();
    m_fileName = fileName;
    QFile file(m_fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QString infos = readString(data);
    int i;
    QStringList* rowData = nullptr;
    rowData = new QStringList();
    do
    {
        i = infos.indexOf("\"");
        infos = infos.mid(i + 1);
        int j = infos.indexOf("\"");
        QString s = infos.left(j);
        rowData->append(s);
        infos = infos.mid(j + 1);
        if (infos.indexOf("\n") == 0)
        {
            rowDatas << rowData;
            rowData = new QStringList();
            QApplication::processEvents();
        }
        if (infos == "\n")
        {
            break;
        }

    }
    while (i >= 0);





    file.close();
}

void CsvReader::clearRowDatas()
{
    qDeleteAll(rowDatas);
    rowDatas.clear();
}
