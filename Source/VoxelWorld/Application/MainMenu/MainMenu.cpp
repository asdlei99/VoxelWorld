/*================================================================
Filename: MainMenu.cpp
Date: 2018.2.27
Created by AirGuanZ
================================================================*/
#include <memory>

#include <CEGUI\CEGUI.h>
#include <Utility\Clock.h>

#include <Input\InputManager.h>
#include <Resource\ResourceNameManager.h>
#include <Screen\GUISystem.h>
#include <Window\Window.h>

#include "MainMenu.h"

AppState MainMenu::Run(void)
{
    Window &win         = Window::GetInstance();
    InputManager &input = InputManager::GetInstance();
    RscNameMgr &rM      = RscNameMgr::GetInstance();

    bool done = false;
    AppState ret = AppState::Exit;

    win.SetBackgroundColor(0.0f, 1.0f, 1.0f, 0.0f);

    std::unique_ptr<GUIContext, GUIContext::Deleter> ctx(
        GUI::CreateGUIContextFromLayoutFile(rM.AsString("MainMenu", "LayoutFile")));
    ctx->SetDefaultFont(rM.AsString("MainMenu", "Font"));
    ctx->Enable();

    CEGUI::PushButton *gameButton = static_cast<CEGUI::PushButton*>
        (ctx->GetCEGUIContext()->getRootWindow()->getChild("Game"));
    gameButton->subscribeEvent(CEGUI::PushButton::EventMouseClick,
                               CEGUI::Event::Subscriber(&MainMenu::GameClicked, this));

    CEGUI::PushButton *exitButton = static_cast<CEGUI::PushButton*>
        (ctx->GetCEGUIContext()->getRootWindow()->getChild("Exit"));
    exitButton->subscribeEvent(CEGUI::PushButton::EventMouseClick,
                               CEGUI::Event::Subscriber(&MainMenu::ExitClicked, this));

    CEGUI::PushButton *editButton = static_cast<CEGUI::PushButton*>
        (ctx->GetCEGUIContext()->getRootWindow()->getChild("VoxelModelEditor"));
    editButton->subscribeEvent(CEGUI::PushButton::EventMouseClick,
        CEGUI::Event::Subscriber(&MainMenu::EditClicked, this));

    Clock clock;
    clock.Restart();

    while(!done)
    {
        win.ClearDepthStencil();
        win.ClearRenderTarget();

        GUI::BeginCERender();
        ctx->Render();
        GUI::EndCERender();

        win.Present();
        win.DoEvents();

        clock.Tick();
        GUI::TimeElapsed(clock.ElapsedTime());

        if(gameClicked_)
        {
            ret = AppState::Game;
            done = true;
        }
        else if(exitClicked_)
        {
            ret = AppState::Exit;
            done = true;
        }
        else if(editClicked_)
        {
            ret = AppState::VoxelModelEditor;
            done = true;
        }
    }

    return ret;
}
