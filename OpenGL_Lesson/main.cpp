//
//  main.cpp
//  OpenGL_Lesson
//
//  Created by wta1601 on 2017/11/08.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "global.h"
#include "Loader.hpp"
#include "Camera.hpp"

// glfwWindowHintをまとめた処理です
void initWindowHints();

int main() {
    
    if (!glfwInit()){
        return -1;
    }
    
    initWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "🐵", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    
    // 入力周りの設定です。今回はカーソルを非表示にしています。
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    mat4 modelMatrix = mat4();  // MVPはGLUTでも扱っていたので、あまり触れません。
    vector<vec3> vertices;
    LoadMesh("monkey.obj", &vertices);
    
    vector<vec3> normals;
    LoadNormal("monkey.obj", &normals);
    
    // シェーダー読み込み
    GLuint programID = LoadShaders( "Basic.vs", "Basic.fs" );
    GLuint modelMatrixID = glGetUniformLocation(programID, "M");   // シェーダー参照
    GLuint viewmatrixID = glGetUniformLocation(programID, "V");   // シェーダー参照
    GLuint projectionmatrixID = glGetUniformLocation(programID, "P");   // シェーダー参照
    GLuint lightPositionID = glGetUniformLocation(programID, "LightPosition_w");   // シェーダー参照
    
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
    
    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(vec3), &normals[0], GL_STATIC_DRAW);
    
    // 自前のカメラクラスです。位置とカメラが担当するウィンドウを指定します。
    Camera cam(vec3(0, 0, 2), window);
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.5, .5, .5, 1);
        
        
        // カメラの移動制御
        cam.controller(window);
        
        glUseProgram(programID);
        
        // シェーダーに各値を渡しています。
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(viewmatrixID, 1, GL_FALSE, &cam.getView()[0][0]);
        glUniformMatrix4fv(projectionmatrixID, 1, GL_FALSE, &cam.getProjection()[0][0]);
        glUniform3f(lightPositionID, cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        
        glDrawArrays(GL_TRIANGLES, 0, (int)(vertices.size()));
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void initWindowHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED ,true);  // <-これをfalseにすると…
}


