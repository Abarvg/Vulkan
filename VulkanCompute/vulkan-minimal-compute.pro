# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = vulkan_minimal_compute
CONFIG += c++11

QT       += core gui widgets

LIBS += -lvulkan

HEADERS = \
   $$PWD/src/lodepng.h \
   ../VulkanField/mainwindow.h \
   src/CComputeApplication.h \
   src/MainWindow.h \
   src/const.h

SOURCES = \
   $$PWD/src/lodepng.cpp \
   $$PWD/src/main.cpp \
   src/CComputeApplication.cpp \

INCLUDEPATH = \
    $$PWD/src

#DEFINES = 

DISTFILES += \
    shaders/comp.spv \
    shaders/shader.comp


