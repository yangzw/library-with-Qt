/****************************************************************************
** Meta object code from reading C++ file 'searchwindow.h'
**
** Created: Mon Jun 18 17:12:54 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "searchwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SearchWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      40,   13,   13,   13, 0x08,
      57,   13,   13,   13, 0x08,
      71,   13,   13,   13, 0x08,
      88,   13,   13,   13, 0x08,
     102,   13,   13,   13, 0x08,
     115,   13,   13,   13, 0x08,
     128,   13,   13,   13, 0x08,
     141,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SearchWindow[] = {
    "SearchWindow\0\0on_lineEdit_textChanged()\0"
    "searchbybkname()\0searchbykey()\0"
    "searchbyauthor()\0rowselected()\0"
    "borrowbook()\0deletebook()\0updatebook()\0"
    "updatebkprocess()\0"
};

const QMetaObject SearchWindow::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_SearchWindow,
      qt_meta_data_SearchWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SearchWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SearchWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SearchWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchWindow))
        return static_cast<void*>(const_cast< SearchWindow*>(this));
    return QSplitter::qt_metacast(_clname);
}

int SearchWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_lineEdit_textChanged(); break;
        case 1: searchbybkname(); break;
        case 2: searchbykey(); break;
        case 3: searchbyauthor(); break;
        case 4: rowselected(); break;
        case 5: borrowbook(); break;
        case 6: deletebook(); break;
        case 7: updatebook(); break;
        case 8: updatebkprocess(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
