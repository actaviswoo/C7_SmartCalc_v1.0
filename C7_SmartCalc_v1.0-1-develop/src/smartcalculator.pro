QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    plotterwindow.cpp \
    s21_smartcalc.c \
    s21_stack.c \
    qcustomplot.cpp \
    s21_credit.c \

HEADERS += \
    creditwindow.h \
    mainwindow.h \
    plotterwindow.h \
    s21_smartcalc.h \
    qcustomplot.h \
    s21_credit.h \

FORMS += \
    creditwindow.ui \
    mainwindow.ui \
    plotterwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
