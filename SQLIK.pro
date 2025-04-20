QT       += core gui charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DictionaryWidget.cpp \
    customchartview.cpp \
    getValueFromDatabase.cpp \
    main.cpp \
    mainwindow.cpp \
    sqlhighlighter.cpp \
    trainerTaskWidget.cpp \
    trainerwidget.cpp

HEADERS += \
    ColumnFontDelegate.h \
    clickableframe.h \
    customchartview.h \
    mainwindow.h \
    sqlhighlighter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/img/Dictionary.svg \
    res/img/Dictionary2.svg \
    res/img/DictionaryOrange.svg \
    res/img/Lessons.svg \
    res/img/Tests.svg \
    res/img/Trainer.svg \
    res/img/back.svg \
    res/img/execute.svg \
    res/img/ico.png \
    res/img/ico.svg \
    res/img/lk.png \
    res/img/lk.svg
