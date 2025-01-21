#ifndef GLLIGHTING_H
#define GLLIGHTING_H

#include <QMap>
#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

class QOpenGLShaderProgram;
class QOpenGLFunctions;

//light type
enum class GLLightingType
{
    Point,
    Directional,
    Spot
};

//lighting represenation
class GLLighting
{
public:
    GLLighting(
        GLLightingType type,
        const QVector3D& position,
        const QVector3D& direction,
        const QColor& ambient = Qt::cyan,
        const QColor& diffuse = Qt::yellow,
        const QColor& specular = Qt::white
    );

    //set light type
    void setType(GLLightingType type);
    //get light type
    GLLightingType getType() const;
    //set light source position
    void setPosition(const QVector3D& position);
    //get light source position
    QVector3D getPosition() const;
    //set light direction
    void setDirection(const QVector3D& direction);
    //get light direction
    QVector3D getDirection() const;
    //set ambient light color
    void setAmbientColor(const QColor& color);
    //get ambient light color
    QColor getAmbientColor() const;
    //set diffuse light color
    void setDiffuseColor(const QColor& color);
    //get diffuse light color
    QColor getDiffuseColor() const;
    //set specular light color
    void setSpecularColor(const QColor& color);
    //get specular light color
    QColor getSpecularColor() const;
    //set attenuation coefficients: constant, linear and quadratic
    void setAttenuation(const QVector3D& attenuation);
    //get attenuation coefficients: constant, linear and quadratic
    QVector3D getAttenuation() const;
    //set spot light cut offset
    void setCutOff(float cutOff);
    //get spot light cut offset
    float getCutOff() const;
    //set spot light outer cut offset
    void setOuterCutOff(float outerCutOff);
    //get spot light outer cut offset
    float getOuterCutOff() const;
    //load lighting info to the shader program
    void apply(QOpenGLShaderProgram* shaderProgram) const;

private:
    //convert degrees to radians
    inline float d2r(float degrees) const
    {
        return 3.1459265 * degrees / 180.f;
    }

    //current light type
    GLLightingType type_;
    //light source position
    QVector3D position_;
    //light direction
    QVector3D direction_;
    //ambient light color
    QColor ambient_;
    //diffuse light color
    QColor diffuse_;
    //specular light color
    QColor specular_;
    //attenuation coefficients: constant, linear and quadratic
    QVector3D attenuation_;
    //spot light cut offset
    float cutOff_;
    //spot light outer cut offset
    float outerCutOff_;
};

#endif // GLLIGHTING_H
