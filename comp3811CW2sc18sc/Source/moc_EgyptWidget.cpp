/****************************************************************************
** Meta object code from reading C++ file 'EgyptWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EgyptWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EgyptWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EgyptWidget_t {
    QByteArrayData data[18];
    char stringdata[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EgyptWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EgyptWidget_t qt_meta_stringdata_EgyptWidget = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 11),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 10),
QT_MOC_LITERAL(4, 36, 17),
QT_MOC_LITERAL(5, 54, 17),
QT_MOC_LITERAL(6, 72, 25),
QT_MOC_LITERAL(7, 98, 20),
QT_MOC_LITERAL(8, 119, 24),
QT_MOC_LITERAL(9, 144, 11),
QT_MOC_LITERAL(10, 156, 24),
QT_MOC_LITERAL(11, 181, 30),
QT_MOC_LITERAL(12, 212, 21),
QT_MOC_LITERAL(13, 234, 20),
QT_MOC_LITERAL(14, 255, 20),
QT_MOC_LITERAL(15, 276, 9),
QT_MOC_LITERAL(16, 286, 8),
QT_MOC_LITERAL(17, 295, 9)
    },
    "EgyptWidget\0updateAngle\0\0updateZoom\0"
    "updateAlienRadius\0updateAlienHeight\0"
    "updateAlienRotationRadius\0"
    "updateAlienSpinSpeed\0updateAlienRotationSpeed\0"
    "alienAbduct\0updateArmJointProperties\0"
    "updateArmJointSphereProperties\0"
    "updateAlienProperties\0updateDiscProperties\0"
    "updateGateProperties\0lightsOff\0lightsOn\0"
    "angleView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EgyptWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    1,   95,    2, 0x0a /* Public */,
       4,    1,   98,    2, 0x0a /* Public */,
       5,    1,  101,    2, 0x0a /* Public */,
       6,    1,  104,    2, 0x0a /* Public */,
       7,    1,  107,    2, 0x0a /* Public */,
       8,    1,  110,    2, 0x0a /* Public */,
       9,    0,  113,    2, 0x0a /* Public */,
      10,    1,  114,    2, 0x0a /* Public */,
      11,    1,  117,    2, 0x0a /* Public */,
      12,    1,  120,    2, 0x0a /* Public */,
      13,    1,  123,    2, 0x0a /* Public */,
      14,    1,  126,    2, 0x0a /* Public */,
      15,    0,  129,    2, 0x0a /* Public */,
      16,    0,  130,    2, 0x0a /* Public */,
      17,    1,  131,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void EgyptWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EgyptWidget *_t = static_cast<EgyptWidget *>(_o);
        switch (_id) {
        case 0: _t->updateAngle(); break;
        case 1: _t->updateZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateAlienRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateAlienHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateAlienRotationRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateAlienSpinSpeed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updateAlienRotationSpeed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->alienAbduct(); break;
        case 8: _t->updateArmJointProperties((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->updateArmJointSphereProperties((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->updateAlienProperties((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->updateDiscProperties((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->updateGateProperties((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->lightsOff(); break;
        case 14: _t->lightsOn(); break;
        case 15: _t->angleView((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EgyptWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_EgyptWidget.data,
      qt_meta_data_EgyptWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *EgyptWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EgyptWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EgyptWidget.stringdata))
        return static_cast<void*>(const_cast< EgyptWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int EgyptWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
