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
        void addBufferElement(unsigned int vertexType, unsigned int vertexCount)
        {
            m_BufferLayout.push_back({vertexCount, vertexCount *});
        }

    private:
        std::vector<BufferElement> m_BufferLayout;
};