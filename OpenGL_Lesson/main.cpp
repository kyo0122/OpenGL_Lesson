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
    
    ModelObject monkey("monkey.obj", "Basic");
    monkey.SetPosition(vec3(-3, -2, -1));
    
    vector<Bullet> bullets;

    Camera cam(vec3(0, 0, 2), window);
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        cam.controller(window);
        
        // 射出ボタン
        if (glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS) {
            Bullet b(cam.GetDirection());
            b.SetPosition(cam.GetPosition());
            bullets.push_back(b);
        }
        
        for(auto bullet : bullets)
        {
            bullet.Update();
            bullet.Rendering(cam);
        }
        
        auto pos = monkey.GetPosition();
        monkey.SetPosition(vec3(pos.x+.1, pos.z+.1, pos.z+.1));
        
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


