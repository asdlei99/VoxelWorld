/*================================================================
Filename: VoxelModelEditorCore.h
Date: 2018.3.10
Created by AirGuanZ
================================================================*/
#pragma once

#include <deque>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SkeletonAnimation/SkeletonData.h>
#include "VoxelModelBinding.h"

class VMEFatalError
{
public:
    VMEFatalError(const std::string &msg)
        : msg_(msg)
    {

    }

    const char *What(void) const
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class VoxelModelEditorCore
{
public:
    VoxelModelEditorCore(void)
    {
        mainLoopDone_ = false;
        needRefreshDisplay_ = false;
    }

    int selectedBindingNameIndex_;
    std::vector<std::string> bindingNames_;

    bool mainLoopDone_;
    bool needRefreshDisplay_;

    bool modelChanged_;
    std::unique_ptr<VoxelModelBinding> model_;
};

class VoxelModelEditorCommand;
using VMECmdQueue = std::deque<VoxelModelEditorCommand*>;

class VoxelModelEditorCommand
{
public:
    virtual void Execute(VoxelModelEditorCore &core) = 0;
};
