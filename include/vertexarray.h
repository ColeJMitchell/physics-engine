#pragma once
#include <GL/glew.h>
#include <vector>
#include "debugging.h"

struct BufferElement
{
    unsigned int vertexCount;
    unsigned int vertexByteSize;
    unsigned int vertexType;
    unsigned int offset;
    bool normalized;
};

class VertexArray
{
    public:
        VertexArray()
        {
            glGenVertexArrays(1, &m_VertexArrayId);
            glBindVertexArray(m_VertexArrayId);
            Debugging::debug("Vertex Array");
        }

        ~VertexArray() { glDeleteVertexArrays(1, &m_VertexArrayId); }

        unsigned int getEnumByteSize(unsigned int glEnum)
        {
            switch(glEnum)
            {
                case GL_FLOAT:
                    return 4;
                case GL_INT:
                    return 4;
                case GL_BYTE:
                    return 1;
                default:
                    return 0;
            }
        }
    
        void addBufferElement(unsigned int vertexType, unsigned int vertexCount)
        {
            unsigned int byteSize = vertexCount * getEnumByteSize(vertexType);
            BufferElement element = {vertexCount, byteSize, vertexType, m_Stride, true};
            m_BufferLayout.push_back(element);
            m_Stride += byteSize; 
        }

        void processBufferLayout()
        {
            unsigned int counter = 0;
            for (auto &bufferElement : m_BufferLayout)
            {
                glEnableVertexAttribArray(counter);
                glVertexAttribPointer(
                    counter,
                    bufferElement.vertexCount,
                    bufferElement.vertexType,
                    bufferElement.normalized,
                    m_Stride,                             
                    reinterpret_cast<void*>(bufferElement.offset) 
                );
            counter++;
            }
        }

        void bind(){ glBindVertexArray(m_VertexArrayId); }

        void unbind(){ glBindVertexArray(0); }

        std::vector<BufferElement> getBufferElements(){ return m_BufferLayout; }
    
    private:
        unsigned int m_Stride = 0;
        unsigned int m_VertexArrayId;
        std::vector<BufferElement> m_BufferLayout;
};