#ifndef GLVERTEXOBJECT_H
#define GLVERTEXOBJECT_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLFunctions;

//object vertices info representation
class GLVertexObject
{
public:
    GLVertexObject();
    ~GLVertexObject();
    //initialize vertex object: create VAO, VBO and EBO
    bool init();
    bool isInitialized() const;
    //bind VAO
    void bind_vao();
    //release VAO
    void unbind_vao();
    QOpenGLVertexArrayObject& vao();
    const QOpenGLBuffer& vbo() const;
    const QOpenGLBuffer& ebo() const;
    //load vertices to VBO
    template <typename VertexDataType>
    void loadVertices(
        const QVector<VertexDataType>& vertices
    )
    {
        loadVertices<VertexDataType, std::nullptr_t>(vertices, {});
    }
    //load vertices to VBO and indices to EBO
    template <typename VertexDataType, typename IndexDataType>
    void loadVertices(
        const QVector<VertexDataType>& vertices,
        const QVector<IndexDataType>& indices
    )
    {
        /* release previous buffers data */
        vertexBuffer_.release();
        elementBuffer_.release();

        /* load data to VBO */
        vertexBuffer_.bind();
        vertexBuffer_.allocate(vertices.constData(), vertices.size() * sizeof(VertexDataType));

        /* load data to EBO (if needed) */
        if (indices.size())
        {
            elementBuffer_.bind();
            elementBuffer_.allocate(indices.constData(), indices.size() * sizeof(IndexDataType));
        }
    }
    //set vertex attribute data
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
    //is vertex object has been initialized
    bool initialized_ = false;
    //VAO
    QOpenGLVertexArrayObject vertexArray_;
    //VBO
    QOpenGLBuffer vertexBuffer_;
    //EBO
    QOpenGLBuffer elementBuffer_;
};

#endif // GLVERTEXOBJECT_H
