#include "glshaderprogram.h"

GLShaderProgram::GLShaderProgram(
    const QMap<QOpenGLShader::ShaderType, QString>& shaders,
    QObject *parent
):
    QOpenGLShaderProgram{parent},
    shaders_{shaders}
{}


bool GLShaderProgram::init()
{
    /* check if initialized before */
    if (isInitialized())
    {
        return initialized_;
    }

    initialized_ = true;
    /* compile all given shaders */
    for (const auto& [type, path]: shaders_.asKeyValueRange())
    {
        initialized_ = initialized_ && addShaderFromSourceFile(type, path);
    }
    /* link and bind shader program */
    initialized_ = initialized_ && link() && bind();

    return initialized_;
}


bool GLShaderProgram::isInitialized() const
{
    return initialized_;
}
