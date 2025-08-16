#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shaders.h"
#include "renderer.h"
#include "debugging.h"

class Renderer
{
    public:
        float vertices[8] = 
        {
            -0.5f, -0.5f,
            0.5f,  -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f,
        };
    

        unsigned int indices[6] = 
        {
            0, 1, 2, 
            2, 3, 0  
        };

        ~Renderer();

        int setupWindow();

        void initRenderObjects();

        void startRenderLoop();

    private:
        GLFWwindow* m_Window; 
        VertexBuffer* m_VBO;
        VertexArray* m_VAO;
        IndexBuffer* m_IBO;
        Shaders* m_Shaders;
        unsigned int m_ShaderProgram;      
};