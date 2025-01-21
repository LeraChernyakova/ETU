#include "glvertexobject.h"

#include <QOpenGLFunctions>
#include <QVector3D>

GLVertexObject::GLVertexObject():
    vertexBuffer_{QOpenGLBuffer::VertexBuffer},
    elementBuffer_{QOpenGLBuffer::IndexBuffer}
{}


GLVertexObject::~GLVertexObject()
{
    elementBuffer_.destroy();
    vertexBuffer_.destroy();
    vertexArray_.destroy();
}


bool GLVertexObject::init()
{
    /* check if initialized before */
    if (initialized_)
    {
        return initialized_;
    }

    /* create vertex buffers and vertex array */
    vertexArray_.create();
    vertexBuffer_.create();
    elementBuffer_.create();

    initialized_ = true;
    return initialized_;
}


void GLVertexObject::setupVertexAttribute(
    QOpenGLFunctions* painter,
    GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const void *offset
)
{
    /* set vertex attribute pointer */
    painter->glEnableVertexAttribArray(index);
    painter->glVertexAttribPointer(index, size, type, normalized, stride, offset);
}


QOpenGLVertexArrayObject& GLVertexObject::vao()
{
    return vertexArray_;
}


const QOpenGLBuffer& GLVertexObject::vbo() const
{
    return vertexBuffer_;
}


const QOpenGLBuffer& GLVertexObject::ebo() const
{
    return elementBuffer_;
}


bool GLVertexObject::isInitialized() const
{
    return initialized_;
}


void GLVertexObject::bind_vao()
{
    if (initialized_)
    {
        vertexArray_.bind();
    }
}


void GLVertexObject::unbind_vao()
{
    if (initialized_)
    {
        vertexArray_.release();
    }
}
