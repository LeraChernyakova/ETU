#ifndef GLMATERIAL_H
#define GLMATERIAL_H

#include <QColor>

class QOpenGLShaderProgram;

//material representation
class GLMaterial
{
public:
    GLMaterial();
    GLMaterial(
        const QColor& diffuse,
        const QColor& specular,
        float shininess = 16.f,
        float ambientStrength = 0.4f
    );

    //set material diffuse light color
    void setDiffuseColor(const QColor& color);
    //get material diffuse light color
    QColor getDiffuseColor() const;
    //set material specular light color
    void setSpecularColor(const QColor& color);
    //get material specular light color
    QColor getSpecularColor() const;
    //set material shininess
    void setShininess(float shininess);
    //get material shininess
    float getShininess() const;
    //set material ambient light strength
    void setAmbientStrength(float strength);
    //get material ambient light strength
    float getAmbientStrength() const;
    //load material info to the shader program
    void apply(QOpenGLShaderProgram* shaderProgram) const;

private:
    //material diffuse light color
    QColor diffuse_;
    //material specular light color
    QColor specular_;
    //material shininess
    float shininess_;
    //material ambient light strength
    float ambientStrength_;
};

#endif // GLMATERIAL_H
