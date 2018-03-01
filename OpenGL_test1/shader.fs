#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

vec2 nTexCoord;

uniform float mixAmount;
uniform sampler2D texture1;
uniform sampler2D texture2;



void main()
{
	nTexCoord = vec2(-TexCoord.x, TexCoord.y);
	FragColor= mix(texture(texture1,TexCoord), texture(texture2, nTexCoord), mixAmount);
}