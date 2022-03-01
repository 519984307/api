#ifndef SOCKETHELP_H
#define SOCKETHELP_H

#include <QObject>
#include <QTcpSocket>
#include <QApplication>
#include <QFile>

void socketWrite(QTcpSocket* socket, QString s);
void socketWriteEnd(QTcpSocket* socket);
int socketWriteFile(QTcpSocket* socket, QString pathName);
QString socketReadLine(QTcpSocket* socket);

#endif // SOCKETHELP_H
