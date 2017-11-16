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
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // オブジェクトの処理を一つにまとめたクラスを用意しました
    ModelObject monkey("monkey.obj", "Basic");

    Camera cam(vec3(0, 0, 2), window);
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // カメラの移動制御
        cam.controller(window);
        
        // オブジェクトの描画処理
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


