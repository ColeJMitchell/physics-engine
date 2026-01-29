#include "renderer.h"
#include <iostream>
#include <GL/glew.h>

int main()
{
    Renderer renderer;
    int renderSetupStatus = renderer.setupWindow();
    if (renderSetupStatus == -1)
    {
        return -1;
    }
    
    else
    {
        std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        renderer.initRenderObjects();
        renderer.startRenderLoop();
    }
    
    return 0;
}