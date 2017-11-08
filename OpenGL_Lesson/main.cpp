//
//  main.cpp
//  OpenGL_Lesson
//
//  Created by wta1601 on 2017/11/08.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include <iostream>
using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>

#pragma clang pop



int main() {
    
    // glfwの初期化です。失敗するとTrueを返します。必ず実行してください。
    if (!glfwInit()){
        return -1;
    }
    
    // OpenGLのバージョンなどの設定です。
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED ,true);  // <-これをfalseにすると…
    
    
    GLFWwindow* window;                     // glfwでは複数のウィンドウを利用することができます。
    int width  = 640;            // 初期生成時のウィンドウの横幅です。
    int height = 480;            // 初期生成時のウィンドウの縦幅です。
    const char* windowName = "ｳｨﾝﾄﾞｳﾀﾞﾖ-🌝 〜そして日本語も〜";  // ウィンドウに表示される名前です。
    
    // glfwCreateWindow:ウィンドウを生成します。左側のNULLをglfwGetPrimaryMonitor()にすると、フルスクリーンモードになります。
    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    
    // ウィンドウ生成が失敗するとTrueを返します。
    if (!window){
        glfwTerminate();    // glfwの終了時に呼び出す関数です。
        return -1;
    }
    
    // ウィンドウのコンテキストをカレントにします。(これから行う処理は指定したwindowに対するものですよ…的なことですよ、多分。)
    glfwMakeContextCurrent(window);
    
    
    // glfwWindowShouldClose:ウィンドウが閉じられた時にTrueを返します。
    // glfwGetKey: 指定windowでのキー入力を取得します。状態確認はGLFW_PRESSなどで確認します。
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);   // 指定バッファ(今回は色バッファ)の初期化を行います。そのうち透過度、深度なども指定して初期化します。
        glClearColor(.3, .3, .3, 1);    // 指定した色で画面をクリアします。
        
        
        
        glfwSwapBuffers(window);    // 表示されている画面の裏で用意された絵に切り替えます。
        glfwPollEvents();   // イベントの確認です。ボタン入力とかのことです。
    }
    
    glfwTerminate();    // さっき出てきました。
    
    
    return 0;
}
