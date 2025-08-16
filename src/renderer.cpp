#include "renderer.h"

Renderer::~Renderer()
{
    m_VBO->unbind();
    m_VAO->unbind();
    m_IBO->unbind();
    delete m_VBO;
    delete m_VAO;
    delete m_IBO;
    delete m_Shaders;
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

int Renderer::setupWindow()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    m_Window = glfwCreateWindow(800, 600, "Physics Engine", nullptr, nullptr);

    if(!m_Window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(m_Window);
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //check if the shader did not compile properly in constructor
    if (m_ShaderProgram == 0) 
    {
        std::cerr << "Failed to create shader program" << std::endl;
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        return -1;
    }

    Debugging::debug("Window Setup");
    return 0;
}

void Renderer::initRenderObjects()
{
    m_VBO = new VertexBuffer(vertices, (sizeof(vertices) / sizeof(vertices[0])));
    m_VAO = new VertexArray();
    m_IBO = new IndexBuffer(indices, sizeof(indices) / sizeof(indices[0]));
    m_Shaders = new Shaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    m_VAO->addBufferElement(GL_FLOAT, 2);
    m_VAO->processBufferLayout();
    m_ShaderProgram = m_Shaders->getShaderProgram();
}

void Renderer::startRenderLoop()
{
    while(!glfwWindowShouldClose(m_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        m_VAO->bind();
        glUseProgram(m_ShaderProgram);
        int location = glGetUniformLocation(m_ShaderProgram, "u_Color");
        glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}