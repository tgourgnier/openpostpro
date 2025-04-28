#version 300 es
precision highp float;

uniform vec4 inner_color;
uniform int  use_aa;
uniform float aa_factor;

uniform int use_clip;
uniform float clip_x;
uniform float clip_y;
uniform float clip_right;
uniform float clip_bottom;

// Input daata
in float f_aa;

// Ouput data
out vec4 color;

void main()
{
    if ( use_clip == 1 && (gl_FragCoord.x < clip_x || gl_FragCoord.x > clip_right || gl_FragCoord.y > clip_y || gl_FragCoord.y < clip_bottom ) )
        discard;

	float alpha = 1.0;
	if ( use_aa == 1 )
		alpha = f_aa * aa_factor;
	
	color = vec4(inner_color.rgb, inner_color.a * alpha);
}