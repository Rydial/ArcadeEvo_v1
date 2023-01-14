#version 460

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D texture1;

void main()
{
    fragColor = texture(texture1, texCoord);
}
