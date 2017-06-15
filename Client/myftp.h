#ifndef MYFTP_H
#define MYFTP_H

#include <QtCore>
#include "qurlinfo.h"

class ftpPI;
class ftpCommand;

class myFTP : public QObject {
    Q_OBJECT
public:
    enum State {
        Unconnected,
        HostLookup,
        Connecting,
        Connected,
        LoggedIn,
        Closing
    };

    enum Command {
        ConnectToHost,
        Login,
        List,
        Cd,
        Close,
        None
    };

    myFTP(QObject* parent = nullptr);
    virtual ~myFTP();

    //OK
    void connectToHost(const QString &host, quint16 port=21);
    //OK
    void login(const QString &user = QString(), const QString &password = QString());
    //OK
    void close();
    //OK
    void list(const QString &dir = QString());
    //OK
    void cd(const QString &dir);

    //int rawCommand(const QString &command);

    //OK
    Command currentCommand() const;

private:
    //OK
    void addCommand(ftpCommand* cmd);

public slots:
    //OK
    void abort();

private slots:
    //OK
    void startNextCommand();
    //OK
    void piFinished(bool error);
    //OK
    void piConnectState(myFTP::State);

signals:
    void stateChanged(myFTP::State);
    void listInfo(const QUrlInfo&);
    void readyRead();
    void commandFinished(bool);

private:
    ftpPI* pi;
    QList<ftpCommand*> pendingCmds;

    State currentState;
};

class ftpCommand {
    friend class myFTP;
public:
    ftpCommand(myFTP::Command cmd, QStringList raw) : command(cmd), rawCmds(raw) {}
    //virtual ~ftpCommand();

    myFTP::Command command;
    QStringList rawCmds;
};

#endif // MYFTP_H
