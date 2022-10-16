#version 420

#ifdef GL_ES
precision mediump float;
#endif

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out vec3 outColor;

void main(){
	gl_Position = vec4(in_position, 1.0);
	outColor = in_color;
}