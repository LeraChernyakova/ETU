#ifndef GLVERTEXOBJECT_H
#define GLVERTEXOBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLFunctions;

class GLVertexObject {
public:
    GLVertexObject();
    ~GLVertexObject();

    bool init();
    bool isInitialized() const;

    void bind_vao();
    void unbind_vao();

    QOpenGLVertexArrayObject& vao();
    const QOpenGLBuffer& vbo() const;
    const QOpenGLBuffer& ebo() const;

    template <typename VertexDataType>
    void loadVertices(const QVector<VertexDataType>& vertices) {
        loadVertices<VertexDataType, std::nullptr_t>(vertices, {});
    }

    template <typename VertexDataType, typename IndexDataType>
    void loadVertices(
        const QVector<VertexDataType>& vertices,
        const QVector<IndexDataType>& indices
    )
    {
        vertexBuffer_.release();
        elementBuffer_.release();

        vertexBuffer_.bind();
        vertexBuffer_.allocate(vertices.constData(), vertices.size() * sizeof(VertexDataType));

        if (indices.size()) {
            elementBuffer_.bind();
            elementBuffer_.allocate(indices.constData(), indices.size() * sizeof(IndexDataType));
        }
    }

    void setupVertexAttribute(
        QOpenGLFunctions* painter,
        GLuint index,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const void *offset
    );

private:
    bool initialized_ = false;

    QOpenGLVertexArrayObject vertexArray_;
    QOpenGLBuffer vertexBuffer_;
    QOpenGLBuffer elementBuffer_;
};

#endif // GLVERTEXOBJECT_H
