#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	vec4 texColor = texture2D(ourTexture, TexCoord);
	if (texColor.a < 0.1)
	{
		discard;
	}

	FragColor = texColor;
}