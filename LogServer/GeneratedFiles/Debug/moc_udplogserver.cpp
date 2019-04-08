/****************************************************************************
** Meta object code from reading C++ file 'udplogserver.h'
**
** Created: Mon Feb 25 16:24:51 2019
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../udplogserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udplogserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UDPLogServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   14,   13,   13, 0x05,
      70,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     114,   13,   13,   13, 0x0a,
     132,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UDPLogServer[] = {
    "UDPLogServer\0\0message,level\0"
    "signalSendMessageToRealTimeDia(char*,int)\0"
    "signalSendMessageToRealTimeDia(QString,int)\0"
    "slotChileThread()\0slotReSetSQLDelete(int)\0"
};

void UDPLogServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UDPLogServer *_t = static_cast<UDPLogServer *>(_o);
        switch (_id) {
        case 0: _t->signalSendMessageToRealTimeDia((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalSendMessageToRealTimeDia((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotChileThread(); break;
        case 3: _t->slotReSetSQLDelete((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UDPLogServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UDPLogServer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UDPLogServer,
      qt_meta_data_UDPLogServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UDPLogServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UDPLogServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UDPLogServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UDPLogServer))
        return static_cast<void*>(const_cast< UDPLogServer*>(this));
    return QThread::qt_metacast(_clname);
}

int UDPLogServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void UDPLogServer::signalSendMessageToRealTimeDia(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UDPLogServer::signalSendMessageToRealTimeDia(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
