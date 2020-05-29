#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 mvp;
uniform mat4 model;

void main() {
	gl_Position = mvp * model * position;
}