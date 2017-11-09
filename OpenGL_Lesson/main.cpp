//
//  main.cpp
//  OpenGL_Lesson
//
//  Created by wta1601 on 2017/11/08.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "global.h"
#include "Loader.hpp"

// glfwWindowHintをまとめた処理です
void initWindowHints();



int main() {
    
    if (!glfwInit()){
        return -1;
    }
    
    initWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "🔺", NULL, NULL);
    
    if (!window){
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // GLEWの初期化処理です。
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    
    
    // 配列バッファオブジェクトの生成
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    // 三角の頂点
    static const GLfloat vertex[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
    
    
    // シェーダー読み込み
    GLuint programID = LoadShaders( "Red.vs", "Red.fs" );
    
    
    // 今扱うデータは位置だけなので、バッファオブジェクトを1つ生成します。(VBOで調べると詳しく解説されてます)
    // UVとかを扱うと、これが増えます。
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* ここから三角の描画処理 */
        
        // 指定したシェーダーを使います。
        glUseProgram(programID);
        
        glEnableVertexAttribArray(0);   // 頂点シェーダーのアトリビュート変数[location=0~]に渡すデータだという意思表示です。
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0             // アトリビュート変数。頂点シェーダーのlocationで指定した数字です。
                              ,3            // 位置はxyzの3つのデータ
                              ,GL_FLOAT     // データの型
                              ,GL_FALSE     // -1.0~1.0に正規化するか
                              ,0            // 配列のストライド
                              ,(void*)0);   // 配列バッファのオフセット
        
        glDrawArrays(GL_TRIANGLES, 0, 3);   // 指定した描画モードで描画
        
        glDisableVertexAttribArray(0);  // ここまで頂点シェーダーのlocation=0に渡すデータだという意思表示
        
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


