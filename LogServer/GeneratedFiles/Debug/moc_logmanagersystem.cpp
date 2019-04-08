/****************************************************************************
** Meta object code from reading C++ file 'logmanagersystem.h'
**
** Created: Mon Feb 25 09:54:37 2019
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../logmanagersystem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logmanagersystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogManagerSystem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      35,   17,   17,   17, 0x05,
      66,   17,   17,   17, 0x05,
      90,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     114,   17,   17,   17, 0x08,
     132,   17,   17,   17, 0x08,
     158,   17,   17,   17, 0x08,
     171,   17,   17,   17, 0x08,
     184,   17,   17,   17, 0x08,
     199,   17,   17,   17, 0x08,
     217,   17,   17,   17, 0x08,
     232,   17,   17,   17, 0x08,
     253,  247,   17,   17, 0x08,
     276,   17,   17,   17, 0x08,
     305,   17,   17,   17, 0x08,
     332,   17,   17,   17, 0x08,
     355,   17,   17,   17, 0x08,
     384,   17,   17,   17, 0x08,
     414,  408,   17,   17, 0x08,
     442,   17,   17,   17, 0x28,
     467,  408,   17,   17, 0x08,
     495,   17,   17,   17, 0x28,
     520,   17,   17,   17, 0x08,
     539,   17,   17,   17, 0x08,
     559,   17,   17,   17, 0x08,
     580,   17,   17,   17, 0x08,
     599,   17,   17,   17, 0x08,
     620,   17,   17,   17, 0x08,
     640,   17,   17,   17, 0x08,
     663,   17,   17,   17, 0x08,
     677,   17,   17,   17, 0x08,
     697,   17,   17,   17, 0x08,
     720,   17,   17,   17, 0x08,
     745,   17,   17,   17, 0x08,
     769,   17,   17,   17, 0x08,
     787,   17,   17,   17, 0x08,
     808,   17,   17,   17, 0x08,
     827,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LogManagerSystem[] = {
    "LogManagerSystem\0\0sigStartThread()\0"
    "signalComboBoxToClearTime(int)\0"
    "signalResetSaveDay(int)\0signalStartAutoUpDate()\0"
    "slotButtonClear()\0slotSelectDateChange(int)\0"
    "slotUpDate()\0slotUpPage()\0slotDownPage()\0"
    "slotGotoPage(int)\0slotHeadPage()\0"
    "slotTailPage()\0state\0slotCheckBoxDebug(int)\0"
    "slotSpinboxResetSaveDay(int)\0"
    "slotSearchGotoSomeday(int)\0"
    "slotOnRealtimeDialog()\0"
    "slotSetCloseRealTimeDialog()\0"
    "slotOpenSettingDialog()\0index\0"
    "slotSetStackWidgetFist(int)\0"
    "slotSetStackWidgetFist()\0"
    "slotSetStackWidgetNext(int)\0"
    "slotSetStackWidgetNext()\0slotONAutoUpDate()\0"
    "slotShowLevelMenu()\0slotShowSelectDays()\0"
    "slotSelectOneDay()\0slotSelectThreeDay()\0"
    "slotSelectFiveDay()\0slotShowGotoSomeDays()\0"
    "slotGotoNow()\0slotGotoYesterday()\0"
    "slotGotoTwoDayBefore()\0slotGotoThreeDayBefore()\0"
    "slotGotoFourDayBefore()\0slotOnErrorMenu()\0"
    "slotOnWarnningMenu()\0slotOnSystemMenu()\0"
    "slotPushButtonMin()\0"
};

void LogManagerSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LogManagerSystem *_t = static_cast<LogManagerSystem *>(_o);
        switch (_id) {
        case 0: _t->sigStartThread(); break;
        case 1: _t->signalComboBoxToClearTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalResetSaveDay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalStartAutoUpDate(); break;
        case 4: _t->slotButtonClear(); break;
        case 5: _t->slotSelectDateChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotUpDate(); break;
        case 7: _t->slotUpPage(); break;
        case 8: _t->slotDownPage(); break;
        case 9: _t->slotGotoPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotHeadPage(); break;
        case 11: _t->slotTailPage(); break;
        case 12: _t->slotCheckBoxDebug((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slotSpinboxResetSaveDay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slotSearchGotoSomeday((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slotOnRealtimeDialog(); break;
        case 16: _t->slotSetCloseRealTimeDialog(); break;
        case 17: _t->slotOpenSettingDialog(); break;
        case 18: _t->slotSetStackWidgetFist((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->slotSetStackWidgetFist(); break;
        case 20: _t->slotSetStackWidgetNext((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->slotSetStackWidgetNext(); break;
        case 22: _t->slotONAutoUpDate(); break;
        case 23: _t->slotShowLevelMenu(); break;
        case 24: _t->slotShowSelectDays(); break;
        case 25: _t->slotSelectOneDay(); break;
        case 26: _t->slotSelectThreeDay(); break;
        case 27: _t->slotSelectFiveDay(); break;
        case 28: _t->slotShowGotoSomeDays(); break;
        case 29: _t->slotGotoNow(); break;
        case 30: _t->slotGotoYesterday(); break;
        case 31: _t->slotGotoTwoDayBefore(); break;
        case 32: _t->slotGotoThreeDayBefore(); break;
        case 33: _t->slotGotoFourDayBefore(); break;
        case 34: _t->slotOnErrorMenu(); break;
        case 35: _t->slotOnWarnningMenu(); break;
        case 36: _t->slotOnSystemMenu(); break;
        case 37: _t->slotPushButtonMin(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LogManagerSystem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LogManagerSystem::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LogManagerSystem,
      qt_meta_data_LogManagerSystem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LogManagerSystem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LogManagerSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LogManagerSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogManagerSystem))
        return static_cast<void*>(const_cast< LogManagerSystem*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LogManagerSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void LogManagerSystem::sigStartThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LogManagerSystem::signalComboBoxToClearTime(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LogManagerSystem::signalResetSaveDay(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LogManagerSystem::signalStartAutoUpDate()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
