#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer
{
    public:
        void setupWindow();
        void renderLoop();

    private:
        GLFWwindow* m_Window;
};