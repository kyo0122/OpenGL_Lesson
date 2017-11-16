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
    pos+=vec3(direction.x*10, direction.y*10, direction.z*10);
    this->SetPosition(pos);
    
//    auto position = GetPosition();
//    cout<<position.x<<", "<<position.y<<", "<<position.z<<", "<<endl;
//    cout<<direction.x<<", "<<direction.y<<", "<<direction.z<<", "<<endl;
//
//    this->SetPosition(vec3(position.x+1, position.z+1, position.z+1));
    
}
