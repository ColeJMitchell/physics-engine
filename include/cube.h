#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include "camera.h"
#include "indexbuffer.h"

class CubeRenderer
{
  public:
    static void renderCube(float xTranslate, float yTranslate, float zTranslate,
                           float xScale, float yScale, float zScale, 
                           float xRotate, float yRotate, float zRotate, float radians,
                           IndexBuffer* faceIBO, IndexBuffer* edgeIBO, unsigned int shaderProgram
                          )
    {
      glm::mat4 mvp = Camera::calculateMVP(xTranslate, yTranslate, zTranslate,
                                           xScale, yScale, zScale,
                                           xRotate, yRotate, zRotate, radians);

      int location = glGetUniformLocation(shaderProgram, "u_MVP");
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));
       
      int colorLocation = glGetUniformLocation(shaderProgram, "u_Color");

      glUniform3f(colorLocation, 1.0f, 0.0f, 0.0f);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      faceIBO->bind();
      glDrawElements(GL_TRIANGLES, getFaceIndexFloatCount(), GL_UNSIGNED_INT, nullptr);

      glUniform3f(colorLocation, 0.0f, 0.0f, 0.0f);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glLineWidth(2.0f);
      edgeIBO->bind(); 
      glDrawElements(GL_LINES, getEdgeIndexFloatCount(), GL_UNSIGNED_INT, nullptr);
    }

    float* getVertices() { return m_Vertices; }
    unsigned int* getFaceIndices() { return m_FaceIndices; }
    unsigned int* getEdgeIndices() { return m_EdgeIndices; }
    int getVertexStrideCount() { return 3; }
    int getVertexFloatCount() { return 24; }
    static int getFaceIndexFloatCount() { return 36; }
    static int getEdgeIndexFloatCount() { return 24; }
    
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