#include "torus.h"

torus::torus(float innerRadius, float outerRadius, int sides, int rings) {
    QVector<QVector3D> vertices;
    float ringDelta = 2.0f * M_PI / rings;
    float sideDelta = 2.0f * M_PI / sides;
    for (int i = 0; i < rings; ++i) {
        float theta = i * ringDelta;
        float cosTheta = qCos(theta);
        float sinTheta = qSin(theta);
        for (int j = 0; j < sides; ++j) {
            float phi = j * sideDelta;
            float cosPhi = qCos(phi);
            float sinPhi = qSin(phi);
            float x = cosTheta * (outerRadius + innerRadius * cosPhi);
            float y = sinTheta * (outerRadius + innerRadius * cosPhi);
            float z = innerRadius * sinPhi;

            vertices.push_back(QVector3D(x, y, z));
        }
    }

    for (int i = 0; i < rings; ++i) {
        for (int j = 0; j < sides; ++j) {
            int nextI = (i + 1) % rings;
            int nextJ = (j + 1) % sides;

            QVector3D v0 = vertices[i * sides + j];
            QVector3D v1 = vertices[i * sides + nextJ];
            QVector3D v2 = vertices[nextI * sides + j];
            QVector3D v3 = vertices[nextI * sides + nextJ];

            glBegin(GL_LINE_LOOP);
            glVertex3f(v0.x(), v0.y(), v0.z());
            glVertex3f(v1.x(), v1.y(), v1.z());
            glVertex3f(v3.x(), v3.y(), v3.z());
            glVertex3f(v2.x(), v2.y(), v2.z());
            glEnd();
        }
    }
}
