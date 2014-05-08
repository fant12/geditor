#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T03:38:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GEditor1_4
TEMPLATE = app


SOURCES += main.cpp\
        geditor.cpp \
    model/toyobject.cpp \
    interfaces/iserializable.cpp \
    control/manager.cpp \
    control/drawer.cpp \
    model/camera.cpp \
    model/background.cpp \
    model/clickarea.cpp \
    model/door.cpp \
    model/gcharacter.cpp \
    model/gcursor.cpp \
    model/inventar.cpp \
    model/item.cpp \
    model/gobject.cpp \
    model/player.cpp \
    model/videoarea.cpp \
    model/soundarea.cpp \
    model/mediaarea.cpp \
    view/workbox.cpp \
    view/elist.cpp \
    view/scripteditor.cpp \
    view/oinspector.cpp \
    view/dialogs/cadialog.cpp \
    view/dialogs/inputdialog.cpp \
    view/dialogs/aboutdialog.cpp \
    view/dialogs/projectdialog.cpp \
    view/canvas/canvas.cpp \
    view/editor/highlighter.cpp \
    view/canvas/canvasview.cpp \
    view/canvas/canvasitem.cpp \
    view/canvas/cornergrabber.cpp \
    view/canvas/rotatoritem.cpp \
    view/canvas/rotatorcircle.cpp \
    view/dialogs/rotatordialog.cpp \
    view/fileinspector.cpp \
    view/dialogs/connector/connectordialog.cpp \
    view/canvas/sprite.cpp \
    view/dialogs/searchdialog.cpp \
    view/dialogs/statecreator/abstractspritestate.cpp \
    view/dialogs/statecreator/statefactory.cpp

HEADERS  += geditor.h \
    model/toyobject.h \
    templates/getset.h \
    templates/singleton.h \
    interfaces/iserializable.h \
    templates/observer.h \
    templates/observable.h \
    control/manager.h \
    control/drawer.h \
    model/camera.h \
    model/background.h \
    model/clickarea.h \
    model/door.h \
    model/gcharacter.h \
    model/gcursor.h \
    model/inventar.h \
    model/item.h \
    model/gobject.h \
    model/player.h \
    model/videoarea.h \
    model/soundarea.h \
    model/mediaarea.h \
    interfaces/tobjecttypes.h \
    view/workbox.h \
    view/elist.h \
    view/scripteditor.h \
    view/oinspector.h \
    view/dialogs/inputdialog.h \
    view/dialogs/projectdialog.h \
    view/canvas/canvas.h \
    view/editor/highlighter.h \
    view/canvas/canvasview.h \
    view/canvas/canvasitem.h \
    view/canvas/cornergrabber.h \
    view/canvas/rotatoritem.h \
    view/canvas/rotatorcircle.h \
    view/dialogs/rotatordialog.h \
    view/fileinspector.h \
    view/dialogs/connector/connectordialog.h \
    view/canvas/sprite.h \
    view/dialogs/searchdialog.h \
    view/dialogs/aboutdialog.h \
    view/dialogs/cadialog.h \
    view/dialogs/statecreator/abstractspritestate.h \
    view/dialogs/statecreator/statefactory.h

FORMS    += geditor.ui

RESOURCES += \
    resources.qrc
