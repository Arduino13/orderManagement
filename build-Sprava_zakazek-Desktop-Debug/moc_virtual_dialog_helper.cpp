/****************************************************************************
** Meta object code from reading C++ file 'virtual_dialog_helper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../App/virtual_dialog_helper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtual_dialog_helper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_virtual_dialog_helper_t {
    QByteArrayData data[11];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_virtual_dialog_helper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_virtual_dialog_helper_t qt_meta_stringdata_virtual_dialog_helper = {
    {
QT_MOC_LITERAL(0, 0, 21), // "virtual_dialog_helper"
QT_MOC_LITERAL(1, 22, 7), // "onClose"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 22), // "virtual_dialog_helper*"
QT_MOC_LITERAL(4, 54, 7), // "menuReq"
QT_MOC_LITERAL(5, 62, 3), // "pos"
QT_MOC_LITERAL(6, 66, 10), // "reloadMain"
QT_MOC_LITERAL(7, 77, 6), // "choose"
QT_MOC_LITERAL(8, 84, 14), // "QItemSelection"
QT_MOC_LITERAL(9, 99, 11), // "onClose_sub"
QT_MOC_LITERAL(10, 111, 15) // "menuReq_wrapper"

    },
    "virtual_dialog_helper\0onClose\0\0"
    "virtual_dialog_helper*\0menuReq\0pos\0"
    "reloadMain\0choose\0QItemSelection\0"
    "onClose_sub\0menuReq_wrapper"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_virtual_dialog_helper[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   53,    2, 0x09 /* Protected */,
       9,    1,   58,    2, 0x09 /* Protected */,
      10,    1,   61,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QPoint,    5,

       0        // eod
};

void virtual_dialog_helper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<virtual_dialog_helper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClose((*reinterpret_cast< virtual_dialog_helper*(*)>(_a[1]))); break;
        case 1: _t->menuReq((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->reloadMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->choose((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 4: _t->onClose_sub((*reinterpret_cast< virtual_dialog_helper*(*)>(_a[1]))); break;
        case 5: _t->menuReq_wrapper((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< virtual_dialog_helper* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< virtual_dialog_helper* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (virtual_dialog_helper::*)(virtual_dialog_helper * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&virtual_dialog_helper::onClose)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (virtual_dialog_helper::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&virtual_dialog_helper::menuReq)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (virtual_dialog_helper::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&virtual_dialog_helper::reloadMain)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject virtual_dialog_helper::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_virtual_dialog_helper.data,
    qt_meta_data_virtual_dialog_helper,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *virtual_dialog_helper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *virtual_dialog_helper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_virtual_dialog_helper.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int virtual_dialog_helper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void virtual_dialog_helper::onClose(virtual_dialog_helper * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void virtual_dialog_helper::menuReq(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void virtual_dialog_helper::reloadMain(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
