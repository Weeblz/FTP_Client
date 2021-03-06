#ifndef FTPPI_H
#define FTPPI_H

#include <QtCore>
#include <QTcpSocket>
#include <QDebug>
#include "qurlinfo.h"
#include "myftp.h"

class ftpPI;

// The ftpDTP (DTP = Data Transfer Process) controls all client side //
// data transfer between the client and server.                      //

class ftpDTP : public QObject {
    Q_OBJECT

public:
    enum ConnectState {
        CsHostFound,
        CsConnected,
        CsClosed,
        CsHostNotFound,
        CsConnectionRefused
    };

    ftpDTP(ftpPI *pi, QObject *parent = 0);
    //virtual ~ftpDTP();

    void connectToHost(const QString & host, quint16 port);
    //QTcpSocket::SocketState state() const;
    void abortConnection();

    static bool parseDir(const QByteArray& buffer, QUrlInfo& info);

signals:
    void listInfo(const QUrlInfo&);
    void connectState(ftpDTP::ConnectState);

private slots:
    void socketConnected();
    void socketReadyRead();
    //void socketError(QAbstractSocket::SocketError);
    void socketConnectionClosed();

private:
    QTcpSocket *socket = nullptr;
    ftpPI *pi = nullptr;
};

// ftpPI - Protocol Interpreter //

class ftpPI : public QObject {
    Q_OBJECT
    friend class FtpClient;
public:
    enum State {
        Begin,
        Idle,
        Waiting,
        Success,
        Failure
    };

    ftpPI(QObject *parent = 0);

    void connectToHost(const QString &host, quint16 port);

    bool sendCommands(const QStringList &cmds);
    bool sendCommand(const QString &cmd)
        { return sendCommands(QStringList(cmd)); }

    //void clearPendingCommands();
    void abort();

    QString currentCommand() const
        { return currentCmd; }

    //bool rawCommand;
    //bool transferConnectionExtended;

    ftpDTP dtp; // the PI has a DTP which is not the design of RFC 959, but it
                 // makes the design simpler this way
signals:
    void connectState(myFTP::State);
    void finished(bool);
    //void error(int, const QString&);
    //void rawFtpReply(int, const QString&);

private slots:
    void hostFound();
    void connected();
    void connectionClosed();
    //void delayedCloseFinished();
    void readyRead();
    //void error(QAbstractSocket::SocketError);

    void dtpConnectState(ftpDTP::ConnectState State);

private:
    // the states are modelled after the generalized state diagram of RFC 959,
    // page 58

    bool processReply();
    bool startNextCmd();

    QTcpSocket commandSocket;
    QString replyText;
    char replyCode[3];
    State state;
    //AbortState abortState;
    QStringList pendingCommands;
    QString currentCmd;

    bool waitForDtpToConnect = false;
    bool waitForDtpToClose = false;

    //QByteArray bytesFromSocket;

    friend class ftpDTP;
};

#endif
