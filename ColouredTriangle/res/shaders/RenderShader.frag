#version 450

// Incoming interpolated UV coordinates.
layout (location = 0) in Block
{
    vec3 interpolatedColor;
    vec3 N;
    vec3 worldVertex;
	vec2 UV;
};

// Outgoing final color.
layout (location = 0) out vec4 outputColor;

// Texture sampler
uniform sampler2D textureSampler;

void main()
{
    // Retrieve the final color from the texture
    outputColor = texture(textureSampler, UV).rgba;
}
