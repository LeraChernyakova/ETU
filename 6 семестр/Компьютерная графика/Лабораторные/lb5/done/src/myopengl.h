#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "camera.h"

struct VertexData {
    VertexData()
    {
    }
    VertexData(QVector3D pos, QVector3D col, QVector3D norm) :
        position(pos), color(col), normal(norm)
    {
    }
    QVector3D position;
    QVector3D color;
    QVector3D normal;
};

class MyOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    MyOpenGL(QWidget* parent);
    ~MyOpenGL();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void initShaders();
    void initObject();
    void drawObject();

    QVector2D curve(float t);
    void calculateNormals(QVector<VertexData>& vertices);

    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject objectVao;

    QVector3D lightPos;
    Camera camera;

    QVector<QVector2D> controlPoints;
    int countVertices;

public slots:
    void changeLightPosition(QVector3D pos);
};

#endif // MYOPENGL_H
