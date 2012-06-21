/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Jun 19 23:41:03 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      20,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      50,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      66,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     102,   11,   11,   11, 0x08,
     110,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     128,   11,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     168,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0regis()\0ulogin()\0rmain()\0"
    "managerlog()\0search()\0open()\0openusrfile()\0"
    "openbkfile()\0okopen()\0about()\0whenexit()\0"
    "save()\0saveas()\0saveasusrfile()\0"
    "saveasbkfile()\0oksaveas()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: regis(); break;
        case 1: ulogin(); break;
        case 2: rmain(); break;
        case 3: managerlog(); break;
        case 4: search(); break;
        case 5: open(); break;
        case 6: openusrfile(); break;
        case 7: openbkfile(); break;
        case 8: okopen(); break;
        case 9: about(); break;
        case 10: whenexit(); break;
        case 11: save(); break;
        case 12: saveas(); break;
        case 13: saveasusrfile(); break;
        case 14: saveasbkfile(); break;
        case 15: oksaveas(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
