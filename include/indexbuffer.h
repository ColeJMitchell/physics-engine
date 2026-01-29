#pragma once
#include <GL/glew.h>
#include "debugging.h"

class IndexBuffer
{
    public:
        template <typename T>
        IndexBuffer(T *bufferData, size_t count)
        {
            glGenBuffers(1, &m_IndexBufferId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * count, bufferData, GL_STATIC_DRAW);
            Debugging::debug("Index Buffer");
        }

        ~IndexBuffer(){ glDeleteBuffers(1, &m_IndexBufferId); }

        void bind(){ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId); }
        
        void unbind(){ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    private:
        unsigned int m_IndexBufferId;
};