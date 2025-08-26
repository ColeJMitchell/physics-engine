#include "renderer.h"
#include "iostream"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

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
        renderer.initRenderObjects();
        renderer.startRenderLoop();
    }
    
    return 0;
}