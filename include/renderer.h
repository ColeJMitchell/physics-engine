#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shaders.h"
#include "renderer.h"
#include "debugging.h"
#include "cube.h"

struct Camera
{
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    Camera(glm::vec3 e, glm::vec3 c, glm::vec3 u): 
           eye(e), center(c), up(u) {}
};

class Renderer
{
    public:
        ~Renderer();
        glm::mat4 calculateMVP(float xTranslate, float yTranslate, float zTranslate,
                               float xScale, float yScale, float zScale, 
                               float xRotate, float yRotate, float zRotate, float radians);
 
        void renderCube(float xTranslate, float yTranslate, float zTranslate,
                        float xScale, float yScale, float zScale, 
                        float xRotate, float yRotate, float zRotate, float radians);
                        
        int setupWindow();
        void initRenderObjects();
        void startRenderLoop();

    private:
        Camera* m_Camera;
        Cube* m_Cube;
        GLFWwindow* m_Window; 
        VertexBuffer* m_VBO;
        VertexArray* m_VAO;
        IndexBuffer* m_FaceIBO;
        IndexBuffer* m_EdgeIBO;
        Shaders* m_Shaders;
        unsigned int m_ShaderProgram;      
};