#version 330 core

layout(location = 0) in vec3 Position_m;
layout(location = 1) in vec3 Normal_m;

out vec3 Position_w;
out vec3 Normal_c;
out vec3 EyeDirection_c;
out vec3 LightDirection_c;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_w;

void main() {
    gl_Position = P * V * M * vec4(Position_m,1);
    
    // ワールド空間での頂点の位置
    Position_w = (M * vec4(Position_m,1)).xyz;
    
    // カメラ空間で、頂点からカメラへ向かうベクトル
    // カメラ空間ではカメラは原点(0,0,0)にあります。
    vec3 Position_c = (V * M * vec4(Position_m,1)).xyz;
    EyeDirection_c = vec3(0,0,0) - Position_c;
    
    // カメラ空間で、頂点から光へ向かうベクトル。Mは単位行列なので除外します。
    vec3 LightPosition_c = (V * vec4(LightPosition_w,1)).xyz;
    LightDirection_c = LightPosition_c + EyeDirection_c;
    
    // カメラ空間での、頂点の法線
    Normal_c = (V * M * vec4(Normal_m,0)).xyz;
}
