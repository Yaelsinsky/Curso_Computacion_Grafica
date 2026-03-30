#version 330 core
out vec4 outColor;
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    outColor = vec4(Color,1.0)*texture(ourTexture, TexCoord);
     FragColor = vec4(1.0f);
}