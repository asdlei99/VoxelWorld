/*================================================================
Filename: Actor.h
Date: 2018.1.19
Created by AirGuanZ
================================================================*/
#ifndef VW_ACTOR_H
#define VW_ACTOR_H

#include "../Camera/Camera.h"
#include "../Utility/Math.h"
#include "../Window/Window.h"

class Actor
{
public:
    void UpdateCamera(float deltaT);

    const Matrix &GetViewProjMatrix(void) const;
    const Camera &GetCamera(void) const;

private:
    float flyUpSpeed_ = 0.004f;
    float flyDownSpeed_ = 0.004f;
    float horMoveSpeed_ = 0.004f;

    float mouseXSpeed_ = 0.00005f;
    float mouseYSpeed_ = 0.00005f;

    Camera camera_;
};

#endif //VW_ACTOR_H
