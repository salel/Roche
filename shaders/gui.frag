layout (location = 0) in vec2 inUv;
layout (location = 1) in vec4 inColor;

layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform sampler2D atlas;

void main()
{
	outColor = inColor*texture(atlas, inUv);
}