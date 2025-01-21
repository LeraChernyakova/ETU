#ifndef GLFIGURE_H
#define GLFIGURE_H

#include <QMatrix4x4>
#include "glvertexobject.h"
#include "glmaterial.h"

class GLScene;

struct CircleBaseData
{
    GLfloat radius;
    GLfloat y;
};


struct TriangleIndices
{
    GLuint first;
    GLuint second;
    GLuint third;
};


class GLFigure
{
public:
    GLFigure(const QVector<CircleBaseData>& circles);


    void init(GLScene* painter);

    void draw(GLScene* painter, GLuint fragmentation = 0);

    void setRotation(const QMatrix4x4& rotationMatrix);

    void setRotation(GLfloat angle, const QVector3D& rotationAxis);

    void setScale(const QMatrix4x4& scaleMatrix);

    void setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

    void setTranslation(const QMatrix4x4& translationMatrix);

    void setTranslation(GLfloat translationX, GLfloat translationY, GLfloat translationZ);

    inline GLMaterial& getMaterial() { return material_; }

private:
    //calculate figure polygons and norms
    void calculatePolygons();
    //calculate figure vertices
    void generateCircles();
    //calculate figure vertices indices for EBO
    void generateIndices();
    //calculate polygons norms
    void generateNorms();
    //generate circle with given radius and Y coordinate
    void generateCircle(
        GLfloat radius,
        GLfloat y
    );
    //set figure attribute info
    void setAttributeInfo(QOpenGLFunctions* painter);

    //is figure has been initialized
    bool initialized_ = false;
    //is polygons recalculation needed
    bool dirty_ = true;
    //count of EBO elements
    GLuint indicesCount_;
    //current figure fragmentation factor
    GLuint fragmentation_;
    //base count of figure cut (circle) segments
    GLuint baseCircleSegmentsCount_;
    //figure base set of cuts
    const QVector<CircleBaseData> baseCircles_;
    //vertex object
    GLVertexObject vertexObject_;
    //figure vertices and norms vector
    QVector<QPair<QVector3D, QVector3D>> vertices_;
    //figure vertices indices for EBO
    QVector<TriangleIndices> indices_;
    //figure rotation matrix
    QMatrix4x4 rotation_;
    //figure scale matrix
    QMatrix4x4 scale_;
    //figure translation matrix
    QMatrix4x4 translation_;
    //inverse transposed model matrix
    QMatrix4x4 inverseTransposedModel_;
    //figure material info
    GLMaterial material_;
};

#endif // GLFIGURE_H
