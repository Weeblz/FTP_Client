#include "FtpCore.h"
#include "myftp.h"

ftpPI::ftpPI(QObject* parent)
    : QObject{ parent },
      dtp{ this },
      commandSocket{ 0 }

{
    commandSocket.setObjectName("FTP_Protocol_Iterpreter_socket");
    connect(&commandSocket, SIGNAL(hostFound()), this, SLOT(hostFound()));
    connect(&commandSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(&commandSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&commandSocket, SIGNAL(disconnected()), this, SLOT(connectionClosed()));

    connect(&dtp, SIGNAL(connectState(ftpDTP::ConnectState)),
            this, SLOT(dtpConnectState(ftpDTP::ConnectState)));
}

void ftpPI::hostFound()
{
    emit connectState(myFTP::State::Connecting);
}

void ftpPI::connected()
{
    state = State::Begin;
    emit connectState(myFTP::State::Connected);
}

void ftpPI::readyRead()
{
    if(waitForDtpToConnect) {qDebug()<<"asd\n";return;}
    while(commandSocket.canReadLine())
    {
        QString line = commandSocket.readLine();

        for (int i=0; i<3; i++) {
            replyCode[i] = line[i].digitValue();
        }

        QString multiline_end;
        multiline_end[0] = '0' + replyCode[0];
        multiline_end[1] = '0' + replyCode[1];
        multiline_end[2] = '0' + replyCode[2];
        multiline_end[3] = QLatin1Char(' ');

        QString multiline_beg(multiline_end);
        multiline_beg[3] = QLatin1Char('-');

        QString line_beg = line.left(4);
        while (line_beg != multiline_end)
        {
            if (line_beg == multiline_beg) {
                replyText += line.mid(4); // strip multiline beginning "xxx-"
            } else {
                replyText += line;
            }
            if (!commandSocket.canReadLine()) {
                return;
            }
            line = QString::fromLatin1(commandSocket.readLine());
            line_beg = line.left(4);
        }
        replyText += line.mid(4); // strip multiline end "xxx "
        if (replyText.endsWith(QLatin1String("\r\n")))
            replyText.chop(2);
        if (processReply())
            replyText.clear();
    }
}

void ftpPI::connectionClosed()
{
    commandSocket.close();
    emit connectState(myFTP::State::Unconnected);
}

void ftpPI::dtpConnectState(ftpDTP::ConnectState state)
{
    typedef ftpDTP::ConnectState DTP_Connection;
    switch (state)
    {
    case DTP_Connection::CsClosed:
        if(waitForDtpToClose)
        {
            // flush some any unprocessed replies
            if(processReply()) {
                replyText.clear();
            } else {
                return;
            }
        }
        waitForDtpToClose = false;
        readyRead();
        return;
    case DTP_Connection::CsConnected:
        waitForDtpToConnect = false;
        startNextCmd();
        return;
    case DTP_Connection::CsHostNotFound:
    case DTP_Connection::CsConnectionRefused:
        qDebug() << "DTP: cannot connect to the host.";
        startNextCmd();
        return;
    default:
        return;
    }
}

void ftpPI::connectToHost(const QString& address, quint16 port)
{
    emit connectState(myFTP::State::HostLookup);
    commandSocket.connectToHost(address, port);
}

void ftpPI::abort()
{
    pendingCommands.clear();

    // NOTE: ABOR may be already sent
    commandSocket.write("ABOR\r\n", 6);
}

// if there are pending commands return false
// and adds nothing
// return true otherwise
bool ftpPI::sendCommands(const QStringList& cmds)
{
    if(!pendingCommands.empty()){
        return false;
    }

    if(commandSocket.state() != QTcpSocket::ConnectedState){
        qDebug() << "Can not send commands. Please, try again.";
        return true;
    }

    pendingCommands = cmds;
    startNextCmd();
    return true;
}

bool ftpPI::processReply()
{
    static const State states[5] =
    {
        State::Waiting,             // 1xx
        State::Success,             // 2xx
        State::Idle,                // 3xx
        State::Failure,             // 4xx
        State::Failure              // 5xx
    };

    switch(state)
    {
        case State::Begin:
            if(replyCode[0] == 1) return true;
            if(replyCode[1] == 2)
            {
                state = State::Idle;
                emit finished(false);   // TODO
                break;
            }
            else return true;
        case State::Waiting:
            state = states[replyCode[0] - 1];
            break;
        default:
            // ignore all messages in state other then Begin or Wait
            return true;
    }

    int code = replyCode[0] * 100 + replyCode[1] * 10 + replyCode[2];

#ifdef _DEBUG
    qDebug() << code << replyText;
#endif

    if(code == 227)
    {
       // => Entering Passive Mode (h1,h2,h3,h4,p1,p2).
       QRegExp full_address_pattern("(\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+)");
       if(full_address_pattern.indexIn(replyText) == -1) {
           qDebug() << "No host address for TDP received";
       } else {
           QStringList full_address = full_address_pattern.capturedTexts();
           QString address =
                   full_address[1] + '.' +
                   full_address[2] + '.' +
                   full_address[3] + '.' +
                   full_address[4];
           quint16 port = (full_address[5].toUInt() << 8) + full_address[6].toUInt();

           waitForDtpToConnect = true;
           dtp.connectToHost(address, port);
       }
    }

    // => Handle a new state
    if(state == State::Success){
        state = State::Idle;
    }
    if (state == State::Idle) {
        startNextCmd();
    }
    return true;
}

// return false if there are now pending commands
// return true otherwise
bool ftpPI::startNextCmd()
{
    if(waitForDtpToConnect) {
        return true;
    }

    // if there is nothing to process
    if(pendingCommands.empty())
    {
        currentCmd.clear();
        emit finished(false);               // TODO
        return false;
    }

    currentCmd = pendingCommands.takeFirst();

    state = State::Waiting;
    commandSocket.write(currentCmd.toLatin1());

    return true;
}

ftpDTP::ftpDTP(ftpPI* _pi, QObject* parent)
    : QObject{ parent },
      socket{ 0 },
      pi{ _pi }
{
}

void ftpDTP::socketConnected()
{
    emit connectState(ConnectState::CsConnected);
}

void ftpDTP::socketReadyRead()
{
    if(socket == nullptr) {
        return;
    }

    // if no commands processed by PI
    // close data channel
    if(pi->currentCommand().isEmpty())
    {
        socket->close();
        emit connectState(ftpDTP::ConnectState::CsClosed);
        return;
    }

    // process appropriate command
    if(pi->currentCommand().startsWith("LIST"))
    {
        while(socket->canReadLine())
        {
            QUrlInfo dir_info;
            QByteArray line_buffer = socket->readLine();
            if(parseDir(line_buffer, dir_info)) {
                emit listInfo(dir_info);
            }
        }
    }


}

void ftpDTP::socketConnectionClosed() {
    emit connectState(ConnectState::CsClosed);
}

void ftpDTP::connectToHost(const QString& address, quint16 port) {
    if(socket != nullptr) {
        delete socket;
        socket = nullptr;
    }
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketConnectionClosed()));

    socket->connectToHost(address, port);
}


void ftpDTP::abortConnection() {
    if(socket != nullptr) {
        socket->abort();
    }
}


static void parseUnixDir(const QStringList& tokens, QUrlInfo& dir_info)
{

    // ** Taken from Qt 4.8
    // Unix style, 7 + 1 entries
    // -rw-r--r--    1 ftp      ftp      17358091 Aug 10  2004 qt-x11-free-3.3.3.tar.gz
    // drwxr-xr-x    3 ftp      ftp          4096 Apr 14  2000 compiled-examples
    // lrwxrwxrwx    1 ftp      ftp             9 Oct 29  2005 qtscape -> qtmozilla
    if (tokens.size() != 8)
        return;

    char first = tokens.at(1).at(0).toLatin1();
    if (first == 'd') {
        dir_info.setDir(true);
        dir_info.setFile(false);
        dir_info.setSymLink(false);
    } else if (first == '-') {
        dir_info.setDir(false);
        dir_info.setFile(true);
        dir_info.setSymLink(false);
    } else if (first == 'l') {
        dir_info.setDir(true);
        dir_info.setFile(false);
        dir_info.setSymLink(true);
    }

    // Resolve filename
    QString name = tokens.at(7);
    if (dir_info.isSymLink()) {
        int linkPos = name.indexOf(QLatin1String(" ->"));
        if (linkPos != -1)
            name.resize(linkPos);
    }
    dir_info.setName(name);

    // Resolve owner & group
    dir_info.setOwner(tokens.at(3));
    dir_info.setGroup(tokens.at(4));

    // Resolve size
    dir_info.setSize(tokens.at(5).toLongLong());

    QStringList formats;
    formats << QLatin1String("MMM dd  yyyy") << QLatin1String("MMM dd hh:mm") << QLatin1String("MMM  d  yyyy")
            << QLatin1String("MMM  d hh:mm") << QLatin1String("MMM  d yyyy") << QLatin1String("MMM dd yyyy");

    QString dateString = tokens.at(6);
    dateString[0] = dateString[0].toUpper();

    // Resolve the modification date by parsing all possible formats
    QDateTime dateTime;
    int n = 0;
    do {
        dateTime = QLocale::c().toDateTime(dateString, formats.at(n++));
    }  while (n < formats.size() && (!dateTime.isValid()));

    if (n == 2 || n == 4) {
        // Guess the year.
        dateTime.setDate(QDate(QDate::currentDate().year(),
                               dateTime.date().month(),
                               dateTime.date().day()));
    }
    if (dateTime.isValid())
        dir_info.setLastModified(dateTime);

    // Resolve permissions
    int permissions = 0;
    QString p = tokens.at(2);
    permissions |= (p[0] == QLatin1Char('r') ? QUrlInfo::ReadOwner : 0);
    permissions |= (p[1] == QLatin1Char('w') ? QUrlInfo::WriteOwner : 0);
    permissions |= (p[2] == QLatin1Char('x') ? QUrlInfo::ExeOwner : 0);
    permissions |= (p[3] == QLatin1Char('r') ? QUrlInfo::ReadGroup : 0);
    permissions |= (p[4] == QLatin1Char('w') ? QUrlInfo::WriteGroup : 0);
    permissions |= (p[5] == QLatin1Char('x') ? QUrlInfo::ExeGroup : 0);
    permissions |= (p[6] == QLatin1Char('r') ? QUrlInfo::ReadOther : 0);
    permissions |= (p[7] == QLatin1Char('w') ? QUrlInfo::WriteOther : 0);
    permissions |= (p[8] == QLatin1Char('x') ? QUrlInfo::ExeOther : 0);
    dir_info.setPermissions(permissions);

    dir_info.setReadable(true);
    dir_info.setWritable(dir_info.isFile());
}

static void parseDosDir(const QStringList& tokens, QUrlInfo& dir_info)
{

    // ** Taken from Qt 4.8
    // DOS style, 3 + 1 entries
    // 01-16-02  11:14AM       <DIR>          epsgroup
    // 06-05-03  03:19PM                 1973 readme.txt
    if (tokens.size() != 4)
        return;

    QString name = tokens.at(3);
    dir_info.setName(name);
    dir_info.setSymLink(name.toLower().endsWith(".lnk"));

    if (tokens.at(2) == "<DIR>") {
        dir_info.setFile(false);
        dir_info.setDir(true);
    } else {
        dir_info.setFile(true);
        dir_info.setDir(false);
        dir_info.setSize(tokens.at(2).toLongLong());
    }

    // Note: We cannot use QFileInfo; permissions are for the server-side
    // machine, and QFileInfo's behavior depends on the local platform.
    int permissions = QUrlInfo::ReadOwner | QUrlInfo::WriteOwner
                      | QUrlInfo::ReadGroup | QUrlInfo::WriteGroup
                      | QUrlInfo::ReadOther | QUrlInfo::WriteOther;
    QString extension;
    int extension_index = name.lastIndexOf('.');
    if (extension_index != -1)
        extension = name.mid(extension_index + 1);
    if (extension == "exe" || extension == "bat" || extension == "com")
        permissions |= QUrlInfo::ExeOwner | QUrlInfo::ExeGroup | QUrlInfo::ExeOther;
    dir_info.setPermissions(permissions);

    dir_info.setReadable(true);
    dir_info.setWritable(dir_info.isFile());

    QDateTime date_time;
    date_time = QLocale::c().toDateTime(tokens.at(1), "MM-dd-yy  hh:mmAP");
    dir_info.setLastModified(date_time);
}


bool ftpDTP::parseDir(const QByteArray& buffer, QUrlInfo& dir_info)
{

    if(buffer.isEmpty()){
        return false;
    }

    QString string_buffer = QString(buffer).trimmed();

#ifdef _DEBUG
    qDebug() << "           " << string_buffer;
#endif

    // Unix style listing on FTP servers
    QRegExp unix_listing_pattern("^([\\-dl])([a-zA-Z\\-]{9,9})\\s+\\d+\\s+(\\S*)\\s+"
                                          "(\\S*)\\s+(\\d+)\\s+(\\S+\\s+\\S+\\s+\\S+)\\s+(\\S.*)");

    if(unix_listing_pattern.indexIn(string_buffer) == 0)
    {
        parseUnixDir(unix_listing_pattern.capturedTexts(), dir_info);
        return true;
    }

    // DOS style listing on FTP server
    QRegExp dos_listing_pattern("^(\\d\\d-\\d\\d-\\d\\d\\d?\\d?\\ \\ \\d\\d:\\d\\d[AP]M)\\s+"
                                     "(<DIR>|\\d+)\\s+(\\S.*)$");

    if(dos_listing_pattern.indexIn(string_buffer) == 0)
    {
        parseDosDir(dos_listing_pattern.capturedTexts(), dir_info);
        return true;
    }

    // directory representation format is unsupported
    return false;
}
