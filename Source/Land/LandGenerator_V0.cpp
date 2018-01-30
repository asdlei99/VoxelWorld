/*================================================================
Filename: LandGenerator_V0.cpp
Date: 2018.1.21
Created by AirGuanZ
================================================================*/
#include "../Chunk/Chunk.h"
#include "../Chunk/ChunkTraversal.h"
#include "LandGenerator_V0.h"
#include "OakGenerator_V0.h"

LandGenerator_V0::LandGenerator_V0(Seed seed)
    : seed_(seed)
{

}

void LandGenerator_V0::GenerateLand(Chunk *ck)
{
    assert(ck != nullptr);

    Chunk::BlockTypeData &data = ck->blocks;
    Chunk::HeightMap &heightMap = ck->heightMap;
    Chunk::BlockLightData &lights = ck->lights;

    IntVectorXZ ckPos = ck->GetPosition();
    int xBase = ChunkXZ_To_BlockXZ(ckPos.x);
    int zBase = ChunkXZ_To_BlockXZ(ckPos.z);
    for(int x = 0; x != CHUNK_SECTION_SIZE; ++x)
    {
        for(int z = 0; z != CHUNK_SECTION_SIZE; ++z)
        {
            int h = GetHeight(x + xBase, z + zBase);

            ck->SetBlockType(x, 0, z, BlockType::Bedrock);

            for(int y = 1; y != h - 2; ++y)
                ck->SetBlockType(x, y, z, BlockType::Stone);

            for(int y = h - 2; y != h; ++y)
                ck->SetBlockType(x, y, z, BlockType::Dirt);

            constexpr int WATER_LEVEL = 40;
            if(h < WATER_LEVEL)
            {
                for(int y = h; y <= WATER_LEVEL; ++y)
                    ck->SetBlockType(x, y, z, BlockType::Water);
                h = WATER_LEVEL;
            }
            else
            {
                ck->SetBlockType(x, h, z, BlockType::GrassBox);

                float gfv = Random(1, x + xBase, z + zBase, 0.0f, 1.0f);
                if(gfv < 0.1f)
                    ck->SetBlockType(x, ++h, z, BlockType::Grass);
                else if(gfv < 0.11f)
                    ck->SetBlockType(x, ++h, z, BlockType::Flower);
            }

            for(int y = h + 1; y != CHUNK_MAX_HEIGHT; ++y)
                ck->SetBlockType(x, y, z, BlockType::Air);

            ck->SetHeight(x, z, h);
        }
    }

    //������
    OakGenerator_V0(seed_).Make(ck);

    for(int x = 0; x != CHUNK_SECTION_SIZE; ++x)
    {
        for(int z = 0; z != CHUNK_SECTION_SIZE; ++z)
        {
            int H = ck->GetHeight(x, z);
            for(int y = 0; y <= H; ++y)
                ck->SetBlockLight(x, y, z, LIGHT_ALL_MIN);

            for(int y = H + 1; y < CHUNK_MAX_HEIGHT; ++y)
                ck->SetBlockLight(x, y, z, LIGHT_MIN_MIN_MIN_MAX);
        }
    }
}

int LandGenerator_V0::GetHeight(int x, int z)
{
    constexpr int LEVEL_NUM = 5;
    constexpr int MAX_GRID_SIZE = 128;
    constexpr float MAX_LEVEL_HEIGHT = 30.0f;

    int gridSize = MAX_GRID_SIZE;
    float levelHeight = MAX_LEVEL_HEIGHT;
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    auto randXZ = [&](int x, int z, int level)
    {
        return dis(RandomEngine(seed_ * x + z + level * level));
    };

    auto lerp = [](float a, float b, float t)
    {
        return a + (b - a) * (3 * t * t - 2 * t * t * t);
    };

    float result = 10.0f;
    for(int level = 0; level != LEVEL_NUM; ++level)
    {
        int gridX = (x + 0x40000000) / gridSize - 0x40000000 / gridSize;
        int gridZ = (z + 0x40000000) / gridSize - 0x40000000 / gridSize;

        float xzH   = randXZ(gridX, gridZ, level);
        float x1zH  = randXZ(gridX + 1, gridZ, level);
        float xz1H  = randXZ(gridX, gridZ + 1, level);
        float x1z1H = randXZ(gridX + 1, gridZ + 1, level);
        float tX    = static_cast<float>(x - gridX * gridSize) / gridSize;
        float tZ    = static_cast<float>(z - gridZ * gridSize) / gridSize;

        result += levelHeight * lerp(lerp(xzH, x1zH, tX), lerp(xz1H, x1z1H, tX), tZ);
        gridSize /= 2;
        levelHeight *= 0.7f;
    }

    return static_cast<int>(result);
}

float LandGenerator_V0::Random(Seed seedOffset, int blkX, int blkZ, float min, float max)
{
    return std::uniform_real_distribution<float>(min, max)(
        RandomEngine((seed_ + seedOffset) * blkX + blkZ));
}
