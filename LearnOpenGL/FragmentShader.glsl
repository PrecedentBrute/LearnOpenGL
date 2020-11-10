#version 330 core

out vec4 color;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float mix_value;

void main()
{
	color = vec4(ourColor, 1.0f) * mix(texture(ourTexture2, TexCoord), texture(ourTexture, TexCoord), mix_value);
}
	                                                              