#version 330
//precision highp float;

uniform vec4 inner_color;
uniform int  use_aa;
uniform int  use_clip;
uniform float aa_factor;

// Input daata
in float f_aa;

// Ouput data
out vec4 color;

void main(){
	float alpha = 1.0;
	if ( use_aa == 1 )
		alpha = f_aa * aa_factor;
	
	color = vec4(inner_color.rgb, inner_color.a * alpha);
}