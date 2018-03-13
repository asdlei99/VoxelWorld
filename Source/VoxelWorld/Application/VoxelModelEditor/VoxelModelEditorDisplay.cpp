/*================================================================
Filename: VoxelModelEditorDisplay.cpp
Date: 2018.3.10
Created by AirGuanZ
================================================================*/
#include <Screen/GUISystem.h>
#include <Window/Window.h>

#include "VoxelModelBinding.h"
#include "VoxelModelEditorDisplay.h"

VoxelModelEditorDisplay::VoxelModelEditorDisplay(VMECmdQueue &cmdQueue)
    : cmdQueue_(cmdQueue)
{
    newBindingNameBuf_.resize(32);
    newBindingNameBuf_[0] = '\0';
}

void VoxelModelEditorDisplay::Display(void)
{
    Window &win = Window::GetInstance();

    GUI::NewFrame();
    win.ClearDepthStencil();
    win.ClearRenderTarget();

    Frame();

    GUI::RenderImGui();

    win.Present();
    win.DoEvents();
}

void VoxelModelEditorDisplay::Frame(void)
{
    if(ImGui::Begin("Select Binding##VoxelModelEditor", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Select Binding Name:");
        if(bindingNames_.size())
        {
            assert(0 <= selectedBindingNameIndex_ &&
                selectedBindingNameIndex_ < static_cast<int>(bindingNames_.size()));
            int selected = selectedBindingNameIndex_;
            ImGui::ListBox("", &selected,
                bindingNames_.data(), bindingNames_.size(), 5);
            if(selected != selectedBindingNameIndex_)
                cmdQueue_.push_back(new VMWCmd_SelectBindingName(selected));
        }
        else
            ImGui::Text("No Binding");

        if(ImGui::SmallButton("Exit"))
            cmdQueue_.push_back(new VMECmd_ExitClicked());

        ImGui::SameLine();
        if(ImGui::SmallButton("Load"))
            cmdQueue_.push_back(new VMWCmd_LoadSelectedBinding());

        ImGui::SameLine();
        if(ImGui::SmallButton("Unload"))
            cmdQueue_.push_back(new VMWCmd_UnloadBinding());

        ImGui::SameLine();
        if(ImGui::SmallButton("Delete"))
            cmdQueue_.push_back(new VMWCmd_DeleteSelectedBinding());

        ImGui::InputText("", newBindingNameBuf_.data(), newBindingNameBuf_.size());

        ImGui::SameLine();
        if(ImGui::Button("+") && newBindingNameBuf_[0] != '\0')
        {
            cmdQueue_.push_back(new VMWCmd_CreateBinding(std::string(newBindingNameBuf_.data())));
            newBindingNameBuf_[0] = '\0';
        }

        bindingDisplay_.Display();
    }
    ImGui::End();

    cmdWinDisplay_.Display();
}