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
    
    LoadModel(objName.c_str(), &indices, &vertices, &uvs, &normals);
    
    modelMatrixID = glGetUniformLocation(programID, "M");
    viewMatrixID = glGetUniformLocation(programID, "V");
    projectionMatrixID = glGetUniformLocation(programID, "P");
    
    textureID = glGetUniformLocation(programID, "textureSampler");
    lightID =glGetUniformLocation(programID, "LightPosition_w");
    
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(vec3), &indices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
    
}

void ModelObject::SetTexture(const char* path)
{
    texture = LoadTexture(path);
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
    
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &camera.GetView()[0][0]);
    glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &camera.GetProjection()[0][0]);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
    
    glUniform3f(lightID, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    
    glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_SHORT, (void*)0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

