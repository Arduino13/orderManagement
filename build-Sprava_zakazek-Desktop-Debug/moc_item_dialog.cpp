/****************************************************************************
** Meta object code from reading C++ file 'item_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../App/item_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'item_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_item_dialog_t {
    QByteArrayData data[5];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_item_dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_item_dialog_t qt_meta_stringdata_item_dialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "item_dialog"
QT_MOC_LITERAL(1, 12, 4), // "edit"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "remove"
QT_MOC_LITERAL(4, 25, 10) // "customMenu"

    },
    "item_dialog\0edit\0\0remove\0customMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_item_dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       3,    1,   32,    2, 0x08 /* Private */,
       4,    1,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QPoint,    2,

       0        // eod
};

void item_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<item_dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->edit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->remove((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->customMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject item_dialog::staticMetaObject = { {
    &virtual_dialog<Ui::ItemTab*>::staticMetaObject,
    qt_meta_stringdata_item_dialog.data,
    qt_meta_data_item_dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *item_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *item_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_item_dialog.stringdata0))
        return static_cast<void*>(this);
    return virtual_dialog<Ui::ItemTab*>::qt_metacast(_clname);
}

int item_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = virtual_dialog<Ui::ItemTab*>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
