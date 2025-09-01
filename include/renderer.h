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
#include "camera.h"

class Renderer
{
    public:
        ~Renderer();                        
        int setupWindow();
        void initRenderObjects();
        void startRenderLoop();

    private:
        Cube* m_Cube;
        GLFWwindow* m_Window; 
        VertexBuffer* m_VBO;
        VertexArray* m_VAO;
        IndexBuffer* m_FaceIBO;
        IndexBuffer* m_EdgeIBO;
        Shaders* m_Shaders;
        unsigned int m_ShaderProgram;      
};