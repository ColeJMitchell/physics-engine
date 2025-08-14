#include <GL/glew.h>
#include <vector>

struct BufferElement
{
    unsigned int vertexCount;
    unsigned int vertexByteSize;
    unsigned int vertexType;
    unsigned int offset;
    bool normalized;
};

class BufferLayout
{
    public:
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
        }

        void addBufferElement(unsigned int vertexType, unsigned int vertexCount)
        {
            m_BufferLayout.push_back({vertexCount, vertexCount * getTypeByteSize(vertexType), vertexType, sizeof(m_BufferLayout)});
        }

        std::vector<BufferElement> getBufferElements() { return m_BufferLayout; }

    private:
        std::vector<BufferElement> m_BufferLayout;
};