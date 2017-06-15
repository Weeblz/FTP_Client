#include "myftp.h"
#include "FtpCore.h"

myFTP::myFTP(QObject *parent)
    : QObject{ parent }, pi{ new ftpPI(this) }
{
    connect(pi, SIGNAL(connectState(myFTP::State)),
            SLOT(piConnectState(myFTP::State)));
    connect(pi, SIGNAL(finished(bool)),
                this, SLOT(piFinished(bool)));

    connect(&pi->dtp, SIGNAL(listInfo(QUrlInfo)),
            this, SIGNAL(listInfo(QUrlInfo)));
}

myFTP::~myFTP() {
    abort();
    close();

    while(!pendingCmds.empty()) {
        delete pendingCmds.takeFirst();
    }

    pi->abort();
}

void myFTP::addCommand(ftpCommand* cmd) {
    pendingCmds.append(cmd);
    if(pendingCmds.count() == 1) {
        startNextCommand();
    }
}

void myFTP::connectToHost(const QString& host, quint16 port) {
    QStringList cmds;
    cmds << host;
    cmds << QString::number((uint)port);

    addCommand(new ftpCommand(Command::ConnectToHost, cmds));
}

void myFTP::login(const QString& user, const QString& password) {
    QStringList cmds;
    cmds << (QLatin1String("USER ") + (user.isNull() ? QLatin1String("anonymous") : user) + QLatin1String("\r\n"));
    cmds << (QLatin1String("PASS ") + (password.isNull() ? QLatin1String("anonymous@") : password) + QLatin1String("\r\n"));

    addCommand(new ftpCommand(Login, cmds));
}

void myFTP::close() {
    addCommand(new ftpCommand(Close, QStringList("QUIT \r\n")));
}

void myFTP::list(const QString &dir) {
    QStringList cmds;
    cmds << "TYPE A\r\n";
    cmds << "PASV\r\n";

    dir.isEmpty() ? cmds << "LIST\r\n" : cmds << ("LIST " + dir + "\r\n");

    addCommand(new ftpCommand(Command::List, cmds));
}

void myFTP::cd(const QString &dir) {
    addCommand(new ftpCommand(Cd, QStringList("CWD " + dir + "\r\n")));
}

myFTP::Command myFTP::currentCommand() const{
    return pendingCmds.empty() ? None : pendingCmds.first()->command;
}

//SLOTS

void myFTP::abort() {
    if(pendingCmds.empty()) {
        return;
    }

    while(!pendingCmds.empty()) {
        delete pendingCmds.takeLast();
    }

    pi->abort();
}

void myFTP::startNextCommand() {
    if(pendingCmds.empty()){
        return;
    }

    ftpCommand* cmd = pendingCmds.first();

    if(cmd->command == ConnectToHost) {
        pi->connectToHost(cmd->rawCmds[0], cmd->rawCmds[1].toUInt());
    } else {
        if(cmd->command == Close) {
            currentState = State::Closing;
            emit stateChanged(currentState);
        }
        pi->sendCommands(cmd->rawCmds);
    }
}

void myFTP::piFinished(bool error) {
    if (pendingCmds.isEmpty()) {
            return;
    }
    ftpCommand *c = pendingCmds.first();

    if (c->command == Close) {
        if (currentState != Unconnected) {
            return;
        }
    }
    emit commandFinished(error);
    pendingCmds.removeFirst();

    delete c;

    if (!pendingCmds.isEmpty()) {
        startNextCommand();
    }
}

void myFTP::piConnectState(State cState) {
    currentState = cState;
    emit stateChanged(currentState);
}
