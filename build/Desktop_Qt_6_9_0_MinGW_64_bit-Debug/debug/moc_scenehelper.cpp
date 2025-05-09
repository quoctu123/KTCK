/****************************************************************************
** Meta object code from reading C++ file 'scenehelper.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../scenehelper.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenehelper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11SceneHelperE_t {};
} // unnamed namespace

template <> constexpr inline auto SceneHelper::qt_create_metaobjectdata<qt_meta_tag_ZN11SceneHelperE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SceneHelper",
        "findEntity",
        "",
        "Qt3DRender::QSceneLoader*",
        "loader",
        "name",
        "addListEntry",
        "QVariant",
        "list",
        "entry",
        "removeFromScene",
        "names",
        "addBasicMaterials",
        "Qt3DRender::QMaterial*",
        "material",
        "addTextureMaterial",
        "replaceMaterial",
        "searchCamera"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'findEntity'
        QtMocHelpers::MethodData<QObject *(Qt3DRender::QSceneLoader *, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::QObjectStar, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 5 },
        }}),
        // Method 'addListEntry'
        QtMocHelpers::MethodData<void(const QVariant &, QObject *)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::QObjectStar, 9 },
        }}),
        // Method 'removeFromScene'
        QtMocHelpers::MethodData<void(Qt3DRender::QSceneLoader *, const QStringList &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QStringList, 11 },
        }}),
        // Method 'addBasicMaterials'
        QtMocHelpers::MethodData<void(Qt3DRender::QSceneLoader *, Qt3DRender::QMaterial *, QStringList)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 13, 14 }, { QMetaType::QStringList, 11 },
        }}),
        // Method 'addTextureMaterial'
        QtMocHelpers::MethodData<void(Qt3DRender::QSceneLoader *, Qt3DRender::QMaterial *, QString)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 13, 14 }, { QMetaType::QString, 5 },
        }}),
        // Method 'replaceMaterial'
        QtMocHelpers::MethodData<void(Qt3DRender::QSceneLoader *, const QString &, Qt3DRender::QMaterial *)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 5 }, { 0x80000000 | 13, 14 },
        }}),
        // Method 'searchCamera'
        QtMocHelpers::MethodData<void(Qt3DRender::QSceneLoader *, const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QString, 5 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SceneHelper, qt_meta_tag_ZN11SceneHelperE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SceneHelper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SceneHelperE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SceneHelperE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11SceneHelperE_t>.metaTypes,
    nullptr
} };

void SceneHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SceneHelper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QObject* _r = _t->findEntity((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QSceneLoader*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = std::move(_r); }  break;
        case 1: _t->addListEntry((*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[2]))); break;
        case 2: _t->removeFromScene((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QSceneLoader*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 3: _t->addBasicMaterials((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QSceneLoader*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Qt3DRender::QMaterial*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[3]))); break;
        case 4: _t->addTextureMaterial((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QSceneLoader*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Qt3DRender::QMaterial*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 5: _t->replaceMaterial((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QSceneLoader*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<Qt3DRender::QMaterial*>>(_a[3]))); break;
        case 6: _t->searchCamera((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QSceneLoader*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *SceneHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SceneHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11SceneHelperE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SceneHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
