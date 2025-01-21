#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

#include "glshaderprogram.h"
#include "glvertexobject.h"

class GLScene: public QOpenGLWidget, public QOpenGLFunctions {
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    void setType(std::string type);
    void setFragmentationFactor(GLuint factor);
    void setRotation(GLdouble x, GLdouble y, GLdouble z);
    void setScale(GLdouble x, GLdouble y, GLdouble z);
    void setTranslation(GLdouble x, GLdouble y, GLdouble z);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    void createShaderPrograms();

    void prepareAxes();
    void loadAxes();

    GLdouble _width;
    GLdouble _height;

    GLShaderProgram* figureShaderProgram_ = nullptr;
    GLVertexObject figureVertexObject_;

    GLShaderProgram* axesShaderProgram_ = nullptr;
    GLVertexObject axesVertexObject_;

    std::string type_ = "";

    GLuint fragmentationFactor_ = 1;

    QMatrix4x4 rotationMatrix_;
    QMatrix4x4 scaleMatrix_;
    QMatrix4x4 translationMatrix_;

    QVector<QPair<QVector3D, QVector3D>> axesVertices_;
};

#endif // GLSCENE_H
