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
protected:
    mat4 modelMatrix;
    
    vector<unsigned short> indices;
    vector<vec3> vertices;
    vector<vec2> uvs;
    vector<vec3> normals;
    GLuint texture;
    
    GLuint programID;
    GLuint textureID;
    GLuint lightID;
    GLuint modelMatrixID;
    GLuint viewMatrixID;
    GLuint projectionMatrixID;
    
    GLuint vertexArray;
    GLuint elementBuffer;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint normalBuffer;
    
public:
    ModelObject(string objName, string shaderName);
    
    vec3 position = vec3(0, 0, 0);
    vec3 rotation = vec3(0, 0, 0);
    vec3 scale = vec3(1, 1, 1);
    
    void SetTexture(const char* path);
    
//    void SetPosition(vec3 position);
//    vec3 GetPosition();
    
    void Rendering(Camera camera);
};

#endif /* ModelObject_hpp */
