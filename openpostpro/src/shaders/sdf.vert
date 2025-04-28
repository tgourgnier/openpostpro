#version 300 es
precision highp float;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 in_vertex;
layout(location = 1) in vec2 in_texture;

// Output data ; will be interpolated for each fragment.
out vec2 vec_texture;

// Values that stay constant for the whole mesh.
uniform mat4 modelview;
uniform mat4 projection;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  projection * modelview * vec4(in_vertex, 0, 1);
	
	// UV of the vertex. No special space for this one.
	vec_texture = in_texture;
}