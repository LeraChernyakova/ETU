#include "glscene.h"

#include "hyperboloid.h"
#include "torus.h"
#include "cylinder.h"

#include <iostream>

GLScene::GLScene(QWidget* parent):QOpenGLWidget{ parent }{}

void GLScene::initializeGL() {
    QColor bgc(0x2E, 0x2E, 0x2E);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());
    createShaderPrograms();
    if (!figureShaderProgram_->init() || !axesShaderProgram_->init()) {
        std::cerr << "Unable to initialize Shader Programs" << std::endl;
        std::cerr << "Figure Shader Program log: " << figureShaderProgram_->log().toStdString() << std::endl;
        std::cerr << "Axes Shader Program log: " << axesShaderProgram_->log().toStdString() << std::endl;
        return;
    }
    figureVertexObject_.init();
    axesVertexObject_.init();
    setRotation(0.f, 0.f, 0.f);
    setScale(1.f, 1.f, 1.f);
    setTranslation(0.f, 0.f, 0.f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLScene::resizeGL(int w, int h) {
    _width = w;
    _height = h;
}

void GLScene::paintGL() {
    figureShaderProgram_->bind();
    figureVertexObject_.bind_vao();

    glLineWidth(1.0f);

    if (type_ == "Torus") {
        torus(0.2, 0.3, fragmentationFactor_ * 15, fragmentationFactor_ * 15);
    }

    if (type_ == "Hyperboloid") {
        hyperboloid(0.1, 0.1, 0.35, fragmentationFactor_ * 10, fragmentationFactor_ * 10);
    }

    if (type_ == "Cylinder") {
        cylinder(0.25, 1.0, fragmentationFactor_ * 10);
    }

    prepareAxes();
    loadAxes();

    {
        int rotationMatrixLocation = figureShaderProgram_->uniformLocation("rotation");
        figureShaderProgram_->setUniformValue(rotationMatrixLocation, rotationMatrix_);

        int scaleMatrixLocation = figureShaderProgram_->uniformLocation("scale");
        figureShaderProgram_->setUniformValue(scaleMatrixLocation, scaleMatrix_);

        int translationMatrixLocation = figureShaderProgram_->uniformLocation("translation");
        figureShaderProgram_->setUniformValue(translationMatrixLocation, translationMatrix_);
    }

    figureVertexObject_.unbind_vao();
    figureShaderProgram_->release();

    axesShaderProgram_->bind();
    axesVertexObject_.bind_vao();

    glLineWidth(3.0f);
    {
        int rotationMatrixLocation = axesShaderProgram_->uniformLocation("rotation");
        axesShaderProgram_->setUniformValue(rotationMatrixLocation, rotationMatrix_);
    }
    glDrawArrays(GL_LINES, 0, 6);

    axesVertexObject_.unbind_vao();
    axesShaderProgram_->release();
}

void GLScene::createShaderPrograms() {
    QMap<QOpenGLShader::ShaderType, QString> figureShaders;
    QMap<QOpenGLShader::ShaderType, QString> axesShaders;

    figureShaders[QOpenGLShader::Vertex] = ":/shaders/figure.vs";
    figureShaders[QOpenGLShader::Fragment] = ":/shaders/figure.fs";

    axesShaders[QOpenGLShader::Vertex] = ":/shaders/axes.vs";
    axesShaders[QOpenGLShader::Fragment] = ":/shaders/axes.fs";

    figureShaderProgram_ = new GLShaderProgram(figureShaders, this);
    axesShaderProgram_ = new GLShaderProgram(axesShaders, this);
}

void GLScene::loadAxes() {
    axesVertexObject_.bind_vao();
    axesVertexObject_.loadVertices(axesVertices_);
    axesVertexObject_.setupVertexAttribute(this, 0, 3, GL_FLOAT, GL_TRUE, sizeof(QVector3D) * 2, nullptr);
    axesVertexObject_.setupVertexAttribute(this, 1, 3, GL_FLOAT, GL_TRUE, sizeof(QVector3D) * 2, reinterpret_cast<void*>(sizeof(QVector3D)));
    axesVertexObject_.unbind_vao();
}

void GLScene::setType(std::string type) {
    type_ = type;
    update();
}

void GLScene::setFragmentationFactor(GLuint factor) {
    fragmentationFactor_ = factor;
    update();
}

void GLScene::setRotation(GLdouble x, GLdouble y, GLdouble z) {
    rotationMatrix_.setToIdentity();
    rotationMatrix_.rotate(x, 1.f, 0.f, 0.f);
    rotationMatrix_.rotate(y, 0.f, 1.f, 0.f);
    rotationMatrix_.rotate(z, 0.f, 0.f, 1.f);

    update();
}

void GLScene::setScale(GLdouble x, GLdouble y, GLdouble z) {
    scaleMatrix_.setToIdentity();
    scaleMatrix_.scale(x, y, z);

    update();
}

void GLScene::setTranslation(GLdouble x, GLdouble y, GLdouble z) {
    translationMatrix_.setToIdentity();
    translationMatrix_.translate(x, y, z);

    update();
}

void GLScene::prepareAxes() {
    axesVertices_.clear();

    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.8, 0.2, 0.2 }
    });
    axesVertices_.push_back({
        { 0.1, 0.0, 0.0 },
        { 0.8, 0.2, 0.2 }
    });

    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.2, 0.8, 0.2 }
    });
    axesVertices_.push_back({
        { 0.0, 0.1, 0.0 },
        { 0.2, 0.8, 0.2 }
    });

    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.2, 0.2, 0.8 }
    });
    axesVertices_.push_back({
        { 0.0, 0.0, 0.1 },
        { 0.2, 0.2, 0.8 }
    });
}
