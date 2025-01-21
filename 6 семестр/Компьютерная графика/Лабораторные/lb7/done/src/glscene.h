#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <memory>

#include "glshaderprogram.h"
#include "glfigure.h"
#include "gllighting.h"
#include "camera.h"

//camera projection type
enum class GLProjectionType
{
    Perspective,
    Orthographic
};

//OpenGL scene representation
class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    //set camera projection type
    void setProjectionType(GLProjectionType type);

    inline GLShaderProgram* getFigureShaderProgram() { return figureShaderProgram_; }
    inline GLLighting& getLighting() { return lighting_; }
    inline QVector<std::shared_ptr<GLFigure>>& getFigures() { return figures_; }
    inline std::shared_ptr<GLFigure> getFigure(ssize_t index) { return figures_.at(index); }

protected:
    //initialize OpenGL window
    virtual void initializeGL() override;
    //resize OpenGL window
    virtual void resizeGL(int w, int h) override;
    //draw scene
    virtual void paintGL() override;

private:
    //create OpenGL shader programs for figures, axes and light source
    void createShaderProgram();
    //generate figures base cuts
    void generateFigures();
    //generate axes vertices
    void generateAxes();
    //convert degrees to radians
    inline float d2r(float degrees) const
    {
        return 3.1459265 * degrees / 180.f;
    }

    //scene width
    GLfloat width_;
    //scene height
    GLfloat height_;
    //figure shader program
    GLShaderProgram* figureShaderProgram_ = nullptr;
    //scene lighting params
    GLLighting lighting_;
    //axes shader program
    GLShaderProgram* axesShaderProgram_ = nullptr;
    //axes vertex object
    GLVertexObject axesVertexObject_;
    //light source shader program
    GLShaderProgram* lightSourceShaderProgram_ = nullptr;
    //light source representation
    std::shared_ptr<GLFigure> lightSource_;
    //detalization factor
    GLuint fragmentationFactor_ = 5;
    //camera settings
    Camera camera_;
    //camera projection type
    GLProjectionType projection_ = GLProjectionType::Perspective;
    //model matrix
    QMatrix4x4 modelMatrix_;
    //projection matrix
    QMatrix4x4 projectionMatrix_;
    //figures representations
    QVector<std::shared_ptr<GLFigure>> figures_;
    //axes vertices vector
    QVector<QPair<QVector3D, QVector3D>> axesVertices_;
};

#endif // GLSCENE_H
