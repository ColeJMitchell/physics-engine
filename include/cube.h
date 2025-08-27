#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Cube
{
  public:
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

    float* getVertices() { return m_Vertices; }
    unsigned int* getIndices() { return m_Indices; }
    int getVertexStrideCount() { return 3; }
    int getVertexFloatCount() { return 24; }
    int getIndexFloatCount() { return 36; }

  private:
    //there are 8 vertices which each have 3 floats (x, y, z) to represent a cube
    float m_Vertices[8 * 3] = 
    {
      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f, 
      0.5f,  0.5f, -0.5f,  
      -0.5f,  0.5f, -0.5f, 
      -0.5f, -0.5f,  0.5f,  
      0.5f, -0.5f,  0.5f, 
      0.5f,  0.5f,  0.5f, 
      -0.5f,  0.5f,  0.5f, 
    };

    //each square face of the cube is composed of two triangles
    unsigned int m_Indices[36] =
    {
      0, 1, 2,  2, 3, 0, 
      4, 5, 6,  6, 7, 4, 
      0, 4, 7,  7, 3, 0, 
      1, 5, 6,  6, 2, 1, 
      3, 2, 6,  6, 7, 3, 
      0, 1, 5,  5, 4, 0  
    };
};