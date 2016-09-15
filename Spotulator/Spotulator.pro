TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++

QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
