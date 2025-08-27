#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
        int setupWindow();
        void initRenderObjects();
        void startRenderLoop();

    private:
        GLFWwindow* m_Window; 
        VertexBuffer* m_VBO;
        VertexArray* m_VAO;
        IndexBuffer* m_IBO;
        Shaders* m_Shaders;
        Cube* m_Cube;
        unsigned int m_ShaderProgram;      
};