#ifndef GLSHADERPROGRAM_H
#define GLSHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QString>
#include <QMap>

class GLShaderProgram: public QOpenGLShaderProgram {
public:
    GLShaderProgram(
        const QMap<QOpenGLShader::ShaderType, QString>& shaders,
        QObject *parent = nullptr
    );
    bool init();
    bool isInitialized() const;

private:
    QMap<QOpenGLShader::ShaderType, QString> shaders_;
    bool initialized_ = false;
};

#endif // GLSHADERPROGRAM_H
