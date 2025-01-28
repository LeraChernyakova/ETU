QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    copy_frame.cpp \
    dialog.cpp \
    get_ornament.cpp \
    imageviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    pixel_functions.cpp \
    read_write_functions.cpp \
    search_rectangles.cpp

HEADERS += \
    copy_frame.h \
    dialog.h \
    get_ornament.h \
    imageviewer.h \
    mainwindow.h \
    pixel_functions.h \
    png_structs.h \
    read_write_functions.h \
    search_rectangles.h

FORMS += \
    dialog.ui \
    imageviewer.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/release/ -lpng
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/debug/ -lpng
else:unix: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/ -lpng

INCLUDEPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/release/libpng.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/debug/libpng.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/release/png.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/debug/png.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/libpng.a
