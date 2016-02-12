#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T22:06:22
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Orangutan
TEMPLATE = app
CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    assetsstorage.cpp \
    material.cpp \
    mesh.cpp \
    Shader/environmentstrategy.cpp \
    Shader/gouraudstrategy.cpp \
    Shader/shader.cpp \
    Shader/shaderprogram.cpp \
    Shader/shaderstrategy.cpp \
    Shader/skyboxstrategy.cpp \
    Shader/toonstrategy.cpp \
    texture.cpp \
    opengl.cpp \
    lightnode.cpp \
    light.cpp \
    transformable.cpp \
    assetsfactory.cpp \
    parseur.cpp \
    renderingwindow.cpp \
    scene.cpp \
    renderable.cpp \
    camera.cpp \
    cameranode.cpp \
    renderablenode.cpp \
    scenenode.cpp \
    windowtitlebar.cpp \
    materialtool.cpp \
    customsliderwidget.cpp

HEADERS  += mainwindow.h \
    assetsstorage.h \
    material.h \
    mesh.h \
    Shader/environmentstrategy.h \
    Shader/gouraudstrategy.h \
    Shader/shader.h \
    Shader/shaderprogram.h \
    Shader/shaderstrategy.h \
    Shader/skyboxstrategy.h \
    Shader/toonstrategy.h \
    texture.h \
    util.h \
    opengl.h \
    lightnode.h \
    light.h \
    transformable.h \
    assetsfactory.h \
    parseur.h \
    renderingwindow.h \
    scene.h \
    renderable.h \
    camera.h \
    cameranode.h \
    renderablenode.h \
    scenenode.h \
    windowtitlebar.h \
    materialtool.h \
    customsliderwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/GLM\

LIBS += opengl32.lib\

DISTFILES += \
    style.qss
