/*================================================================
Filename: VoxelModelEditorDisplay.h
Date: 2018.3.10
Created by AirGuanZ
================================================================*/
#pragma once

#include <vector>

#include "VoxelModelEditorCommand.h"

class VoxelModelBindingDisplay
{
public:
    void Clear(void);

    void Display(void);

private:
    friend class VoxelModelBinding;

    std::string bindingName_;
};

class VoxelModelEditorDisplay
{
public:
    VoxelModelEditorDisplay(VMECmdQueue &cmdQueue);

    void Display(void);

private:
    void Frame(void);

private:
    std::vector<char> newBindingNameBuf_;

private:
    VMECmdQueue &cmdQueue_;

    friend class VoxelModelEditor;

    std::vector<const char*> bindingNames_;
    int selectedBindingNameIndex_;

    VoxelModelBindingDisplay bindingDisplay_;
};
