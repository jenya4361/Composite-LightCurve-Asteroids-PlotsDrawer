#-------------------------------------------------
#
# Project created by QtCreator 2019-04-16T22:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlotsDrawer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    ManagersController.cpp \
    managers/LogManager.cpp \
    managers/PlotsManager.cpp \
    App.cpp \
    ui/AddPlotImpl.cpp \
    ui/AxisLimitsImpl.cpp \
    ui/CurrentPlotImpl.cpp \
    ui/LogsImpl.cpp \
    ui/PlotsImpl.cpp \
    MainIncludes.cpp \
    AppEnums.cpp \
    ui/CustomPlotImpl.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    ManagersController.h \
    managers/LogManager.h \
    managers/PlotsManager.h \
    App.h \
    ui/AddPlotImpl.h \
    ui/AxisLimitsImpl.h \
    ui/CurrentPlotImpl.h \
    ui/LogsImpl.h \
    ui/PlotsImpl.h \
    MainIncludes.h \
    AppEnums.h \
    ui/CustomPlotImpl.h

FORMS    += mainwindow.ui
