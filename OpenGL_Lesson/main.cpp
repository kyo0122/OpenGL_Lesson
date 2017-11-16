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
#include "ModelObject.hpp"
#include "Bullet.hpp"

void initWindowHints();

int main() {
    
    if (!glfwInit()){
        return -1;
    }
    
    initWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "==🔴", NULL, NULL);
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
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // 深度を使うための宣言(デフォルトでは、あらゆる機能がオフ)
    glEnable(GL_DEPTH_TEST);
    
    ModelObject monkey("monkey.obj", "Basic");
    
    // 弾リスト
    vector<Bullet> bullets;

    Camera cam(vec3(0, 0, 2), window);
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        // GL_DEPTH_BUFFER_BITで深度情報のクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cam.controller(window);
        
        // 射出ボタン
        if (glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS) {
            Bullet b(cam.GetDirection());
            b.SetPosition(cam.GetPosition());
            bullets.push_back(b);
        }
        
        // 弾の更新
        for(int i = 0;i<bullets.size();i++)
        {
            bullets[i].Update();
            bullets[i].Rendering(cam);
        }
        
        monkey.Rendering(cam);
         
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


