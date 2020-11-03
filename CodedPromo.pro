QT += \
    quick \
    network \
    serialport \
    sql

win32: LIBS += -lUser32

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        modules/activity.cpp \
        modules/arduino.cpp \
        modules/controllservice.cpp \
        modules/messageservice.cpp \
        modules/network.cpp \
        modules/opencv.cpp \
        modules/questions.cpp \
        modules/weather.cpp \
        modules/wincontrols.cpp \
        modules/yandexapi.cpp \
        sources/main.cpp \
        sources/private.cpp

RESOURCES += sources/qml.qrc \
    sources/images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    modules/activity.h \
    modules/arduino.h \
    modules/controllservice.h \
    modules/messageservice.h \
    modules/network.h \
    modules/opencv.h \
    modules/questions.h \
    modules/weather.h \
    modules/wincontrols.h \
    modules/yandexapi.h \
    sources/private.h \
    sources/private.h

win32:CONFIG(release, debug|release): LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world450
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world450d
else:unix: LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world450

INCLUDEPATH += D:/opencv/build/include
DEPENDPATH += D:/opencv/build/include
