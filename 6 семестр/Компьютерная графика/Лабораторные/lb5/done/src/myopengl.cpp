#include "myopengl.h"

MyOpenGL::MyOpenGL(QWidget* parent) :
    QOpenGLWidget(parent), vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    lightPos = QVector3D(0.0f, 0.0f, 0.0f);
    countVertices = 0;
    controlPoints = {
        QVector2D(-0.75f, -0.45f),
        QVector2D(0.0f, -0.85f),
        QVector2D(0.75f, -0.3f)
    };
}

MyOpenGL::~MyOpenGL()
{
    if (objectVao.isCreated()) {
        objectVao.destroy();
    }
    if (vertexBuffer.isCreated()) {
        vertexBuffer.destroy();
    }
}

void MyOpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    initShaders();
    initObject();
    camera.rotate(30.0f, 0.0f);
    camera.move(Camera::MoveDirection::Left);
    camera.move(Camera::MoveDirection::Left);
    camera.move(Camera::MoveDirection::Left);
}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.setViewport(w, h);
}

void MyOpenGL::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawObject();
}

void MyOpenGL::initShaders()
{
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh")
        || !shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh")
        || !shaderProgram.link()) {
        close();
    }
}

void MyOpenGL::initObject()
{
    QVector<VertexData> vertices;

    for (float t = 0; t <= 1; t += 0.01) {
        QVector2D p = curve(t);
        vertices.append(VertexData(QVector3D(p.x(), p.y(), -0.5), QVector3D(1.0f, 1.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f)));
        vertices.append(VertexData(QVector3D(p.x(), p.y(), 0.5), QVector3D(1.0f, 1.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f)));
    }

    countVertices = vertices.size();
    calculateNormals(vertices);

    objectVao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&objectVao);

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(vertices.constData(), vertices.size() * sizeof(VertexData));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    vertexBuffer.release();
}

void MyOpenGL::drawObject()
{
    QMatrix4x4 viewMatrix = camera.getView();
    QMatrix4x4 projectionMatrix = camera.getProjection();
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    QVector3D viewPos = camera.getPos();

    shaderProgram.bind();
    shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
    shaderProgram.setUniformValue("viewMatrix", viewMatrix);
    shaderProgram.setUniformValue("modelMatrix", modelMatrix);
    shaderProgram.setUniformValue("lightPos", lightPos);
    shaderProgram.setUniformValue("viewPos", viewPos);

    QOpenGLVertexArrayObject::Binder vaoBinder(&objectVao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, countVertices);

    shaderProgram.release();
}

QVector2D MyOpenGL::curve(float t)
{
    float x = pow((1 - t), 2) * controlPoints[0].x() + 2 * t * (1 - t) * controlPoints[1].x() + pow(t, 2) * controlPoints[2].x();
    float y = pow((1 - t), 2) * controlPoints[0].y() + 2 * t * (1 - t) * controlPoints[1].y() + pow(t, 2) * controlPoints[2].y();
    return QVector2D(x, y);
}

void MyOpenGL::calculateNormals(QVector<VertexData> &vertices)
{
    for (int i = 0; i < vertices.size() - 2; i++) {
        QVector3D v1 = vertices[i + 1].position - vertices[i].position;
        QVector3D v2 = vertices[i + 2].position - vertices[i + 1].position;
        QVector3D normal = QVector3D::crossProduct(v1, v2);
        normal.normalize();

        if (normal.y() < 0) {
            normal.setY(-normal.y());
        }

        normal.normalize();

        vertices[i].normal += normal;
        vertices[i + 1].normal += normal;
    }

    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i].normal.normalize();
    }
}

void MyOpenGL::changeLightPosition(QVector3D pos)
{
    lightPos = pos;
    update();
}
