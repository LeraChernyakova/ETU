#include "glscene.h"

#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>


GLScene::GLScene(QWidget* parent):
    QOpenGLWidget{ parent },
    lighting_{ GLLightingType::Point, { 1.2f, 1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f } },
    camera_{ { 800.f, 600.f } }
{
    /* generate vector of 6 figures */
    generateFigures();

    width_ = width();
    height_ = height();

    modelMatrix_.setToIdentity();
    projectionMatrix_.setToIdentity();
}


void GLScene::initializeGL()
{
    /* init opengl window */
    QColor bgc(0x3F, 0x3F, 0x3F);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());
    /* create figures shader program */
    createShaderProgram();
    /* initialize figures shader programs */
    if (!figureShaderProgram_->init())
    {
        std::cerr << "[error] Unable to initialize Figure Shader Program" << std::endl;
        std::cerr << "Shader Program log: " << figureShaderProgram_->log().toStdString() << std::endl;
        return;
    }
    /* initialize axes shader programs */
    if (!axesShaderProgram_->init())
    {
        std::cerr << "[error] Unable to initialize Axes Shader Program" << std::endl;
        std::cerr << "Shader Program log: " << axesShaderProgram_->log().toStdString() << std::endl;
        return;
    }
    /* initialize light source shader programs */
    if (!lightSourceShaderProgram_->init())
    {
        std::cerr << "[error] Unable to initialize Light Source Shader Program" << std::endl;
        std::cerr << "Shader Program log: " << lightSourceShaderProgram_->log().toStdString() << std::endl;
        return;
    }
    /* initialize axes vertex object */
    axesVertexObject_.init();
    generateAxes();
    /* initialize all figures */
    for (auto figure: figures_)
    {
        figure->init(this);
    }
    /* initialize light source */
    lightSource_->init(this);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
}


void GLScene::resizeGL(int w, int h)
{
    width_ = w;
    height_ = h;
    /* update camera window size */
    camera_.resize( { width_, height_ } );
    /* update projection matrix */
    setProjectionType(projection_);
}


void GLScene::paintGL()
{
    figureShaderProgram_->bind();
    glLineWidth(1.0f);
    /* set scene transformations */
    figureShaderProgram_->setUniformValue("model", modelMatrix_);
    figureShaderProgram_->setUniformValue("view", camera_.getView());
    figureShaderProgram_->setUniformValue("projection", projectionMatrix_);
    /* set scene lighting params */
    lighting_.apply(figureShaderProgram_);
    figureShaderProgram_->setUniformValue("cameraPos", camera_.getPosition());
    /* draw figures */
    for (auto figure: figures_)
    {
        figure->draw(this, fragmentationFactor_);
    }
    figureShaderProgram_->release();

    /* draw axes */
    axesShaderProgram_->bind();
    axesVertexObject_.bind_vao();
    glLineWidth(3.0f);
    /* set axes rotation */
    {
        int rotationMatrixLocation = axesShaderProgram_->uniformLocation("rotation");
        axesShaderProgram_->setUniformValue(rotationMatrixLocation, camera_.getRotation());
    }
    glDrawArrays(GL_LINES, 0, 6);
    axesVertexObject_.unbind_vao();
    axesShaderProgram_->release();

    /* draw light source */
    lightSourceShaderProgram_->bind();
    lightSourceShaderProgram_->setUniformValue("model", modelMatrix_);
    lightSourceShaderProgram_->setUniformValue("view", camera_.getView());
    lightSourceShaderProgram_->setUniformValue("projection", projectionMatrix_);
    lightSourceShaderProgram_->setUniformValue("cameraPos", camera_.getPosition());
    if (lighting_.getType() != GLLightingType::Directional)
    {
        lightSource_->setTranslation(
            -lighting_.getPosition().x(),
            -lighting_.getPosition().y(),
            -lighting_.getPosition().z()
        );
        lighting_.apply(lightSourceShaderProgram_);
        lightSource_->draw(this, fragmentationFactor_);
    }
    lightSourceShaderProgram_->release();
}


void GLScene::createShaderProgram()
{
    QMap<QOpenGLShader::ShaderType, QString> figureShaders;

    figureShaders[QOpenGLShader::Vertex] = ":/shaders/figure.vert";
    figureShaders[QOpenGLShader::Fragment] = ":/shaders/figure.frag";

    figureShaderProgram_ = new GLShaderProgram(figureShaders, this);

    QMap<QOpenGLShader::ShaderType, QString> axesShaders;

    axesShaders[QOpenGLShader::Vertex] = ":/shaders/axes.vert";
    axesShaders[QOpenGLShader::Fragment] = ":/shaders/axes.frag";

    axesShaderProgram_ = new GLShaderProgram(axesShaders, this);

    QMap<QOpenGLShader::ShaderType, QString> lightSourceShaders;

    lightSourceShaders[QOpenGLShader::Vertex] = ":/shaders/lightSource.vert";
    lightSourceShaders[QOpenGLShader::Fragment] = ":/shaders/lightSource.frag";

    lightSourceShaderProgram_ = new GLShaderProgram(lightSourceShaders, this);
}


void GLScene::generateFigures()
{
    /* generate different scene objects */
    GLfloat pi = 3.14159265f;

    QVector<CircleBaseData> base1;
    for (GLfloat y = 0.700f; y >= -0.701f; y -= 0.01)
    {
        base1.push_back({
            0.70f * std::abs(
                std::sin(y / 0.70f * 0.40f * pi)
            ), y
        });
    }
    for (GLfloat y = -0.700f; y <= 0.701f; y += 0.01)
    {
        base1.push_back({
            0.75f * std::sin(
                std::abs(y) / 0.70f * 0.70f * pi
            ) + 0.25f, y
        });
    }
    base1.push_back({0.70f, 0.70f});
    figures_.push_back(std::make_shared<GLFigure>(base1));
    figures_.last()->setScale(0.25f, 0.25f, 0.25f);
    figures_.last()->setRotation(20.f, { 0.3f, 1.f, 0.5f });
    figures_.last()->setTranslation(-0.6f, 0.5f, -0.1f);
    figures_.last()->getMaterial().setDiffuseColor(Qt::green);

    QVector<CircleBaseData> base2;
    for (GLfloat y = 0.700f; y >= -0.701f; y -= 0.01)
    {
        base2.push_back({
            0.0001f * std::exp(std::abs(y) / 0.70f * 9.1f) + 0.05f,
            y,
        });
    }
    figures_.push_back(std::make_shared<GLFigure>(base2));
    figures_.last()->setScale(0.3f, 0.3f, 0.3f);
    figures_.last()->setRotation(-40.f, { 1.f, 0.f, 0.2f });
    figures_.last()->setTranslation(0.25f, -0.5f, 0.1f);
    figures_.last()->getMaterial().setDiffuseColor(Qt::yellow);

    QVector<CircleBaseData> base3;
    for (GLfloat y = 0.700f; y >= -0.701f; y -= 0.01)
    {
        base3.push_back({
            0.0001f * std::exp(y / 0.70f * 9.1f) + 0.015f + 0.03f * (y + 0.70f),
            y,
        });
    }
    figures_.push_back(std::make_shared<GLFigure>(base3));
    figures_.last()->setScale(0.35f, 0.35f, 0.35f);
    figures_.last()->setRotation(-20.f, { 0.f, 1.f, 1.f });
    figures_.last()->setTranslation(0.1f, 0.5f, 0.3f);
    figures_.last()->getMaterial().setDiffuseColor(Qt::cyan);

    QVector<CircleBaseData> base4;
    for (GLfloat y = 0.450f; y >= -0.451f; y -= 0.01)
    {
        base4.push_back({
            0.5f - std::sqrt(0.4500000001f * 0.4500000001f - y * y),
            y
        });
    }
    for (GLfloat y = -0.450f; y <= 0.451f; y += 0.01)
    {
        base4.push_back({
            0.5f + std::sqrt(0.4500000001f * 0.4500000001f - y * y),
            y
        });
    }
    base4.push_back({0.50f, 0.45f});
    figures_.push_back(std::make_shared<GLFigure>(base4));
    figures_.last()->setScale(0.3f, 0.3f, 0.3f);
    figures_.last()->setRotation(-50.f, { 1.f, 1.f, 0.f });
    figures_.last()->setTranslation(-0.6f, -0.3f, -0.4f);
    figures_.last()->getMaterial().setDiffuseColor(QColor{ 52, 229, 235 });

    QVector<CircleBaseData> baseLightSource;
    for (GLfloat y = 0.450f; y >= -0.451f; y -= 0.01)
    {
        baseLightSource.push_back({
            0.450f * std::sin(std::acos(std::abs(y) / 0.450f)),
            y
        });
    }
    lightSource_ = std::make_shared<GLFigure>(baseLightSource);
    lightSource_->setScale(0.2f, 0.2f, 0.2f);
}


void GLScene::generateAxes()
{
    /* x axis */
    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.8, 0.2, 0.2 }
    });
    axesVertices_.push_back({
        { 0.1, 0.0, 0.0 },
        { 0.8, 0.2, 0.2 }
    });
    /* y axis */
    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.2, 0.8, 0.2 }
    });
    axesVertices_.push_back({
        { 0.0, 0.1, 0.0 },
        { 0.2, 0.8, 0.2 }
    });
    /* z axis */
    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.2, 0.2, 0.8 }
    });
    axesVertices_.push_back({
        { 0.0, 0.0, 0.1 },
        { 0.2, 0.2, 0.8 }
    });
    /* load axes data to axes buffer */
    axesVertexObject_.bind_vao();
    axesVertexObject_.loadVertices(axesVertices_);
    axesVertexObject_.setupVertexAttribute(
        this, 0, 3, GL_FLOAT, GL_TRUE,
        sizeof(QVector3D) * 2,
        nullptr
    );
    axesVertexObject_.setupVertexAttribute(
        this, 1, 3, GL_FLOAT, GL_TRUE,
        sizeof(QVector3D) * 2,
        reinterpret_cast<void*>(sizeof(QVector3D))
    );
    axesVertexObject_.unbind_vao();
}


void GLScene::keyPressEvent(QKeyEvent* event)
{
    GLint forward = 0;
    GLint right = 0;

    if (event->key() == Qt::Key_W)
    {
        forward += 1;
    }
    if (event->key() == Qt::Key_S)
    {
        forward -= 1;
    }
    if (event->key() == Qt::Key_D)
    {
        right += 1;
    }
    if (event->key() == Qt::Key_A)
    {
        right -= 1;
    }

    camera_.move(forward, right);
    update();
}


void GLScene::mousePressEvent(QMouseEvent *event)
{
    camera_.mousePress(event->position());
}


void GLScene::mouseMoveEvent(QMouseEvent *event)
{
    camera_.rotate(event->position());
    update();
}


void GLScene::setProjectionType(GLProjectionType type)
{
    float aspectRatio = width_ / height_;
    projection_ = type;
    projectionMatrix_.setToIdentity();
    // set projection matrix
    switch (projection_)
    {
        case GLProjectionType::Perspective:
            projectionMatrix_.perspective(45.0f, aspectRatio, 0.01f, 100.0f);
            break;
        case GLProjectionType::Orthographic:
            projectionMatrix_.ortho(
                -1.0f * aspectRatio,
                1.0f * aspectRatio,
                -1.0f,
                1.0f,
                -8.f,
                8.f
            );
            break;
        default:
            break;
    }
}
