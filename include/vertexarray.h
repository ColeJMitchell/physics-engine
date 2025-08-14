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
                    return -1;
            }
        }

        void addBufferElement(unsigned int vertexType, unsigned int vertexCount)
        {
            m_BufferLayout.push_back({vertexCount, vertexCount * getEnumByteSize(vertexType), vertexType, sizeof(m_BufferLayout), true});
        }

        void processBufferLayout()
        {
            unsigned int counter = 0;
            unsigned int offset = 0;
            for(auto bufferElement : m_BufferLayout)
            {
                glEnableVertexAttribArray(counter);
                glVertexAttribPointer(counter, bufferElement.vertexCount, bufferElement.vertexType, bufferElement.normalized, bufferElement.vertexByteSize, 0);
                counter++;
                offset += bufferElement.offset;
            }
        }

        std::vector<BufferElement> getBufferElements() { return m_BufferLayout; }
    
    private:
        unsigned int m_VertexArrayId;
        std::vector<BufferElement> m_BufferLayout;
};