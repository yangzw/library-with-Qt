/****************************************************************************
** Meta object code from reading C++ file 'userwindow.h'
**
** Created: Mon Jun 18 11:29:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "userwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_userWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      21,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   11,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      52,   11,   11,   11, 0x08,
      73,   67,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_userWindow[] = {
    "userWindow\0\0isexit()\0viewmybook()\0"
    "delusr()\0remain()\0updatemybook()\0index\0"
    "setCurrent(int)\0rowselected()\0"
    "returnbook()\0"
};

const QMetaObject userWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_userWindow,
      qt_meta_data_userWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &userWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *userWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *userWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_userWindow))
        return static_cast<void*>(const_cast< userWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int userWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: isexit(); break;
        case 1: viewmybook(); break;
        case 2: delusr(); break;
        case 3: remain(); break;
        case 4: updatemybook(); break;
        case 5: setCurrent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: rowselected(); break;
        case 7: returnbook(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void userWindow::isexit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void userWindow::viewmybook()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
