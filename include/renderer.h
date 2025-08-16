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
        Renderer(VertexBuffer& vertexBuffer, VertexArray& vertexArray, IndexBuffer& indexBuffer, Shaders& shaders):
        m_VertexBuffer(vertexBuffer), m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer), m_Shaders(shaders){}

        ~Renderer();

        void setupWindow();
        
        void renderLoop();

    private:
        GLFWwindow* m_Window;
        VertexBuffer m_VertexBuffer;
        VertexArray m_VertexArray;
        IndexBuffer m_IndexBuffer;
        Shaders m_Shaders;
};