#ifndef CYLINDER_H
#define CYLINDER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class cylinder {
public:
    cylinder(float radius, float height, int segments);
};

#endif // CYLINDER_H
