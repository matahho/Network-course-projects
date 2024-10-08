QT = core
QT += multimedia

CONFIG += c++17 cmdline


INCLUDEPATH +=
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AudioRecorder.cpp \
        audiosink.cpp \
        client.cpp \
        main.cpp \
        server.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AudioRecorder.h \
    audiosink.h \
    client.h \
    server.h

INCLUDEPATH += C:\boost_1_84_0
LIBS += -LC:\boost_1_84_0\stage\mingw-x64\lib -lboost_system-mgw11-mt-d-x64-1_84
LIBS += -lws2_32
LIBS += -lwsock32


# macx {
#     QMAKE_CXXFLAGS += -std=c++17

#     _BOOST_PATH = /usr/local/Cellar/boost/1.84.0_1
#     INCLUDEPATH += "$${_BOOST_PATH}/include/"
#     LIBS += -L$${_BOOST_PATH}/lib
#     ## Use only one of these:
#     LIBS += -lboost_chrono-mt -lboost_system # using dynamic lib (not sure if you need that "-mt" at the end or not)
#     #LIBS += $${_BOOST_PATH}/lib/libboost_chrono-mt.a # using static lib
# }

