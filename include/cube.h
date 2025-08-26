class Cube
{
  public:
    static const int vertexLength = 6 * 8;

  private:
    float vertices[vertexLength] = {
      -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.3f, 0.3f, 0.3f
  };
};