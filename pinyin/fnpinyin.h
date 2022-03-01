#ifndef FNPINYIN_H
#define FNPINYIN_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <memory>
using namespace std;

class FnPinYin : public QObject
{
    Q_OBJECT
public:
    explicit FnPinYin(QObject* parent = nullptr);
    void loadData();
    QString getJianPin(QString s);
    static FnPinYin* instance()
    {
        static shared_ptr<FnPinYin>  _instance = nullptr;
        if (_instance == nullptr)
        {
            _instance = make_shared<FnPinYin>(new FnPinYin(nullptr));
            _instance->loadData();
        }
        return _instance.get();

    }
private:
    QMap<QString, QString> m_jianpins;
    QString getFirstLetter(QString s);
signals:

};
FnPinYin* fnPinyin();

#endif // FNPINYIN_H
