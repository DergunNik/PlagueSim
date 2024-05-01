QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #cityvisualizer.cpp \
    commonClasses/citizen.cpp \
    commonClasses/district.cpp \
    commonClasses/districtsmanager.cpp \
    commonClasses/schedule.cpp \
    commonClasses/statistics.cpp \
    finalStage/statwindow.cpp \
    #generations.cpp \
    main.cpp \
    #mainwindow.cpp \
    simulationStage/ball.cpp \
    simulationStage/citymanager.cpp \
    simulationStage/cityvisualizer.cpp \
    simulationStage/districtvisualizer.cpp \
    simulationStage/graphicsdistrictitem.cpp \
    simulationStage/mainwindow.cpp \
    simulationStage/news.cpp \
    simulationStage/who.cpp \
    startStage/generations.cpp \
    startStage/startmenu.cpp \
    windowsmanager.cpp
    #startmenu.cpp \
     #statwindow.cpp

HEADERS += \
    #basicstructs.h \
    #cityvisualizer.h \
    commonClasses/basicstructs.h \
    commonClasses/citizen.h \
    commonClasses/declarations.h \
    commonClasses/district.h \
    commonClasses/districtsmanager.h \
    commonClasses/plaguebasics.h \
    commonClasses/schedule.h \
    commonClasses/statistics.h \
    finalStage/movingaverage.h \
    finalStage/statwindow.h \
    #generations.h \
    #mainwindow.h \
    simulationStage/ball.h \
    simulationStage/citymanager.h \
    simulationStage/cityvisualizer.h \
    simulationStage/districtvisualizer.h \
    simulationStage/graphicsdistrictitem.h \
    simulationStage/mainwindow.h \
    simulationStage/news.h \
    simulationStage/who.h \
    startStage/generations.h \
    startStage/startmenu.h \
    windowsmanager.h
    #startmenu.h \
     #statwindow.h

FORMS += \
    #cityvisualizer.ui \
    finalStage/statwindow.ui \
    #mainwindow.ui \
    simulationStage/cityvisualizer.ui \
    simulationStage/districtvisualizer.ui \
    simulationStage/mainwindow.ui \
    simulationStage/news.ui \
    startStage/startmenu.ui \
    #startmenu.ui \
    #statwindow.ui

RESOURCES += \
    content.qrc

INCLUDEPATH += \
    commonClasses/ \
    startStage/ \
    simulationStage/ \
    finalStage/


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
