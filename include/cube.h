#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Cube
{
  public:
    float* getVertices() { return m_Vertices; }
    float* getIndices() { return m_Indices; }
    int getVertexCount() { return 48; }
    int getIndexCount() { return 36; }
    int getVertexSize() { return 24; }
    int getIndexSize() { return 24; }

    static glm::mat4 scale(float x, float y, float z, glm::mat4 model)
    {
      return glm::scale(model, glm::vec3(x, y, z));
    }
    
    static glm::mat4 rotate(float x, float y, float z, float radians, glm::mat4 model)
    {
      return glm::rotate(model, radians, glm::vec3(x, y, z));
    }

    static glm::mat4 translate(float x, float y, float z, glm::mat4 model)
    {
      return glm::translate(model, glm::vec3(x, y, z));
    }

  private:
    //there are 8 vertices which each have 6 floats
    float m_Vertices[8 * 6] = 
    {
      -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.3f, 0.3f, 0.3f
    };

    float m_Indices[36] =
    {
      0, 1, 2,  2, 3, 0, 
      4, 5, 6,  6, 7, 4, 
      0, 4, 7,  7, 3, 0, 
      1, 5, 6,  6, 2, 1, 
      3, 2, 6,  6, 7, 3, 
      0, 1, 5,  5, 4, 0  
    };
};