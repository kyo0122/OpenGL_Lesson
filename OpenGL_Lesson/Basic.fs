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
    
    vec3 n = normalize( Normal_c );
    vec3 l = normalize( LightDirection_c );
    float cosTheta = clamp( dot( n,l ), 0,1);
    
    vec3 E = normalize(EyeDirection_c);
    vec3 R = reflect(-l,n);
    float cosAlpha = clamp( dot( E,R ), 0,1 );
    
    // texture(textureSampler, UV).rgb
    color = texture(textureSampler, UV).rgb * LightColor * LightPower * cosTheta / (distance_*distance_) + LightColor * LightPower * pow(cosAlpha,5) / (distance_*distance_);
}

