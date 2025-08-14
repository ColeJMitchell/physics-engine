#include <GL/glew.h>
#include "debugging.h"

class IndexBuffer
{
    public:
        template <typename T>
        void createBuffer(T *bufferData, size_t count)
        {
            glGenBuffers(1, &m_IndexBufferId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * count, bufferData, GL_STATIC_DRAW);
            Debugging::debug("Index Buffer");
        }

        void bindBuffer() { glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferId); }

        void unbindBuffer() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

        void deleteBuffer() { glDeleteBuffers(1, &m_IndexBufferId); }

    private:
        unsigned int m_IndexBufferId;
};