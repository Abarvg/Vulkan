# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = vulkan_minimal_compute
CONFIG += c++11

QT       += core gui widgets

LIBS += -lvulkan

HEADERS = \
   $$PWD/src/lodepng.h \
   src/CComputeApplication.h \
   src/Painting.h \
   src/const.h \
   src/mainwindow.h \
   src/vulkanComputing.h

SOURCES = \
   $$PWD/src/lodepng.cpp \
   $$PWD/src/main.cpp \
   src/CComputeApplication.cpp \
    src/Painting.cpp \
    src/mainwindow.cpp

INCLUDEPATH = \
    $$PWD/src

#DEFINES = 

DISTFILES += \
    shaders/comp.spv \
    shaders/shader.comp


