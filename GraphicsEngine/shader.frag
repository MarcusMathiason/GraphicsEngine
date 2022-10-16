#version 420

#ifdef GL_ES
precision mediump float;
#endif

layout(location = 0) out vec4 fragmentColor;
in vec3 outColor;

void main(){
	fragmentColor.rgb = outColor;
}