#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

out VertexOutput
{
vec4  Color;
vec2  TexCoord;
float TexIndex;
float TilingFactor;
} vs_Output;

uniform mat4 u_ViewProjection;

void main()
{
	vs_Output.Color = a_Color;
	vs_Output.TexCoord = a_TexCoord;
	vs_Output.TexIndex = a_TexIndex;
	vs_Output.TilingFactor = a_TilingFactor;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in VertexOutput
{
vec4  Color;
vec2  TexCoord;
float TexIndex;
float TilingFactor;
} vs_Input;

uniform sampler2D u_Textures[32];

void main()
{
	color = texture(u_Textures[int(vs_Input.TexIndex)], vs_Input.TexCoord * vs_Input.TilingFactor) * vs_Input.Color;
}