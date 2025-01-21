QT       += core gui opengl openglwidgets
QT_OPENGL = desktop

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG	+= c++17

LIBS += -lopengl32 \
        -lGLU32

SOURCES += \
    cylinder.cpp \
    glscene.cpp \
    glshaderprogram.cpp \
    glvertexobject.cpp \
    hyperboloid.cpp \
    main.cpp \
    mainwindow.cpp \
    torus.cpp

HEADERS += \
    cylinder.h \
    glscene.h \
    glshaderprogram.h \
    glvertexobject.h \
    hyperboloid.h \
    mainwindow.h \
    torus.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
