#version 330 core   // GLSL(シェーダーのバージョン)

// レイアウト変数です。与えられた頂点データなどの窓口です。
// 今回は頂点データを受け取ります
layout(location = 0) in vec3 vertexPosition_modelspace;

void main(){
    
    // gl_Positionは、GLSLであらかじめ用意されている変数です。
    // 頂点の座標を、0~1に変換してくれます。
    // 後々、テクスチャを読み込むようになると、gl_TexCoordとか出てきます。
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
    
}
