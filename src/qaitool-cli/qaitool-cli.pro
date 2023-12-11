# ------------------------------------------------------------------------
# Copyright (c) 2013-2023 Seven Mersenne All Rights Reserved.
# Distributed under the GPL software license
# ------------------------------------------------------------------------

include(../config.pri)

QT = core gui

CONFIG += c++17 cmdline console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        TrainDataBundle.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    TrainDataBundle.h

TARGET = qaitool

