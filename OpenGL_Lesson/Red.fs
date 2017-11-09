#version 330 core

// 最後に返す情報です。今回はRGBのvec3を
out vec3 color;

void main()
{
    // RGBそれぞれ1,0,0。つまり赤色です。(255ではなく、0~1で表します)
    color = vec3(1,0,0);
}
