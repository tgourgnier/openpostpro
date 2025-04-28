#version 300 es
precision highp float;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 in_vertex;
layout(location = 1) in vec4 in_color;

// Values that stay constant for the whole mesh.
uniform mat4 modelview;
uniform mat4 projection;

// Output data ; will be interpolated for each fragment.
out vec4 vec_color;

void main()
{
    // Output position of the vertex, in clip space : MVP * position
    gl_Position = projection * modelview * vec4(in_vertex, 0, 1);

    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    vec_color = in_color;
}