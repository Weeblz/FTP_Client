/****************************************************************************
** Meta object code from reading C++ file 'myftp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/myftp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myftp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myFTP_t {
    QByteArrayData data[13];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myFTP_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myFTP_t qt_meta_stringdata_myFTP = {
    {
QT_MOC_LITERAL(0, 0, 5), // "myFTP"
QT_MOC_LITERAL(1, 6, 12), // "stateChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "myFTP::State"
QT_MOC_LITERAL(4, 33, 8), // "listInfo"
QT_MOC_LITERAL(5, 42, 8), // "QUrlInfo"
QT_MOC_LITERAL(6, 51, 9), // "readyRead"
QT_MOC_LITERAL(7, 61, 15), // "commandFinished"
QT_MOC_LITERAL(8, 77, 5), // "abort"
QT_MOC_LITERAL(9, 83, 16), // "startNextCommand"
QT_MOC_LITERAL(10, 100, 10), // "piFinished"
QT_MOC_LITERAL(11, 111, 5), // "error"
QT_MOC_LITERAL(12, 117, 14) // "piConnectState"

    },
    "myFTP\0stateChanged\0\0myFTP::State\0"
    "listInfo\0QUrlInfo\0readyRead\0commandFinished\0"
    "abort\0startNextCommand\0piFinished\0"
    "error\0piConnectState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myFTP[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,
       7,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   64,    2, 0x0a /* Public */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      12,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void myFTP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myFTP *_t = static_cast<myFTP *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< myFTP::State(*)>(_a[1]))); break;
        case 1: _t->listInfo((*reinterpret_cast< const QUrlInfo(*)>(_a[1]))); break;
        case 2: _t->readyRead(); break;
        case 3: _t->commandFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->abort(); break;
        case 5: _t->startNextCommand(); break;
        case 6: _t->piFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->piConnectState((*reinterpret_cast< myFTP::State(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myFTP::*_t)(myFTP::State );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myFTP::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myFTP::*_t)(const QUrlInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myFTP::listInfo)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (myFTP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myFTP::readyRead)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (myFTP::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myFTP::commandFinished)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject myFTP::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_myFTP.data,
      qt_meta_data_myFTP,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myFTP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myFTP::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myFTP.stringdata0))
        return static_cast<void*>(const_cast< myFTP*>(this));
    return QObject::qt_metacast(_clname);
}

int myFTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void myFTP::stateChanged(myFTP::State _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myFTP::listInfo(const QUrlInfo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void myFTP::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void myFTP::commandFinished(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
