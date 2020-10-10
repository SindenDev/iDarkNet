HEADERS += \
    $$PWD/AVDefine.h \
    $$PWD/AVMediaCallback.h \
    $$PWD/AVOutput.h \
    $$PWD/AVPlayer.h \
    $$PWD/AVThread.h \
    $$PWD/AVDecoder.h

SOURCES += \
    $$PWD/AVOutput.cpp \
    $$PWD/AVPlayer.cpp \
    $$PWD/AVThread.cpp \
    $$PWD/AVDecoder.cpp

RESOURCES += \
    $$PWD/qtavplayer.qrc


win32{
    LIBS += -L$$PWD/libs/lib/win64/ -lavcodec -lavfilter -lavformat -lavutil -lswresample -lswscale
}

INCLUDEPATH += \
    $$PWD \
    $$PWD/libs/include
DEPENDPATH += \
    $$PWD \
    $$PWD/libs/include
