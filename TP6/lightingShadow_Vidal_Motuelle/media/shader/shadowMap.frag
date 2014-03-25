#version 130

uniform sampler2D depthTexture;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {

  fragColor=vec4(0,0,0,0);
}
