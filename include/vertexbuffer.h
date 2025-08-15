#include <GL/glew.h>
#include <cstddef>
#include <debugging.h>

class VertexBuffer
{
    public:
        template <typename T>
        VertexBuffer(T* bufferData, size_t count)
        {
            glGenBuffers(1, &m_VertexBufferId);
            glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * count, bufferData, GL_STATIC_DRAW);
            Debugging::debug("Vertex Buffer");
        }

        ~VertexBuffer(){ glDeleteBuffers(1, &m_VertexBufferId); }

        void bind(){ glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId); }
        
        void unbind(){ glBindBuffer(GL_ARRAY_BUFFER, 0); }

    private:
        unsigned int m_VertexBufferId;
};