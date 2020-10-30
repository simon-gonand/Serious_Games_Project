#version 330

precision highp float; // needed only for version 1.30

layout(location = 0) out vec4 out_Color;

in vec2 ex_Tex;

uniform sampler2D textureUnit0;

void main(void){
	out_Color = texture(textureUnit0, ex_Tex);
}