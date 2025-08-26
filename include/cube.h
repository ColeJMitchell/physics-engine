#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Cube
{
  public:
    glm::mat4 scale(float x, float y, float z, glm::mat4 model);

  private:
    //there are 8 vertices which each have 6 floats
    float vertices[8 * 6] = 
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
    
    float indices[36] =
    {
      0, 1, 2,  2, 3, 0, 
      4, 5, 6,  6, 7, 4, 
      0, 4, 7,  7, 3, 0, 
      1, 5, 6,  6, 2, 1, 
      3, 2, 6,  6, 7, 3, 
      0, 1, 5,  5, 4, 0  
    }

};