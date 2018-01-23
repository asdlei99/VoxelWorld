/*================================================================
Filename: CarveRenderer.h
Date: 2018.1.21
Created by AirGuanZ
================================================================*/
#ifndef VW_CARVE_RENDERER_H
#define VW_CARVE_RENDERER_H

#include <memory>
#include <string>

#include <OWEShader.hpp>

#include "../D3DObject/RasterState.h"
#include "../Utility/D3D11Header.h"
#include "../Utility/Math.h"
#include "../Utility/Uncopiable.h"
#include "BasicRenderer.h"

constexpr int CARVE_RENDERER_TEXTURE_NUM = 1;
constexpr int CARVE_RENDERER_TEXTURE_BLOCK_SIZE = 16;

class CarveRenderer : public Uncopiable
{
public:
    using ShaderType = OWE::Shader<SS_VS, SS_PS>;
    using Uniforms = OWE::ShaderUniforms<SS_VS, SS_PS>;

    using Vertex = typename BasicRenderer::Vertex;

    CarveRenderer(void);
    ~CarveRenderer(void);

    bool Initialize(std::string &errMsg);
    void Destroy(void);
    bool IsAvailable(void) const;

    void Begin(void);
    void End(void);

    ShaderType &GetShader(void);

private:
    ID3D11InputLayout *inputLayout_;
    ShaderType shader_;

    std::unique_ptr<RasterState> raster_;
};

#endif //VW_CARVE_RENDERER_H
