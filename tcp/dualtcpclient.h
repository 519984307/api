#ifndef DUALTCPCLIENT_H
#define DUALTCPCLIENT_H

#include <QDebug>
#include <QObject>

class DualTcpClient : public QObject {
    Q_OBJECT
public:
    explicit DualTcpClient(QObject* parent = nullptr);
    ~DualTcpClient();
signals:
};

#endif // DUALTCPCLIENT_H
