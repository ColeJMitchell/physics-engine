#include "vertexbuffer.h"
#include "GL/glew.h"

template <typename T>
void VertexBuffer::createBuffer(T &bufferData)
{
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
}
