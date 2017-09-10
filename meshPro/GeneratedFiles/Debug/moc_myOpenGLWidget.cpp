/****************************************************************************
** Meta object code from reading C++ file 'myOpenGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myOpenGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myOpenGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myOpenGLWidget_t {
    QByteArrayData data[15];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myOpenGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myOpenGLWidget_t qt_meta_stringdata_myOpenGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "myOpenGLWidget"
QT_MOC_LITERAL(1, 15, 16), // "check_edge_state"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "state"
QT_MOC_LITERAL(4, 39, 16), // "check_face_state"
QT_MOC_LITERAL(5, 56, 17), // "check_point_state"
QT_MOC_LITERAL(6, 74, 19), // "check_texture_state"
QT_MOC_LITERAL(7, 94, 17), // "check_light_state"
QT_MOC_LITERAL(8, 112, 16), // "check_axes_state"
QT_MOC_LITERAL(9, 129, 13), // "setWheelSpeed"
QT_MOC_LITERAL(10, 143, 17), // "setLightPositionX"
QT_MOC_LITERAL(11, 161, 17), // "setLightPositionY"
QT_MOC_LITERAL(12, 179, 17), // "setLightPositionZ"
QT_MOC_LITERAL(13, 197, 11), // "loadTexture"
QT_MOC_LITERAL(14, 209, 10) // "clearLines"

    },
    "myOpenGLWidget\0check_edge_state\0\0state\0"
    "check_face_state\0check_point_state\0"
    "check_texture_state\0check_light_state\0"
    "check_axes_state\0setWheelSpeed\0"
    "setLightPositionX\0setLightPositionY\0"
    "setLightPositionZ\0loadTexture\0clearLines"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myOpenGLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       4,    1,   77,    2, 0x0a /* Public */,
       5,    1,   80,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x0a /* Public */,
       7,    1,   86,    2, 0x0a /* Public */,
       8,    1,   89,    2, 0x0a /* Public */,
       9,    1,   92,    2, 0x0a /* Public */,
      10,    1,   95,    2, 0x0a /* Public */,
      11,    1,   98,    2, 0x0a /* Public */,
      12,    1,  101,    2, 0x0a /* Public */,
      13,    0,  104,    2, 0x0a /* Public */,
      14,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void myOpenGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myOpenGLWidget *_t = static_cast<myOpenGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->check_edge_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->check_face_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->check_point_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->check_texture_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->check_light_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->check_axes_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setWheelSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setLightPositionX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setLightPositionY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setLightPositionZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->loadTexture(); break;
        case 11: _t->clearLines(); break;
        default: ;
        }
    }
}

const QMetaObject myOpenGLWidget::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_myOpenGLWidget.data,
      qt_meta_data_myOpenGLWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myOpenGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myOpenGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myOpenGLWidget.stringdata0))
        return static_cast<void*>(const_cast< myOpenGLWidget*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int myOpenGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
