//
//  ModelObject.cpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/16.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "ModelObject.hpp"

ModelObject::ModelObject(string objName, string shaderName)
{
    string v = shaderName + ".vs";
    string f = shaderName + ".fs";
    programID = LoadShaders(v.c_str(), f.c_str());
    
    LoadMesh(objName.c_str(), &vertices);
    
    matrixID = glGetUniformLocation(programID, "MVP");
    
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
}

void ModelObject::SetPosition(vec3 position)
{
    modelMatrix = translate(mat4(), position);
}

vec3 ModelObject::GetPosition()
{
    return vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
}

void ModelObject::Rendering(Camera camera)
{
    glUseProgram(programID);
    
    auto MVP = camera.GetProjection() * camera.GetView() * modelMatrix;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glDrawArrays(GL_TRIANGLES, 0, (int)(vertices.size()));
    glDisableVertexAttribArray(0);
}

