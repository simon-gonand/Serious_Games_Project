#version 330

precision highp float; // needed only for version 1.30

layout(location = 0) out vec4 out_Color;

in vec3 ex_Position;

void main(void){
	out_Color = vec4(0.0, 0.0, 1.0, 1.0);
}