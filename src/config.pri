# ------------------------------------------------------------------------
# Copyright (c) 2013-2022 Seven Mersenne All Rights Reserved.
# Distributed under the GPL software license
# ------------------------------------------------------------------------

# This file is a part of
# QCryptopp - Qt Crypto Cpp
#
# (c) 2013-2022 Seven Mersenne (7mersenne@gmail.com)
#
# It can be used freely, maintaining the information above.

CONFIG += USE_OPENSSL

#CONFIG += c++11
CONFIG += c++17

DEFINES += __SRPG_DEBUG_LOG_ENABLE__

# output
CONFIG(debug, debug|release){
    LIBS += -L$$OUT_PWD/../bin.debug
    DESTDIR = $$OUT_PWD/../bin.debug
}
else{
    LIBS += -L$$OUT_PWD/../bin
    DESTDIR = $$OUT_PWD/../bin
}

# temp dirs (unix)
unix{
    MOC_DIR = $$OUT_PWD/_generated
    OBJECTS_DIR = $$OUT_PWD/_generated
    UI_DIR = $$OUT_PWD/_generated
    RCC_DIR = $$OUT_PWD/_generated
}

#VERSION = 0.0.1.0
#QMAKE_TARGET_COMPANY = "Protasys LLC"



