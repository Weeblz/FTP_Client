/****************************************************************************
** Meta object code from reading C++ file 'FtpCore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/FtpCore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FtpCore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ftpDTP_t {
    QByteArrayData data[9];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ftpDTP_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ftpDTP_t qt_meta_stringdata_ftpDTP = {
    {
QT_MOC_LITERAL(0, 0, 6), // "ftpDTP"
QT_MOC_LITERAL(1, 7, 8), // "listInfo"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "QUrlInfo"
QT_MOC_LITERAL(4, 26, 12), // "connectState"
QT_MOC_LITERAL(5, 39, 12), // "ConnectState"
QT_MOC_LITERAL(6, 52, 15), // "socketConnected"
QT_MOC_LITERAL(7, 68, 15), // "socketReadyRead"
QT_MOC_LITERAL(8, 84, 22) // "socketConnectionClosed"

    },
    "ftpDTP\0listInfo\0\0QUrlInfo\0connectState\0"
    "ConnectState\0socketConnected\0"
    "socketReadyRead\0socketConnectionClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ftpDTP[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ftpDTP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ftpDTP *_t = static_cast<ftpDTP *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->listInfo((*reinterpret_cast< const QUrlInfo(*)>(_a[1]))); break;
        case 1: _t->connectState((*reinterpret_cast< ConnectState(*)>(_a[1]))); break;
        case 2: _t->socketConnected(); break;
        case 3: _t->socketReadyRead(); break;
        case 4: _t->socketConnectionClosed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ftpDTP::*_t)(const QUrlInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ftpDTP::listInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ftpDTP::*_t)(ConnectState );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ftpDTP::connectState)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ftpDTP::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ftpDTP.data,
      qt_meta_data_ftpDTP,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ftpDTP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ftpDTP::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ftpDTP.stringdata0))
        return static_cast<void*>(const_cast< ftpDTP*>(this));
    return QObject::qt_metacast(_clname);
}

int ftpDTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ftpDTP::listInfo(const QUrlInfo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ftpDTP::connectState(ConnectState _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_ftpPI_t {
    QByteArrayData data[13];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ftpPI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ftpPI_t qt_meta_stringdata_ftpPI = {
    {
QT_MOC_LITERAL(0, 0, 5), // "ftpPI"
QT_MOC_LITERAL(1, 6, 12), // "connectState"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "finished"
QT_MOC_LITERAL(4, 29, 5), // "error"
QT_MOC_LITERAL(5, 35, 11), // "rawFtpReply"
QT_MOC_LITERAL(6, 47, 9), // "hostFound"
QT_MOC_LITERAL(7, 57, 9), // "connected"
QT_MOC_LITERAL(8, 67, 16), // "connectionClosed"
QT_MOC_LITERAL(9, 84, 9), // "readyRead"
QT_MOC_LITERAL(10, 94, 15), // "dtpConnectState"
QT_MOC_LITERAL(11, 110, 20), // "ftpDTP::ConnectState"
QT_MOC_LITERAL(12, 131, 5) // "State"

    },
    "ftpPI\0connectState\0\0finished\0error\0"
    "rawFtpReply\0hostFound\0connected\0"
    "connectionClosed\0readyRead\0dtpConnectState\0"
    "ftpDTP::ConnectState\0State"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ftpPI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       4,    2,   65,    2, 0x06 /* Public */,
       5,    2,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   75,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void ftpPI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ftpPI *_t = static_cast<ftpPI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->rawFtpReply((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->hostFound(); break;
        case 5: _t->connected(); break;
        case 6: _t->connectionClosed(); break;
        case 7: _t->readyRead(); break;
        case 8: _t->dtpConnectState((*reinterpret_cast< ftpDTP::ConnectState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ftpPI::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ftpPI::connectState)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ftpPI::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ftpPI::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ftpPI::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ftpPI::error)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ftpPI::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ftpPI::rawFtpReply)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ftpPI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ftpPI.data,
      qt_meta_data_ftpPI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ftpPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ftpPI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ftpPI.stringdata0))
        return static_cast<void*>(const_cast< ftpPI*>(this));
    return QObject::qt_metacast(_clname);
}

int ftpPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ftpPI::connectState(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ftpPI::finished(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ftpPI::error(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ftpPI::rawFtpReply(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
