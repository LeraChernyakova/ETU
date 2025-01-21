#include "gllighting.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QVector4D>
#include <iostream>


GLLighting::GLLighting(
    GLLightingType type,
    const QVector3D& position,
    const QVector3D& direction,
    const QColor& ambient,
    const QColor& diffuse,
    const QColor& specular
):
    type_{ type },
    position_{ position },
    direction_{ direction },
    ambient_{ ambient },
    diffuse_{ diffuse },
    specular_{ specular },
    attenuation_{ 1.0f, 0.09f, 0.032f },
    cutOff_{ 12.5f },
    outerCutOff_{ 17.5f }
{}


void GLLighting::setType(GLLightingType type)
{
    type_ = type;
}


GLLightingType GLLighting::getType() const
{
    return type_;
}


void GLLighting::setPosition(const QVector3D& position)
{
    position_ = position;
}


QVector3D GLLighting::getPosition() const
{
    return position_;
}


void GLLighting::setDirection(const QVector3D& direction)
{
    direction_ = direction;
}


QVector3D GLLighting::getDirection() const
{
    return direction_;
}


void GLLighting::setAmbientColor(const QColor& color)
{
    ambient_ = color;
}


QColor GLLighting::getAmbientColor() const
{
    return ambient_;
}


void GLLighting::setDiffuseColor(const QColor& color)
{
    diffuse_ = color;
}


QColor GLLighting::getDiffuseColor() const
{
    return diffuse_;
}


void GLLighting::setSpecularColor(const QColor& color)
{
    specular_ = color;
}


QColor GLLighting::getSpecularColor() const
{
    return specular_;
}


void GLLighting::setAttenuation(const QVector3D& attenuation)
{
    attenuation_ = attenuation;
}


QVector3D GLLighting::getAttenuation() const
{
    return attenuation_;
}


void GLLighting::setCutOff(float cutOff)
{
    cutOff_ = cutOff;
}


float GLLighting::getCutOff() const
{
    return cutOff_;
}


void GLLighting::setOuterCutOff(float outerCutOff)
{
    outerCutOff_ = outerCutOff;
}


float GLLighting::getOuterCutOff() const
{
    return outerCutOff_;
}


void GLLighting::apply(QOpenGLShaderProgram* shaderProgram) const
{
    if (!shaderProgram)
    {
        std::cerr << "[error] can't apply lighting settings: shader program is nullptr" << std::endl;
        return;
    }

    if (GLLightingType::Point == type_)
    {
        shaderProgram->setUniformValue("light.position", position_);
        shaderProgram->setUniformValue("light.direction", QVector4D{ 0.0f, 0.0f, 0.0f, 1.f });
    } else if (GLLightingType::Directional == type_)
    {
        shaderProgram->setUniformValue("light.position", QVector3D{ 0.0f, 0.0f, 0.0f });
        shaderProgram->setUniformValue("light.direction", QVector4D{
            direction_.x(),
            direction_.y(),
            direction_.z(),
            0.f
        });
    } else if (GLLightingType::Spot == type_)
    {
        shaderProgram->setUniformValue("light.position", position_);
        shaderProgram->setUniformValue("light.direction", QVector4D{
            direction_.x(),
            direction_.y(),
            direction_.z(),
            1.f
        });
    }

    shaderProgram->setUniformValue("light.ambient", QVector3D{
        ambient_.redF(),
        ambient_.greenF(),
        ambient_.blueF()
    });
    shaderProgram->setUniformValue("light.diffuse", QVector3D{
        diffuse_.redF(),
        diffuse_.greenF(),
        diffuse_.blueF()
    });
    shaderProgram->setUniformValue("light.specular", QVector3D{
        specular_.redF(),
        specular_.greenF(),
        specular_.blueF()
    });

    shaderProgram->setUniformValue("light.attenuation_coeffs", attenuation_);

    if (GLLightingType::Spot == type_)
    {
        shaderProgram->setUniformValue("light.cut_off", std::cos(d2r(cutOff_)));
        shaderProgram->setUniformValue("light.outer_cut_off", std::cos(d2r(outerCutOff_)));
    } else
    {
        shaderProgram->setUniformValue("light.cut_off", 0.f);
        shaderProgram->setUniformValue("light.outer_cut_off", 0.f);
    }
}
