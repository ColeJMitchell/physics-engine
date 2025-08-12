class VertexBuffer
{
    public:
        template <typename T>
        void createBuffer(T &bufferData);
        void deleteBuffer();
        unsigned int vertexBufferId;
};