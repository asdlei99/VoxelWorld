/*================================================================
Filename: BlendState.cpp
Date: 2018.1.27
Created by AirGuanZ
================================================================*/
#include "../Utility/HelperFunctions.h"
#include "../Window/Window.h"
#include "BlendState.h"

BlendState::BlendState(void)
    : BlendState(D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD,
                 D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD)
{

}

BlendState::BlendState(D3D11_BLEND src, D3D11_BLEND dst, D3D11_BLEND_OP op,
                       D3D11_BLEND srcA, D3D11_BLEND dstA, D3D11_BLEND_OP opA)
    : state_(nullptr)
{
    D3D11_BLEND_DESC dc;
    dc.AlphaToCoverageEnable = FALSE;
    dc.IndependentBlendEnable = FALSE;
    dc.RenderTarget[0].BlendEnable = TRUE;
    dc.RenderTarget[0].BlendOp = op;
    dc.RenderTarget[0].BlendOpAlpha = opA;
    dc.RenderTarget[0].DestBlend = dst;
    dc.RenderTarget[0].DestBlendAlpha = dstA;
    dc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    dc.RenderTarget[0].SrcBlend = src;
    dc.RenderTarget[0].SrcBlendAlpha = srcA;

    Window::GetInstance().GetD3DDevice()->CreateBlendState(&dc, &state_);
}

BlendState::BlendState(const BlendState &other)
{
    state_ = other.state_;
    Helper::AddRefForCOMObjects(state_);
}

BlendState &BlendState::operator=(const BlendState &other)
{
    Helper::ReleaseCOMObjects(state_);
    state_ = other.state_;
    Helper::AddRefForCOMObjects(state_);
    return *this;
}

BlendState::~BlendState(void)
{
    Helper::ReleaseCOMObjects(state_);
}

BlendState::operator ID3D11BlendState*(void)
{
    return state_;
}

ID3D11BlendState *BlendState::GetState(void)
{
    return state_;
}
