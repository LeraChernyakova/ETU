#include "glfigure.h"

#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <iostream>

#include "glscene.h"


GLFigure::GLFigure(const QVector<CircleBaseData>& circles):
    baseCircleSegmentsCount_{16},
    baseCircles_{circles}
{
    rotation_.setToIdentity();
    scale_.setToIdentity();
    translation_.setToIdentity();
}


void GLFigure::init(GLScene* painter)
{
    if (initialized_)
    {
        std::cerr << "[warning] already initialized" << std::endl;
        return;
    }
    /* initialize buffers */
    initialized_ = vertexObject_.init();
    if (!initialized_)
    {
        std::cerr << "[error] can't initialize vertex object" << std::endl;
        return;
    }
    /* generate polygons for fragmentation = 1 */
    fragmentation_ = 1;
    calculatePolygons();
    setAttributeInfo(painter);
}


void GLFigure::draw(GLScene* painter, GLuint fragmentation)
{
    if (!initialized_)
    {
        std::cerr << "[error] can't draw: not initialized" << std::endl;
        return;
    }
    if (!painter)
    {
        std::cerr << "[error] can't draw: painter is nullptr" << std::endl;
        return;
    }
    vertexObject_.bind_vao();
    /* update poygons if fragmentation changed or transforms dirty */
    if (dirty_ || (fragmentation && fragmentation != fragmentation_))
    {
        /* update polygons */
        fragmentation_ = fragmentation;
        calculatePolygons();
        /* set attribute info */
        setAttributeInfo(painter);
    }
    /* apply material */
    material_.apply(painter->getFigureShaderProgram());
    /* draw polygons */
    glDrawElements(GL_TRIANGLES, indicesCount_, GL_UNSIGNED_INT, nullptr);
    vertexObject_.unbind_vao();
}


void GLFigure::setRotation(const QMatrix4x4& rotationMatrix)
{
    rotation_ = rotationMatrix;
    dirty_ = true;
}


void GLFigure::setRotation(GLfloat angle, const QVector3D& rotationAxis)
{
    rotation_.setToIdentity();
    rotation_.rotate(angle, rotationAxis);
    dirty_ = true;
}


void GLFigure::setScale(const QMatrix4x4& scaleMatrix)
{
    scale_ = scaleMatrix;
    dirty_ = true;
}


void GLFigure::setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
    scale_.setToIdentity();
    scale_.scale(scaleX, scaleY, scaleZ);
    dirty_ = true;
}


void GLFigure::setTranslation(const QMatrix4x4& translationMatrix)
{
    translation_ = translationMatrix;
    dirty_ = true;
}


void GLFigure::setTranslation(GLfloat translationX, GLfloat translationY, GLfloat translationZ)
{
    translation_.setToIdentity();
    translation_.translate(translationX, translationY, translationZ);
    dirty_ = true;
}


void GLFigure::calculatePolygons()
{
    if (!initialized_)
    {
        std::cerr << "[error] can't generate polygons: not initialized" << std::endl;
        return;
    }
    if (!baseCircles_.size())
    {
        std::cerr << "[error] can't generate polygons: base circles is empty" << std::endl;
        return;
    }
    /* recalculate inverse transposed matrix */
    inverseTransposedModel_ = rotation_ * translation_ * scale_;
    inverseTransposedModel_ = inverseTransposedModel_.inverted();
    inverseTransposedModel_ = inverseTransposedModel_.transposed();
    /* prepare data */
    generateCircles();
    generateNorms();
    generateIndices();
    /* load data to buffer */
    vertexObject_.bind_vao();
    vertexObject_.loadVertices(vertices_, indices_);    
    /* set dirty to false */
    dirty_ = false;
}


void GLFigure::generateCircles()
{
    if (!initialized_)
    {
        std::cerr << "[error] can't generate circles: not initialized" << std::endl;
        return;
    }
    if (!baseCircles_.size())
    {
        std::cerr << "[error] can't generate circles: base circles is empty" << std::endl;
        return;
    }
    /* remove previous data */
    vertices_.clear();
    /* circle parameters */
    GLfloat radius = baseCircles_.at(0).radius;
    GLfloat y = baseCircles_.at(0).y;
    /* generate circles */
    for (GLuint i = 0; i < baseCircles_.size() - 1; ++i)
    {
        /* deltas between circles parameters */
        GLfloat deltaRadius = (
            baseCircles_.at(i + 1).radius -
            baseCircles_.at(i).radius
        ) / fragmentation_;
        GLfloat deltaY = (
            baseCircles_.at(i + 1).y -
            baseCircles_.at(i).y
        ) / fragmentation_;
        /* generate intermediate circles */
        for (GLuint j = 0; j < fragmentation_; ++j)
        {
            generateCircle(radius, y);
            radius += deltaRadius;
            y += deltaY;
        }
    }
    /* generate last circle */
    generateCircle(radius, y);
}


void GLFigure::generateIndices()
{
    if (!initialized_)
    {
        std::cerr << "[error] can't generate indices: not initialized" << std::endl;
        return;
    }
    if (!vertices_.size())
    {
        std::cerr << "[error] can't generate indices: vertices is empty" << std::endl;
        return;
    }
    /* remove previous data */
    indices_.clear();
    /* circles count */
    GLuint circleSegmentsCount = fragmentation_ * baseCircleSegmentsCount_;
    GLuint circlesCount = fragmentation_ * (baseCircles_.size() - 1) + 1;
    /* generate indices for polygons */
    for (GLuint i = 0; i < circlesCount - 1; ++i)
    {
        for (GLuint j = 0; j < circleSegmentsCount - 1; ++j)
        {
            /* indices for left triangle */
            indices_.push_back({
                (i + 1) * circleSegmentsCount + j + 0,
                (i + 0) * circleSegmentsCount + j + 0,
                (i + 1) * circleSegmentsCount + j + 1,
            });
            /* indices for right triangle */
            indices_.push_back({
                (i + 1) * circleSegmentsCount + j + 1,
                (i + 0) * circleSegmentsCount + j + 0,
                (i + 0) * circleSegmentsCount + j + 1,
            });
        }
        /* connect last and first vertices */
        /* indices for left triangle */
        indices_.push_back({
            (i + 1) * circleSegmentsCount + circleSegmentsCount - 1,
            (i + 0) * circleSegmentsCount + circleSegmentsCount - 1,
            (i + 1) * circleSegmentsCount + 0,
        });
        /* indices for right triangle */
        indices_.push_back({
            (i + 1) * circleSegmentsCount + 0,
            (i + 0) * circleSegmentsCount + circleSegmentsCount - 1,
            (i + 0) * circleSegmentsCount + 0,
        });
    }
    indicesCount_ = indices_.size() * sizeof(TriangleIndices);
}


void GLFigure::generateNorms()
{
    if (!initialized_)
    {
        std::cerr << "[error] can't generate norms: not initialized" << std::endl;
        return;
    }
    if (!vertices_.size())
    {
        std::cerr << "[error] can't generate norms: vertices is empty" << std::endl;
        return;
    }

    GLuint circleSegmentsCount = fragmentation_ * baseCircleSegmentsCount_;
    GLuint circlesCount = fragmentation_ * (baseCircles_.size() - 1) + 1;
    QVector3D norm;
    QVector4D norm4;
    /* generate norms for vertices */
    for (GLuint i = 0; i < circlesCount - 1; ++i)
    {
        for (GLuint j = 0; j < circleSegmentsCount - 1; ++j)
        {
            /* norms has to be rotated, translated and scaled like vertices */
            norm4 = inverseTransposedModel_ * QVector4D(
                QVector3D::normal(
                    vertices_.at((i + 0) * circleSegmentsCount + j + 0).first, // 0 vertex position
                    vertices_.at((i + 0) * circleSegmentsCount + j + 1).first, // right vertex position
                    vertices_.at((i + 1) * circleSegmentsCount + j + 0).first  // down vertex position
                ),
                1.0f
            );
            norm = QVector3D{ norm4.x(), norm4.y(), norm4.z() };
            /* set all polygon vertices norms */
            vertices_[(i + 0) * circleSegmentsCount + j + 0].second = norm;
            vertices_[(i + 0) * circleSegmentsCount + j + 1].second = norm;
            vertices_[(i + 1) * circleSegmentsCount + j + 0].second = norm;
            vertices_[(i + 1) * circleSegmentsCount + j + 1].second = norm;
        }
    }
}


void GLFigure::generateCircle(
    GLfloat radius,
    GLfloat y
)
{
    if (!initialized_)
    {
        std::cerr << "[error] can't generate circle: not initialized" << std::endl;
        return;
    }
    GLuint circleSegmentsCount = fragmentation_ * baseCircleSegmentsCount_;
    GLfloat angle = 0.f;
    GLfloat deltaAngle = 2.0f * 3.14159265f / circleSegmentsCount;
    QVector4D vertex;
    /* generate circle segments */
    for (GLuint i = 0; i < circleSegmentsCount; ++i)
    {
        /* apply all transformations */
        vertex = translation_ * rotation_ * scale_ * QVector4D{
            radius * std::cos(angle),
            y,
            radius * std::sin(angle),
            1.f
        };
        /* save transformed vertex */
        vertices_.push_back({
            {
                vertex.x(),
                vertex.y(),
                vertex.z()
            },
            {1.f, 1.f, 1.f} // temporary norm
        });
        angle += deltaAngle;
    }
}


void GLFigure::setAttributeInfo(QOpenGLFunctions* painter)
{
    if (!initialized_)
    {
        std::cerr << "[error] can't set attribure pointer: not initialized" << std::endl;
        return;
    }
    if (!painter)
    {
        std::cerr << "[error] can't set attribure pointer: painter is nullptr" << std::endl;
        return;
    }
    /* set attribure info */
    vertexObject_.bind_vao();
    /* set position info */
    vertexObject_.setupVertexAttribute(
        painter, 0, 3, GL_FLOAT, GL_FALSE,
        2 * sizeof(QVector3D), nullptr
    );
    /* set norm info */
    vertexObject_.setupVertexAttribute(
        painter, 1, 3, GL_FLOAT, GL_TRUE,
        2 * sizeof(QVector3D), reinterpret_cast<void*>(sizeof(QVector3D))
    );
}
