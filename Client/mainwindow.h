#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTreeWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "myftp.h"

class ItemInfo
{
    int id;
    bool is_dir;

public:
    ItemInfo() = default;
    ItemInfo(bool _is_dir)
        : is_dir{ _is_dir }
    {
    }

public:
    void SetId(int _id)
        { id = _id;      }
    int GetId() const
        { return id;     }
    bool isDir() const
        { return is_dir; }
};

namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

private:
    Ui::mainwindow *ui;
    myFTP* ftp_client   = nullptr;
    bool connected      = false;            // used for connection timeouts checking

    QHash<QString, ItemInfo> items;         // containes all item names for the current directory
                                            // holds true if item is directory - false otherwise
                                            // empty if no items in current directory

    QString current_path;               // a list of current path tokens
    QVector<int> directory_ids;             // a list of ids corresponding to the current_path list

    int host_id = 0;
    int directory_id = 1;
    QSqlDatabase db;

private slots:
    void connectOrDisconnect();

    void connectToFtp();
    void disconnectFromFtp();

    void ftpCommandFinished(bool error);
    void addToList(const QUrlInfo &urlInfo);
    void itemActivated(QTreeWidgetItem*, int);
    void cdToParent();
    void connectionTimeout();
};

#endif // MAINWINDOW_H
