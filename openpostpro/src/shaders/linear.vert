#version 300 es
precision highp float;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 in_vertex;
layout(location = 1) in float in_aa;

// Values that stay constant for the whole mesh.
uniform mat4 projection;
uniform mat4 modelview;

out float f_aa;

void main(){
    // Output position of the vertex, in clip space : projection * position
    gl_Position = projection * modelview * vec4(in_vertex,0,1);
	f_aa = in_aa;
}