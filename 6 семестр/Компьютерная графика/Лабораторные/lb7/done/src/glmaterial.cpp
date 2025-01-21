#include "glmaterial.h"

#include <QOpenGLShaderProgram>
#include <iostream>


GLMaterial::GLMaterial():
    GLMaterial {
        QColor{ 237, 69, 57 },
        QColor{ 205, 243, 215 },
    }
{}


GLMaterial::GLMaterial(
    const QColor& diffuse,
    const QColor& specular,
    float shininess,
    float ambientStrength
):
    diffuse_{ diffuse },
    specular_{ specular },
    shininess_{ shininess },
    ambientStrength_{ ambientStrength }
{}


void GLMaterial::setDiffuseColor(const QColor& color)
{
    diffuse_ = color;
}


QColor GLMaterial::getDiffuseColor() const
{
    return diffuse_;
}


void GLMaterial::setSpecularColor(const QColor& color)
{
    specular_ = color;
}


QColor GLMaterial::getSpecularColor() const
{
    return specular_;
}


void GLMaterial::setShininess(float shininess)
{
    shininess_ = shininess;
}


float GLMaterial::getShininess() const
{
    return shininess_;
}


void GLMaterial::setAmbientStrength(float strength)
{
    ambientStrength_ = strength;
}


float GLMaterial::getAmbientStrength() const
{
    return ambientStrength_;
}


void GLMaterial::apply(QOpenGLShaderProgram* shaderProgram) const
{
    if (!shaderProgram)
    {
        std::cerr << "[error] can't apply material settings: shader program is nullptr" << std::endl;
        return;
    }
    shaderProgram->setUniformValue("material.diffuse", QVector3D{
        diffuse_.redF(),
        diffuse_.greenF(),
        diffuse_.blueF()
    });
    shaderProgram->setUniformValue("material.specular", QVector3D{
        specular_.redF(),
        specular_.greenF(),
        specular_.blueF()
    });
    shaderProgram->setUniformValue("material.shininess", shininess_);
    shaderProgram->setUniformValue("material.ambient_strength", ambientStrength_);
}
