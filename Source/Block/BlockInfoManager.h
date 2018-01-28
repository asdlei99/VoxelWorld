/*================================================================
Filename: BlockInfoManager.h
Date: 2018.1.17
Created by AirGuanZ
================================================================*/
#ifndef VW_BLOCK_INFO_MANAGER_H
#define VW_BLOCK_INFO_MANAGER_H

#include "../Utility/Singleton.h"
#include "BlockInfo.h"

class BlockInfoManager : public Singleton<BlockInfoManager>
{
public:
    BlockInfoManager::BlockInfoManager(void);

    const BlockInfo &GetBlockInfo(BlockType type) const;

    bool IsFaceVisible(BlockType dst, BlockType neighbor) const;

    bool IsSolid(BlockType type) const
    {
        return info_[Blk2Int(type)].isSolid;
    }

    bool IsRenderable(BlockType type) const
    {
        return info_[Blk2Int(type)].isRenderable;
    }

    bool IsCoverable(BlockType type) const
    {
        return info_[Blk2Int(type)].isCoverable;
    }

    bool IsGlow(BlockType type) const
    {
        return info_[Blk2Int(type)].isGlow;
    }

    const AABB &GetAABB(BlockType type) const
    {
        return info_[Blk2Int(type)].aabb;
    }

private:
    std::vector<BlockInfo> info_;
};

#endif //VW_BLOCK_INFO_MANAGER_H
