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

void Renderer::renderCube(float xTranslate, float yTranslate, float zTranslate,
                          float xScale, float yScale, float zScale, 
                          float xRotate, float yRotate, float zRotate, float radians)
{
    //first three floats are scale, second three are rotation (x, y, z)
    glm::mat4 mvp = Cube::calculateMVP(xTranslate, yTranslate, zTranslate,
                                       xScale, yScale, zScale,
                                       xRotate, yRotate, zRotate, radians);

    int location = glGetUniformLocation(m_ShaderProgram, "u_MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));
       
    int colorLocation = glGetUniformLocation(m_ShaderProgram, "u_Color");

    glUniform3f(colorLocation, 1.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_FaceIBO->bind();
    glDrawElements(GL_TRIANGLES, m_Cube->getFaceIndexFloatCount(), GL_UNSIGNED_INT, nullptr);

    glUniform3f(colorLocation, 0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    m_EdgeIBO->bind(); 
    glDrawElements(GL_LINES, m_Cube->getEdgeIndexFloatCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::startRenderLoop()
{
    int radians = 0;
    int frames = 0;
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(m_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(m_ShaderProgram);
        m_VAO->bind();

        frames += 1;
        if(frames % 15 == 0) { radians += 10; }
        renderCube(-3, 0, -10, 2, 1, 1, 1, 0, 0, radians);
        renderCube(0, 0, -10, 1, 2, 1, 1, 0, 0, radians);
        renderCube(3, 0, -10, 1, 1, 2, 1, 0, 0, radians);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
