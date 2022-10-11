#version 330 core

// This is the default fragment shader for A.C.E.
// This is kinda meant to be copy pasted and be built over as it uses the internal
// ACE uniform names.

uniform vec3 Color;
//uniform sampler2D TEXTURENAME		Add this for however many textures you have.

in vec3 FragPos;
in vec3 FragNorm;
in vec2 TexCoords;

void main(){
	gl_FragColor = vec4(TexCoords.yxy, 1.);
}
