#include "renderer.h"

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