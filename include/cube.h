#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Cube
{
  public:
    static glm::mat4 calculateMVP(float xTranslate, float yTranslate, float zTranslate,
                                  float xScale, float yScale, float zScale, 
                                  float xRotate, float yRotate, float zRotate, float radians)
    {
      glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 900.0f, 0.1f, 100.0f);
      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(xTranslate, yTranslate, zTranslate)); 
      glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(xScale, yScale, zScale));
      model = glm::rotate(model, glm::radians(radians), glm::vec3(xRotate, yRotate, zRotate));
      glm::mat4 mvp = projection * view * model;
      return mvp;
    }

    float* getVertices() { return m_Vertices; }
    unsigned int* getFaceIndices() { return m_FaceIndices; }
    unsigned int* getEdgeIndices() { return m_EdgeIndices; }
    int getVertexStrideCount() { return 3; }
    int getVertexFloatCount() { return 24; }
    int getFaceIndexFloatCount() { return 36; }
    int getEdgeIndexFloatCount() { return 24; }
    
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
    unsigned int m_FaceIndices[36] =
    {
      0, 1, 2,  2, 3, 0, 
      4, 5, 6,  6, 7, 4, 
      0, 4, 7,  7, 3, 0, 
      1, 5, 6,  6, 2, 1, 
      3, 2, 6,  6, 7, 3, 
      0, 1, 5,  5, 4, 0  
    };

    //edges are rendered seperately from faces
    unsigned int m_EdgeIndices[24] =
    {
      0,1, 1,2, 2,3, 3,0,
      4,5, 5,6, 6,7, 7,4, 
      0,4, 1,5, 2,6, 3,7 
    };
};