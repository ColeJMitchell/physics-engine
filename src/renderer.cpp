#include "renderer.h"

Renderer::~Renderer()
{
    m_VBO->unbind();
    m_VAO->unbind();
    m_FaceIBO->unbind();
    m_EdgeIBO->unbind();
    delete m_VBO;
    delete m_VAO;
    delete m_FaceIBO;
    delete m_EdgeIBO;
    delete m_Shaders;
    delete m_Cube;
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

    m_Window = glfwCreateWindow(1200, 900, "Physics Engine", nullptr, nullptr);
    glViewport(0, 0, 1200, 900);

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
    m_Cube = new Cube();
    m_VBO = new VertexBuffer(m_Cube->getVertices(), m_Cube->getVertexFloatCount());
    m_VAO = new VertexArray();
    m_FaceIBO = new IndexBuffer(m_Cube->getFaceIndices(), m_Cube->getFaceIndexFloatCount());
    m_EdgeIBO = new IndexBuffer(m_Cube->getEdgeIndices(), m_Cube->getEdgeIndexFloatCount());
    m_Shaders = new Shaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    m_VAO->addBufferElement(GL_FLOAT, m_Cube->getVertexStrideCount());
    m_VAO->processBufferLayout();
    m_ShaderProgram = m_Shaders->getShaderProgram();
}

void Renderer::startRenderLoop()
{
    int radians = 0;
    int frames = 0;
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(m_Window))
    {
        if(glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS){ Camera::updateEyeYPosition(.2); }
        if(glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS){ Camera::updateEyeYPosition(-.2); }
        if(glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS){ Camera::updateEyeXPosition(.2); }
        if(glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS){ Camera::updateEyeXPosition(-.2); }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(m_ShaderProgram);
        m_VAO->bind();

        frames += 1;
        if(frames % 15 == 0) { radians += 10; }

        //first three floats are translation
        //second three floats are scale
        //last three are rotation (x, y, z)
        Cube::renderCube(-3, 0, -10, 2, 1, 1, 1, 0, 0, radians, m_FaceIBO, m_EdgeIBO, m_ShaderProgram);
        Cube::renderCube(0, 0, -10, 1, 2, 1, 1, 0, 0, radians, m_FaceIBO, m_EdgeIBO, m_ShaderProgram);
        Cube::renderCube(3, 0, -10, 1, 1, 2, 1, 0, 0, radians, m_FaceIBO, m_EdgeIBO, m_ShaderProgram);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
