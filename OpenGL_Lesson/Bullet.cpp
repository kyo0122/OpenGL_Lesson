//
//  Bullet.cpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/16.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(vec3 direction):ModelObject("sphere.obj", "Red")
{
    this->direction = direction;
}

void Bullet::Update()
{
    auto pos = GetPosition();
    pos+=direction;
    SetPosition(pos);
}
