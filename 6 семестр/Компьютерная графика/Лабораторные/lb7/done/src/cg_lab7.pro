QT       += core gui opengl openglwidgets
QT_OPENGL = desktop

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG	+= c++17

LIBS += -lopengl32 \
        -lGLU32

SOURCES += \
    camera.cpp \
    glfigure.cpp \
    gllighting.cpp \
    glmaterial.cpp \
    glscene.cpp \
    glshaderprogram.cpp \
    glvertexobject.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    camera.h \
    glfigure.h \
    gllighting.h \
    glmaterial.h \
    glscene.h \
    glshaderprogram.h \
    glvertexobject.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
