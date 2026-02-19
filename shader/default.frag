#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float time;

uniform float mixValue;

void main()
{
    FragColor = texture(texture1, TexCoord) + texture(texture2, TexCoord) * mixValue + vec4(TexCoord.xy, 0.0, 1.0) * sin(time * 0.2);
}