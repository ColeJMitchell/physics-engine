#include <GL/glew.h>
#include <cstddef>

class VertexBuffer
{
    public:
        template <typename T>
        void createBuffer(T *bufferData, size_t count)
        {
            glGenBuffers(1, &vertexBufferId);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * count, bufferData, GL_STATIC_DRAW);
        }
        void deleteBuffer() { glDeleteBuffers(1, &vertexBufferId); };

        unsigned int vertexBufferId;
};