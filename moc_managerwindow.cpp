/****************************************************************************
** Meta object code from reading C++ file 'managerwindow.h'
**
** Created: Mon Jun 18 18:49:37 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "managerwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'managerwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ManagerWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x08,
      37,   14,   14,   14, 0x08,
      47,   14,   14,   14, 0x08,
      56,   14,   14,   14, 0x08,
      82,   14,   14,   14, 0x08,
      96,   14,   14,   14, 0x08,
     110,   14,   14,   14, 0x08,
     125,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ManagerWindow[] = {
    "ManagerWindow\0\0index\0setCurrent(int)\0"
    "addbook()\0remain()\0on_lineEdit_textChanged()\0"
    "showalluser()\0showallbook()\0closealluser()\0"
    "closeallbook()\0"
};

const QMetaObject ManagerWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ManagerWindow,
      qt_meta_data_ManagerWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ManagerWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ManagerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ManagerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManagerWindow))
        return static_cast<void*>(const_cast< ManagerWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int ManagerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCurrent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: addbook(); break;
        case 2: remain(); break;
        case 3: on_lineEdit_textChanged(); break;
        case 4: showalluser(); break;
        case 5: showallbook(); break;
        case 6: closealluser(); break;
        case 7: closeallbook(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE