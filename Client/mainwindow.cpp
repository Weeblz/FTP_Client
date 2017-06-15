#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QStringList>
#include <QInputDialog>
#include <QVariantList>


mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow),
    db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);

    ui->fileList->setColumnCount(4);
    ui->fileList->hideColumn(3);
    ui->fileList->sortByColumn(3);
    ui->fileList->setSortingEnabled(true);

    ui->toParent->setEnabled(false);
    ui->serverAdress->setText("mirrors.kernel.org");

    connect(ui->connectOrDisconnect, SIGNAL(clicked()),
            this, SLOT(connectOrDisconnect()));
    connect(ui->toParent, SIGNAL(clicked()),
            this, SLOT(cdToParent()));
    connect(ui->fileList, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
            this, SLOT(itemActivated(QTreeWidgetItem*, int)));

    setWindowIcon(QPixmap("/icons/cloud.svg"));
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::connectOrDisconnect() {
    if(!ftp_client) {
        connectToFtp();

        ui->connectOrDisconnect->setEnabled(false);
        ui->connectOrDisconnect->setText("Disconnect");

        QTimer::singleShot(2400, this, SLOT(connectionTimeout()));
    }
    else {
        disconnectFromFtp();

        ui->fileList->clear();
        ui->fileList->setEnabled(true);
        ui->connectOrDisconnect->setEnabled(true);
        ui->connectOrDisconnect->setText("Connect");

        items.clear();
    }
}

void mainwindow::connectToFtp() {
    ftp_client = new myFTP(this);

    connect(ftp_client, SIGNAL(commandFinished(bool)),
            this, SLOT(ftpCommandFinished(bool)));
    connect(ftp_client, SIGNAL(listInfo(QUrlInfo)),
            this, SLOT(addToList(QUrlInfo)));

    ftp_client->connectToHost(ui->serverAdress->text());
    ftp_client->login();

    if(db.isOpen()) {
        db.close();
    }
    db.setDatabaseName(ui->serverAdress->text());

    if(!db.open()) {
        qDebug() << db.lastError().text();
    }
}

void mainwindow::disconnectFromFtp() {
    ftp_client->abort();
    ftp_client->deleteLater();
    ftp_client = nullptr;

    connected = false;
}

void mainwindow::ftpCommandFinished(bool error) {
    auto command = ftp_client->currentCommand();
    if(command == myFTP::Command::ConnectToHost) {
        if(error) {
            QMessageBox::information(this, "FTP connection",
                                     tr("Unable to connect to FTP server "
                                        "with adress %1.")
                                     .arg(ui->serverAdress->text()));
            connectOrDisconnect();
            return;
        }
        ui->fileList->setFocus();
        ui->connectOrDisconnect->setEnabled(true);

        connected = true;

        //QSqlQuery authentication;
        //authentication.prepare("EXEC dbo.AuthenticateHost @HostName = ?;");
        //authentication.addBindValue(ui->ftpServerAddress->text());
        //if(!authentication.exec()) {
        //    qDebug() << db.lastError().text();
        //} else if(authentication.next()) {
        //    host_id = authentication.value(0).toInt();
        //}
    }
    else if(command == myFTP::Command::Login) {
        directory_id = 1;
        ftp_client->list();
    }
    else if(command == myFTP::Command::List) {
        QStringList item_names = items.keys();
        QString insert;
        if(!item_names.empty()) {
            insert = "INSERT INTO @CurrentDirectory(ItemName)"
                     "   VALUES ('" + item_names.join("'), ('") + "'); ";
        }   // insert security check required
        //QSqlQuery sync_directory;
        //sync_directory.prepare
        //        (
        //            "DECLARE @CurrentDirectory DirectoryShortcut; "
        //            + insert +
        //            "EXEC SyncDirectories @HostID = ?, @DirectoryID = ?, @Directory = @CurrentDirectory;"
        //            );
        //sync_directory.addBindValue(host_id);
        //sync_directory.addBindValue(directory_id);
        //if(!sync_directory.exec()) {
        //    qDebug() << sync_directory.lastError().text();
        //}
        //while(sync_directory.next()) {
        //   QString item_name = sync_directory.value("ItemName").toString();
        //    items[item_name].SetId(sync_directory.value("ItemID").toInt());
        //    ui->fileList
        //            ->findItems(item_name, Qt::MatchExactly, 0).first()
        //            ->setText(2, sync_directory.value("ItemComment").toString());
        //
        // }
        if(items.isEmpty()) {
            ui->fileList->addTopLevelItem(new QTreeWidgetItem(QStringList() << tr("<empty>")));
            ui->fileList->setEnabled(false);
        }
    }
}

void mainwindow::addToList(const QUrlInfo &urlInfo) {
    QTreeWidgetItem* tree_item = new QTreeWidgetItem;

    tree_item->setText(0, urlInfo.name());
    tree_item->setText(1, QString::number(urlInfo.size()));
    tree_item->setText(3, urlInfo.isDir() ? "B" : "A" + urlInfo.name());
    QString extension = urlInfo.name().mid(urlInfo.name().lastIndexOf('.') + 1);
    QString icon_path = urlInfo.isDir() ? "/icons/folder.svg" : "/icons/file.svg";
    QPixmap icon(icon_path);
    tree_item->setIcon(0, icon);

    items[urlInfo.name()] = urlInfo.isDir();
    ui->fileList->addTopLevelItem(tree_item);
    if(!ui->fileList->currentItem())
    {
        ui->fileList->setCurrentItem(ui->fileList->topLevelItem(0));
        ui->fileList->setEnabled(true);
    }
}
void mainwindow::itemActivated(QTreeWidgetItem* tree_item, int column) {
    QString item_name = tree_item->text(0);
    if(column == 2) {
        QString comment = QInputDialog::getMultiLineText(this, "Comment",
                                                         "Put your comment here:",
                                                         tree_item->text(column));
        tree_item->setText(column, comment);
//        QSqlQuery update_comment;
//        update_comment.prepare("EXEC UpdateItemComment @HostID = ?, @ItemID = ?, @ItemComment = ?;");
//        update_comment.addBindValue(host_id);
//        update_comment.addBindValue(items.value(item_name).GetId());
//        update_comment.addBindValue(comment);
//        update_comment.exec();
    }
    else {
        if(items.value(item_name).isDir()) {
            directory_id = items.value(item_name).GetId();

            ui->fileList->clear();
            items.clear();

            current_path.append("/" + item_name);
            directory_ids.push_back(directory_id);

            ftp_client->cd(item_name);
            ftp_client->list();
            ui->toParent->setEnabled(true);
        }
    }
}

void mainwindow::cdToParent() {
    if(!connected) { return; }

    ui->fileList->clear();
    current_path = current_path.left(current_path.lastIndexOf('/'));
    if (current_path.isEmpty()) {
        ui->toParent->setEnabled(false);
        ftp_client->cd("/");
    } else {
        ftp_client->cd(current_path);
    }
    ftp_client->list();
}

void mainwindow::connectionTimeout() {
    if(!connected) {
        connectOrDisconnect();
    }
}
