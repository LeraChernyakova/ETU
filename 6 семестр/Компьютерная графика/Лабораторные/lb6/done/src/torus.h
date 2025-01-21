#ifndef TORUS_H
#define TORUS_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class torus {
public:
    torus(float innerRadius, float outerRadius, int sides, int rings);
};

#endif // TORUS_H
