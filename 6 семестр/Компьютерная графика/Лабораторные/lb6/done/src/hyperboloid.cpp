#include "hyperboloid.h"

hyperboloid::hyperboloid(float a, float b, float c, int uSegments, int vSegments) {
    QVector<QVector3D> vertices;

    float uDelta = M_PI / uSegments;
    float vDelta = 2.0f * M_PI / vSegments;

    for (int i = 0; i <= uSegments; ++i) {
        float u = -M_PI / 2.0f + i * uDelta;
        float sinhU = sinh(u);
        float coshU = cosh(u);

        for (int j = 0; j <= vSegments; ++j) {
            float v = j * vDelta;
            float cosV = qCos(v);
            float sinV = qSin(v);

            float x = a * coshU * cosV;
            float y = b * coshU * sinV;
            float z = c * sinhU;

            vertices.push_back(QVector3D(x, y, z));
        }
    }

    for (int i = 0; i < uSegments; ++i) {
        for (int j = 0; j < vSegments; ++j) {
            int nextI = i + 1;
            int nextJ = j + 1;

            QVector3D v0 = vertices[i * (vSegments + 1) + j];
            QVector3D v1 = vertices[i * (vSegments + 1) + nextJ];
            QVector3D v2 = vertices[nextI * (vSegments + 1) + j];
            QVector3D v3 = vertices[nextI * (vSegments + 1) + nextJ];

            glBegin(GL_LINE_LOOP);
            glVertex3f(v0.x(), v0.y(), v0.z());
            glVertex3f(v1.x(), v1.y(), v1.z());
            glVertex3f(v3.x(), v3.y(), v3.z());
            glVertex3f(v2.x(), v2.y(), v2.z());
            glEnd();
        }
    }
}
