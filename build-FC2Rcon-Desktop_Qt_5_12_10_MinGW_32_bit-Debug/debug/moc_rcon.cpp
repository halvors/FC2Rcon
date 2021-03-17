/****************************************************************************
** Meta object code from reading C++ file 'rcon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FC2Rcon/rcon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rcon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_rcon_t {
    QByteArrayData data[8];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rcon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rcon_t qt_meta_stringdata_rcon = {
    {
QT_MOC_LITERAL(0, 0, 4), // "rcon"
QT_MOC_LITERAL(1, 5, 22), // "startFC2ServerInstance"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "errorOccurred"
QT_MOC_LITERAL(4, 43, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(5, 66, 5), // "error"
QT_MOC_LITERAL(6, 72, 9), // "readyRead"
QT_MOC_LITERAL(7, 82, 13) // "newConnection"

    },
    "rcon\0startFC2ServerInstance\0\0errorOccurred\0"
    "QProcess::ProcessError\0error\0readyRead\0"
    "newConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rcon[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       6,    0,   38,    2, 0x08 /* Private */,
       7,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void rcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rcon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->startFC2ServerInstance();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->errorOccurred((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 2: _t->readyRead(); break;
        case 3: _t->newConnection(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject rcon::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_rcon.data,
    qt_meta_data_rcon,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rcon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rcon.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int rcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
