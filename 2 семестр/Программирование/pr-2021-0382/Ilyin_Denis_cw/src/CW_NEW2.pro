QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog_drow_pramougolnik.cpp \
    dialog_ramka.cpp \
    dialog_split.cpp \
    images.cpp \
    main.cpp \
    mainwindow.cpp \
    sprawka.cpp

HEADERS += \
    dialog_drow_pramougolnik.h \
    dialog_ramka.h \
    dialog_split.h \
    images.h \
    mainwindow.h \
    sprawka.h

FORMS += \
    dialog_drow_pramougolnik.ui \
    dialog_ramka.ui \
    dialog_split.ui \
    mainwindow.ui \
    sprawka.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../lib/x86_64-linux-gnu/release/ -lpng
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../lib/x86_64-linux-gnu/debug/ -lpng
else:unix: LIBS += -L$$PWD/../../../../lib/x86_64-linux-gnu/ -lpng

INCLUDEPATH += $$PWD/../../../../lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../lib/x86_64-linux-gnu

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../lib/x86_64-linux-gnu/release/libpng.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../lib/x86_64-linux-gnu/debug/libpng.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../lib/x86_64-linux-gnu/release/png.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../lib/x86_64-linux-gnu/debug/png.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../lib/x86_64-linux-gnu/libpng.a
