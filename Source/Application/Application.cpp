/*================================================================
Filename: Application.cpp
Date: 2018.1.13
Created by AirGuanZ
================================================================*/
#include <stdexcept>
#include <string>

#include <Windows.h>

#include "../Texture/TextureFile.h"
#include "../Window/Window.h"
#include "Application.h"

void Application::Run(void)
{
    std::string initErrMsg;
    Window &window = Window::GetInstance();
    if(!window.InitWindow(640, 480, L"Voxel World", initErrMsg) ||
       !window.InitD3D(1, 0, initErrMsg))
    {
        throw std::runtime_error(initErrMsg.c_str());
    }

    window.SetBackgroundColor(0.0f, 1.0f, 1.0f, 0.0f);

    while(!(GetKeyState(VK_ESCAPE) & 0x8000))
    {
        window.ClearRenderTarget();
        window.ClearDepthStencil();

        window.Present();
        window.DoEvents();
    }

    window.Destroy();
}
