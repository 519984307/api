#include "office2pdfconverter.h"

Office2PdfConverter::Office2PdfConverter(QObject* parent) : QObject(parent)
{
    m_showOffice = false;
    m_skipExist = false;

}

QString Office2PdfConverter::srcPath() const
{
    return m_srcPath;
}

void Office2PdfConverter::setSrcPath(const QString& srcPath)
{
    m_srcPath = srcPath;
    QFileInfo info(m_srcPath);
    m_suffix = info.suffix().toLower();
    qDebug() << m_suffix;
}

QString Office2PdfConverter::destPath() const
{
    return m_destPath;
}

void Office2PdfConverter::setDestPath(const QString& destPath)
{
    m_destPath = destPath;

}

void Office2PdfConverter::convert()
{
    if (m_skipExist)
    {
        QFileInfo info(m_destPath);
        if (info.exists())
        {
            return;
        }
    }

    if ((m_suffix == "docx") || (m_suffix == "doc"))
    {
        QAxWidget* m_app = new QAxWidget("Word.Application");
        m_app->dynamicCall("SetVisible(bool)", m_showOffice);
        QAxObject* m_Documents = m_app->querySubObject("Documents");
        m_Documents->dynamicCall("Open(QString)", m_srcPath);
        QAxObject* m_doc = m_app->querySubObject("ActiveDocument");
        m_doc->dynamicCall("SaveAs(QString,int)", m_destPath, 17);
        m_doc->dynamicCall("Close(boolean)", true);//关闭
        m_app->dynamicCall("Quit()");//退出
        delete m_app;
    }
    else if ((m_suffix == "xlsx") || (m_suffix == "xls"))
    {
        QAxWidget* m_app = new QAxWidget("Excel.Application");
        qDebug() << m_app;
        m_app->dynamicCall("SetVisible(bool Visible)", m_showOffice);
        QAxObject* m_workbooks = m_app->querySubObject("Workbooks");

        m_workbooks->dynamicCall("Open(QString)", m_srcPath);
        QAxObject* m_doc = m_app->querySubObject("ActiveWorkbook");



        //转成pdf
        m_doc->dynamicCall("ExportAsFixedFormat(int, QString)",
                           0, m_destPath);

        //关闭
        m_doc->dynamicCall("Close(boolean)", false);

        delete m_app;
        qDebug() << "ok";
    }
    else if ((m_suffix == "pptx") || (m_suffix == "ppt"))
    {
        QAxWidget* m_app = new QAxWidget("PowerPoint.Application");
        m_app->dynamicCall("SetVisible(bool Visible)", m_showOffice);

        QAxObject* m_presentations = m_app->querySubObject("Presentations");

        m_presentations->dynamicCall("Open(QString)", m_srcPath);
        QAxObject* m_doc = m_app->querySubObject("ActivePresentation");
        QAxObject* m_window = m_app->querySubObject("ActiveWindow");

        m_doc->dynamicCall("SaveAs(Qstring,int,bool)", m_destPath, 32, false);

        m_doc->dynamicCall("Close()");//关闭
        m_app->dynamicCall("Quit()");//退出

        delete m_app;
        qDebug() << "ok";

    }
    taskkill();

}

bool Office2PdfConverter::showOffice() const
{
    return m_showOffice;
}

void Office2PdfConverter::setShowOffice(bool showOffice)
{
    m_showOffice = showOffice;
}

void Office2PdfConverter::taskkill()
{
    QString cmd;
    if ((m_suffix == "docx") || (m_suffix == "doc"))
    {
        cmd = "TASKKILL /F /IM winword.exe /T";
    }
    if ((m_suffix == "xls") || (m_suffix == "xlsx"))
    {
        cmd = "TASKKILL /F /IM excel.exe /T";
    }
    else if ((m_suffix == "pptx") || (m_suffix == "ppt"))
    {

        cmd = "TASKKILL /F /IM powerpnt.exe /T";
    }
    QProcess::execute(cmd);
}

bool Office2PdfConverter::skipExist() const
{
    return m_skipExist;
}

void Office2PdfConverter::setSkipExist(bool skipExist)
{
    m_skipExist = skipExist;
}
