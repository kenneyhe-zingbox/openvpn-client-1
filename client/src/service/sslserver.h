/*
Logserver  Project

*/

#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QtCore>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QSslSocket>

#include "sslconnections.h"

class SslServer : public QTcpServer
{
    Q_OBJECT
public:
    SslServer(quint16 port, QObject *parent = 0);
    ~SslServer ();
    SslConnections *connectionsList () const;

private:
    void incomingConnection (int socketDescriptor);
    SslConnections *connections;

private slots:
    void slotThreadFinished ();
    void slotQuitThread ();

signals:
    void setDisconnected (int id);
    void setError (int id, QString message);
    void needUserInput (int id, int type);
    void receivedDummy ();
    void receivedIP (int id, QString ip);
    void receivedReconnect (int id);
    void receivedTapControl (int type);
    void receivedRemoveTap (QString state);
    void receivedStatus (int id, bool isConnected, bool isConnecting, int lastAction, QString ip);
    void receivedTapCount(int count);
};

#endif // SSLSERVER_H
