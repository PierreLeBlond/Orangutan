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

linux {
CONFIG += c++11
}


SOURCES += main.cpp\
        mainwindow.cpp \
    assetsstorage.cpp \
    material.cpp \
    mesh.cpp \
    shader/environmentstrategy.cpp \
    shader/gouraudstrategy.cpp \
    shader/shader.cpp \
    shader/shaderprogram.cpp \
    shader/shaderstrategy.cpp \
    shader/skyboxstrategy.cpp \
    shader/toonstrategy.cpp \
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
    customsliderwidget.cpp \
    shader/edgefilterstrategy.cpp \
    worldtool.cpp \
    shader/gaussianblurfilterstrategy.cpp \
    object.cpp

HEADERS  += mainwindow.h \
    assetsstorage.h \
    material.h \
    mesh.h \
    shader/environmentstrategy.h \
    shader/gouraudstrategy.h \
    shader/shader.h \
    shader/shaderprogram.h \
    shader/shaderstrategy.h \
    shader/skyboxstrategy.h \
    shader/toonstrategy.h \
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
    customsliderwidget.h \
    shader/edgefilterstrategy.h \
    worldtool.h \
    shader/gaussianblurfilterstrategy.h \
    object.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/GLM\

win32{
LIBS += opengl32.lib\
}

DISTFILES += \
    style.qss \
    edgefilter.vert \
    edgefilter.frag \
    verticalgaussianblurfilter.frag \
    horizontalgaussianblurfilter.frag
