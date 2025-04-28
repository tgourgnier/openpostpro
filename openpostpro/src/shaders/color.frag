#version 300 es
precision highp float;
// Interpolated values from the vertex shaders
in vec4 vec_color;

// Ouput data
out vec4 color;

uniform int use_clip;
uniform float clip_x;
uniform float clip_y;
uniform float clip_right;
uniform float clip_bottom;


void main()
{
    if ( use_clip == 1 && (gl_FragCoord.x < clip_x || gl_FragCoord.x > clip_right || gl_FragCoord.y > clip_y || gl_FragCoord.y < clip_bottom ) )
        discard;

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	color = vec_color;
}