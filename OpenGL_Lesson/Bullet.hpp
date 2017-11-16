//
//  Bullet.hpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/16.
//  Copyright © 2017年 kyo. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "ModelObject.hpp"
#include "global.h"

class Bullet : public ModelObject
{
    vec3 direction;
    
public:
    
    Bullet(vec3 direction);
    void Update();
};

#endif /* Bullet_hpp */
