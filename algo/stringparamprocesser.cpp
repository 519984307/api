#include "stringparamprocesser.h"

StringParamProcesser::StringParamProcesser(QObject* parent) : QObject(parent)
{
    m_functionManager = nullptr;

}

QString StringParamProcesser::srcInfo() const
{
    return m_srcInfo;
}

void StringParamProcesser::setSrcInfo(const QString& srcInfo)
{
    m_srcInfo = srcInfo;
    getParams();

}

void StringParamProcesser::getParams()
{
    params.clear();
    QString s = m_srcInfo;
    int m = s.indexOf("${");
    int n = s.indexOf("}");
    while ((m >= 0) && (n >= 0))
    {
        QString v = s.mid(m + 2, n - m - 2);
        params << v;

        s = s.mid(n + 1);
        m = s.indexOf("${");
        n = s.indexOf("}");

    }
}

QString StringParamProcesser::getRandomDestInfo()
{

    QThread::msleep(1);
    QApplication::processEvents();
    QString s = m_srcInfo;
    for (QString p : params)
    {

        if ((m_functionManager == nullptr) || (m_functionManager->tryRun(p) == false))
        {
            QStringList stl;
            if (p.startsWith("@"))
            {
                emit stl = getCustomValues(p);
            }
            else
            {
                stl = paramValues[p];
            }

            if (stl.count() > 0)
            {
                QString t = "${" + p + "}";
                int k = s.indexOf(t);
                while (k >= 0)
                {
                    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
                    int n = qrand() % stl.count();
                    QString v = stl[n];
                    QString beforStr = s.left(k);
                    QString afterStr = s.mid(k + t.length());
                    qDebug() << beforStr;
                    qDebug() << afterStr;
                    s =  beforStr + v + afterStr;

                    k = s.indexOf(t);
                    QThread::msleep(10);

                }

            }
            else
            {
                s = s.replace("${" + p + "}", "");
            }
            QThread::msleep(1);
            QApplication::processEvents();

        }
        else
        {



            QString t = "${" + p + "}";
            int k = s.indexOf(t);
            while (k >= 0)
            {
                qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));

                QString v = m_functionManager->run(p);
                QString beforStr = s.left(k);
                QString afterStr = s.mid(k + t.length());
                qDebug() << beforStr;
                qDebug() << afterStr;
                s =  beforStr + v + afterStr;

                k = s.indexOf(t);
                QThread::msleep(10);

            }
        }



    }
    QThread::msleep(1);
    QApplication::processEvents();

    return s;
}

QString StringParamProcesser::getRandomValue(QString name)
{
    QThread::msleep(1);
    QApplication::processEvents();
    QString s;


    if ((m_functionManager == nullptr) || (m_functionManager->tryRun(name) == false))
    {
        QStringList stl;
        if (name.startsWith("@"))
        {
            emit stl = getCustomValues(name);
        }
        else
        {
            stl = paramValues[name];
        }
        if (stl.count() > 0)
        {

            qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
            int n = qrand() % stl.count();
            QString v = stl[n];
            s = v;


        }
        else
        {
            s = name;
        }
        QThread::msleep(1);
        QApplication::processEvents();

    }
    else
    {
        QString v = m_functionManager->run(name);
        s = v;
    }





    return s;
}

FunctionManager* StringParamProcesser::getFunctionManager() const
{
    return m_functionManager;
}

void StringParamProcesser::setFunctionManager(FunctionManager* functionManager)
{
    m_functionManager = functionManager;
}
