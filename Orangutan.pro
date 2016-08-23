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

CONFIG += c++11

# App sources
SOURCES += src/app/main.cpp \
        src/app/mainwindow.cpp \
        src/app/windowtitlebar.cpp \
        src/app/materialtool.cpp \
        src/app/customsliderwidget.cpp \
        src/app/renderingwindow.cpp \
        src/app/worldtool.cpp

# Core sources
SOURCES += src/core/shader.cpp \
        src/core/texture.cpp \
        src/core/opengl.cpp \
        src/core/qtrenderer.cpp \
        src/core/shaderprogram.cpp \
        src/core/vao.cpp

# Physics sources
SOURCES += src/physics/transformable.cpp

# Scene sources
SOURCES += src/scene/scene.cpp \
        src/scene/objectnode.cpp \
        src/scene/assetsstorage.cpp \
        src/scene/assetsfactory.cpp

# Object sources
SOURCES += src/object/object.cpp \
        src/object/asset.cpp \
        src/object/renderableobject.cpp \
        src/object/camera.cpp \
        src/object/light.cpp \
        src/object/material.cpp \
        src/object/mesh.cpp

# Shader sources
SOURCES += src/shader/edgefilterstrategy.cpp \
        src/shader/gaussianblurfilterstrategy.cpp \
        src/shader/shaderstrategy.cpp \
        src/shader/skyboxstrategy.cpp \
        src/shader/toonstrategy.cpp \
        src/shader/environmentstrategy.cpp \
        src/shader/gouraudstrategy.cpp

# Util sources
SOURCES += src/util/parseur.cpp


# App headers
HEADERS += src/app/mainwindow.h \
        src/app/windowtitlebar.h \
        src/app/materialtool.h \
        src/app/customsliderwidget.h \
        src/app/renderingwindow.h \
        src/app/worldtool.h

# Core headers
HEADERS += src/core/shader.h \
        src/core/texture.h \
        src/core/opengl.h \
        src/core/qtrenderer.h \
        src/core/shaderprogram.h \
        src/core/vao.h

# Physics headers
HEADERS += src/physics/transformable.h

# Scene headers
HEADERS += src/scene/scene.h \
        src/scene/objectnode.h \
        src/scene/assetsstorage.h \
        src/scene/assetsfactory.h

# Object headers
HEADERS += src/object/object.h \
        src/object/asset.h \
        src/object/renderableobject.h \
        src/object/camera.h \
        src/object/light.h \
        src/object/material.h \
        src/object/mesh.h

# Shader headers
HEADERS += src/shader/edgefilterstrategy.h \
        src/shader/gaussianblurfilterstrategy.h \
        src/shader/shaderstrategy.h \
        src/shader/skyboxstrategy.h \
        src/shader/toonstrategy.h \
        src/shader/environmentstrategy.h \
        src/shader/gouraudstrategy.h

# Util headers
HEADERS  += src/util/util.h

INCLUDEPATH += $$PWD/ext/GLM \
            src


DISTFILES += \
    src/style/style.qss \
