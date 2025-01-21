#ifndef GLSHADERPROGRAM_H
#define GLSHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QString>
#include <QMap>

//OpenGL shader program
class GLShaderProgram: public QOpenGLShaderProgram
{
public:
    GLShaderProgram(
        const QMap<QOpenGLShader::ShaderType, QString>& shaders,
        QObject *parent = nullptr
    );
    //initialize shader program: load, compile and bind shaders
    bool init();
    bool isInitialized() const;

private:
    //shaders map
    QMap<QOpenGLShader::ShaderType, QString> shaders_;
    //is shader program has been initialized
    bool initialized_ = false;
};

#endif // GLSHADERPROGRAM_H
