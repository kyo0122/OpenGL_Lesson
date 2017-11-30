#version 330 core

in vec3 Position_w;
in vec3 Normal_c;
in vec3 EyeDirection_c;
in vec3 LightDirection_c;
in vec2 UV;

out vec3 color;

uniform vec3 LightPosition_w;
uniform sampler2D textureSampler;

void main() {
    vec3 LightColor = vec3(1,1,1);
    float LightPower = 10.0f;
    
    float distance_ = length( LightPosition_w - Position_w );
    // カメラ空間で、計算されたフラグメントの法線
    vec3 n = normalize( Normal_c );
    // 光の方向(フラグメントから光の方向)
    vec3 l = normalize( LightDirection_c );
    
    // 法線と光の方向の角度のコサイン
    // clamped above 0
    //  - 光が三角形に水平の場合 -> 1
    //  - 光が三角形に垂直の場合 -> 0
    //  - 光が三角形の裏側の場合 -> 0
    float cosTheta = clamp( dot( n,l ), 0,1);
    
    // アイ(目)ベクトル(カメラのほうへ向かう)
    vec3 E = normalize(EyeDirection_c);
    // 三角形が光を反射する方向
    vec3 R = reflect(-l,n);
    
    // アイベクトルと反射ベクトルの間の角度のコサイン
    // 0以上に固定します。
    //  - 反射する方向を向いている -> 1
    //  - 他の方向を見ている -> < 1
    float cosAlpha = clamp( dot( E,R ), 0,1 );
    
    // texture(textureSampler, UV).bgr
    color = texture(textureSampler, UV).bgr * LightColor * LightPower * cosTheta / (distance_*distance_) + LightColor * LightPower * pow(cosAlpha,5) / (distance_*distance_);
}

