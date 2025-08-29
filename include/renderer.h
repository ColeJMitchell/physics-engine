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

class Renderer
{
    public:
        ~Renderer();
        void renderCube(float xTranslate, float yTranslate, float zTranslate,
                        float xScale, float yScale, float zScale, 
                        float xRotate, float yRotate, float zRotate, float radians);
                        
        int setupWindow();
        void initRenderObjects();
        void startRenderLoop();

    private:
        GLFWwindow* m_Window; 
        VertexBuffer* m_VBO;
        VertexArray* m_VAO;
        IndexBuffer* m_FaceIBO;
        IndexBuffer* m_EdgeIBO;
        Shaders* m_Shaders;
        Cube* m_Cube;
        unsigned int m_ShaderProgram;      
};