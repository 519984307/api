#include "fnpinyin.h"

FnPinYin::FnPinYin(QObject* parent) : QObject(parent)
{

}

void FnPinYin::loadData()
{
    QFile file(":/res/json/pinyin.json");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonObject jobj = jdoc.object();
    QVariantMap jmap = jobj.toVariantMap();
    QVariantMap::iterator it = jmap.begin();
    for (; it != jmap.end(); it++)
    {
        QString s = it.key();
        s = getFirstLetter(s);
        QVariantList values = it.value().toList();
        for (const auto& v : qAsConst(values))
        {
            m_jianpins.insert(v.toString(), s);
        }
    }


    file.close();


}

QString FnPinYin::getJianPin(QString s)
{
    QString ret;
    for (int i = 0; i < s.length(); i++)
    {
        ret = ret + m_jianpins[s.at(i)];
    }
    return ret;
}

QString FnPinYin::getFirstLetter(QString s)
{
    if (s.length() == 0)
    {
        return "";
    }
    QString a = "āáǎà";
    QString o = "ōóǒò";
    QString e = "ēéěè";
    QString i = "īíǐì";
    QString u = "ūúǔù";
    QString v = "ǖǘǚǜ";
    QString p = s.left(1);
    if (a.indexOf(p) >= 0)
    {
        return "a";
    }
    else if (o.indexOf(p) >= 0)
    {
        return "o";
    }
    else if (e.indexOf(p) >= 0)
    {
        return "e";
    } if (i.indexOf(p) >= 0)
    {
        return "i";
    }
    if (u.indexOf(p) >= 0)
    {
        return "u";
    }
    if (v.indexOf(p) >= 0)
    {
        return "v";
    }
    else
    {
        return p;
    }


}

FnPinYin* fnPinyin()
{
    return FnPinYin::instance();

}
