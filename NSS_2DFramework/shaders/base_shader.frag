#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 spriteColor;

void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	if (texColor.a < 0.1)
	{
		discard;
	}

	FragColor = vec4(spriteColor, 1.0) * texColor;
}