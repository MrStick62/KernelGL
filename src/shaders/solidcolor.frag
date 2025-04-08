#version 460 core
out vec4 FragColor;
in vec3 color;
in vec2 texCoord;

uniform vec3 colorMultiplier;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.5 * vec4(color * colorMultiplier, 1.0));
}