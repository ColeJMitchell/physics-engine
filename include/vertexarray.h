#include <GL/glew.h>
#include "bufferlayout.h"
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

        unsigned int getTypeByteSize(unsigned int glEnum)
        {
            switch(glEnum)
            {
                case GL_FLOAT:
                    return 4;
                case GL_INT:
                    return 4;
                case GL_BYTE:
                    return 1;
            }
            return 0;
        }

        void addBufferElement(unsigned int vertexType, unsigned int vertexCount)
        {
            m_BufferLayout.push_back({vertexCount, vertexCount * getTypeByteSize(vertexType), vertexType, sizeof(m_BufferLayout)});
        }

        void processBufferLayout()
        {
            unsigned int counter = 0;
            for(auto bufferElement : m_BufferLayout)
            {
                glEnableVertexAttribArray(counter);
                glVertexAttribPointer(counter, bufferElement.vertexCount, bufferElement.vertexType, bufferElement.normalized, bufferElement.vertexByteSize, 0);
                counter++;
            }
        }

        std::vector<BufferElement> getBufferElements() { return m_BufferLayout; }
    
    private:
        unsigned int m_VertexArrayId;
        std::vector<BufferElement> m_BufferLayout;
};