//
//  ModelObject.hpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/16.
//  Copyright © 2017年 kyo. All rights reserved.
//

#ifndef ModelObject_hpp
#define ModelObject_hpp

#include "global.h"
#include "Loader.hpp"
#include "Camera.hpp"

class ModelObject
{
    mat4 modelMatrix = mat4();
    vector<vec3> vertices;
    
    GLuint programID;
    GLuint matrixID;
    GLuint vertexArray;
    GLuint vertexBuffer;
    
public:
    ModelObject(string objName, string shaderName);
    
    void SetPosition(vec3 position);
    vec3 GetPosition();
    
    void Rendering(Camera camera);
};

#endif /* ModelObject_hpp */
