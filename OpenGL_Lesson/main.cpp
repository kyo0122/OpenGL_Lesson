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

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


void initWindowHints();

int main() {
    
    if (!glfwInit()){
        return -1;
    }
    
    initWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "💨", NULL, NULL);
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
    glEnable(GL_DEPTH_TEST);
    
    // 削除するモデルを配列として保持しておきます
    vector<ModelObject> models;
    
    ModelObject monkey1("monkey.obj", "Basic");
    monkey1.position = vec3(2, 0, 0);
    models.push_back(monkey1);
    
    ModelObject monkey2("monkey.obj", "Basic");
    monkey2.position = vec3(-2, 0, 0);
    models.push_back(monkey2);
    
    ModelObject monkey3("monkey.obj", "Basic");
    monkey3.position = vec3(0, 2, 0);
    models.push_back(monkey3);
    
    ModelObject monkey4("monkey.obj", "Basic");
    monkey4.position = vec3(0, -2, 0);
    models.push_back(monkey4);
    
    // 上の如く、弾も然り
    vector<Bullet> bullets;
    
    ModelObject skybox("skybox.obj", "Skybox");
    skybox.SetTexture("winter-2383930_1280.png");
    skybox.scale = vec3(100, 100, 100);
    
    Camera cam(vec3(0, 0, 0), window);
    cam.controller(window);
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // 弾を発射
        if(glfwGetKey(window, GLFW_KEY_X)==GLFW_PRESS){
            Bullet b(cam.GetDirection());
            b.position = cam.GetPosition();
            bullets.push_back(b);
        }
        
        // 全ての弾と猿(modelsの要素)との距離を計算。
        // 一定値以下の(接近している)状態で、描画無視フラグをオン
        for(auto &bullet : bullets){
            for(auto &model : models){
                auto d = distance(bullet.position, model.position);
                if(d < 0.5){
                    model.isDead = true;
                }
            }
        }
        
        /*
         *for(int i = 0; i < bullets.size; i++){
         *  bullet[i].Update();
         *  bullet[i].Rendering(cam);
         *}                             と同じ意味です。
         */
        for(auto &bullet : bullets){
            bullet.Update();
            bullet.Rendering(cam);
        }
        
        for(auto &model : models){
            if(!model.isDead){
                model.Rendering(cam);
            }
        }
        
        cam.controller(window);
        
        skybox.position = cam.GetPosition();
        skybox.Rendering(cam);
        
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
    glfwWindowHint(GLFW_DECORATED ,true);
}


