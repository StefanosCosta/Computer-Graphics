######################################################################
# Automatically generated by qmake (3.0) Tue Aug 8 14:19:53 2017
######################################################################

TEMPLATE = app
TARGET = Egypt
INCLUDEPATH += . /opt/local/include

CONFIG += C++11

QT += widgets opengl gui

LIBS += -lglut -lGLU
# Input
HEADERS += Image.h EgyptWidget.h EgyptWindow.h
SOURCES += EgyptMain.cpp \
           EgyptWidget.cpp \
           EgyptWindow.cpp \
	   Image.cpp
