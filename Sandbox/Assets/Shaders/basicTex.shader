#shader vertex
#version 330 core

layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 u_MVP;

void main()
{
	TexCoord = texCoord;
	gl_Position = u_MVP * vertPos;
};

#shader fragment
#version 330 core

in vec2 TexCoord;

out vec4 outColor;

uniform vec4 u_Color;
uniform sampler2D u_Tex;

void main()
{
	outColor = texture(u_Tex, TexCoord) * u_Color;
	//outColor = u_Color;
};