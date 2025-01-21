#ifndef HYPERBOLOID_H
#define HYPERBOLOID_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class hyperboloid {
public:
    hyperboloid(float a, float b, float c, int uSegments, int vSegments);
};

#endif // HYPERBOLOID_H
