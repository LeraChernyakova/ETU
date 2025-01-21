#include "cylinder.h"

cylinder::cylinder(float radius, float height, int segments) {
    QVector<QVector3D> vertices;

    float angleDelta = 2.0f * M_PI / segments;

    for (int i = 0; i < segments; ++i) {
        float angle = i * angleDelta;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        float z = height / 2.0f;
        vertices.push_back(QVector3D(x, y, z));
    }

    for (int i = 0; i < segments; ++i) {
        float angle = i * angleDelta;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        float z = -height / 2.0f;
        vertices.push_back(QVector3D(x, y, z));
    }

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        QVector3D v = vertices[i];
        glVertex3f(v.x(), v.y(), v.z());
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        QVector3D v = vertices[i + segments];
        glVertex3f(v.x(), v.y(), v.z());
    }
    glEnd();

    for (int i = 0; i < segments / 2; ++i) {
        int next = i + (segments / 2);
        int topIndex = i;
        int bottomIndex = i + segments;

        QVector3D vTop0 = vertices[topIndex];
        QVector3D vTop1 = vertices[next];
        QVector3D vBottom0 = vertices[bottomIndex];
        QVector3D vBottom1 = vertices[next + segments];

        glBegin(GL_LINES);
        glVertex3f(vTop0.x(), vTop0.y(), vTop0.z());
        glVertex3f(vBottom0.x(), vBottom0.y(), vBottom0.z());

        glVertex3f(vTop1.x(), vTop1.y(), vTop1.z());
        glVertex3f(vBottom1.x(), vBottom1.y(), vBottom1.z());
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(vTop0.x(), vTop0.y(), vTop0.z());
        glVertex3f(vTop1.x(), vTop1.y(), vTop1.z());

        glVertex3f(vBottom0.x(), vBottom0.y(), vBottom0.z());
        glVertex3f(vBottom1.x(), vBottom1.y(), vBottom1.z());
        glEnd();
    }
}
