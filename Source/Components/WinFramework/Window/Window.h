/*================================================================
Filename: Window.h
Date: 2018.1.12
Created by AirGuanZ
================================================================*/
#pragma once

#include <string>
#include <vector>

#include <Utility\D3D11Header.h>
#include <Utility\Singleton.h>

struct ImFontSpec;

class Window : public Singleton<Window>
{
public:
    bool InitWindow(int clientWidth, int clientHeight, const wchar_t *windowTitle, std::string &errMsg);
    bool InitD3D(int sampleCount, int sampleQuality, std::string &errMsg);
    bool InitGUI(const std::vector<ImFontSpec> &fonts, std::string &errMsg);

    bool IsWindowAvailable(void);
    bool IsD3DAvailable(void);

    void Destroy(void);

    int GetClientWidth(void);
    int GetClientHeight(void);
    float GetClientAspectRatio(void);

    void SetVsync(bool vsync);

    void SetDefaultViewport(void);
    void SetDefaultRTVAndDSV(void);

    void SetBackgroundColor(float r, float g, float b, float a);
    void ClearRenderTarget(void);
    void ClearDepthStencil(void);

    //ClientCentre返回值为屏幕坐标而非客户区坐标

    int ClientCentreX(void);
    int ClientCentreY(void);

    void DoEvents(void);
    void Present(void);

    void SetFullscreen(bool fullscreen);

    ID3D11Device *GetD3DDevice(void);
    ID3D11DeviceContext *GetD3DDeviceContext(void);

    HWND GetWindowHandle(void);
    HINSTANCE GetProgramHandle(void);

    //取得运行目录
    const std::string &GetProgramPath(void);

    bool OpenFileName(const std::string &initDir, std::string &output);
    bool SaveFileName(const std::string &initDir, std::string &output);
    void ErrMsgBox(const std::string &errMsg);
};
